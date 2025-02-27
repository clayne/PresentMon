// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: MIT
#include "Kernel.h"
#include <Core/source/win/WinAPI.h>
#include <Core/source/win/MessageBox.h>
#include <Core/source/infra/Logging.h>
#include <Core/source/infra/util/FolderResolver.h>
#include <random>
#include "OverlayContainer.h"
#include "TargetLostException.h"
#include <Core/source/win/ProcessMapBuilder.h>
#include <Core/source/win/com/WbemConnection.h>
#include <Core/source/cli/CliOptions.h>
#include <CommonUtilities/str/String.h>
#include <CommonUtilities/Exception.h>
#include <boost/process/windows.hpp>


using namespace std::literals;
using namespace ::pmon::util;

namespace p2c::kern
{
    using str::ToWide;

    Kernel::Kernel(KernelHandler* pHandler)
        :
        pHandler{ pHandler },
        constructionSemaphore{ 0 },
        thread{ "kernel", &Kernel::ThreadProcedure_, this}
    {
        constructionSemaphore.acquire();
        HandleMarshalledException_();
    }

    Kernel::~Kernel()
    {
        {
            std::lock_guard lk{ mtx };
            dying = true;
        }
        cv.notify_one();
    }

    void Kernel::PushSpec(std::unique_ptr<OverlaySpec> pSpec)
    {
        HandleMarshalledException_();
        {
            std::lock_guard lk{ mtx };
            pPushedSpec = std::move(pSpec);
        }
        cv.notify_one();
    }

    void Kernel::ClearOverlay()
    {
        HandleMarshalledException_();
        {
            std::lock_guard lk{ mtx };
            if (pOverlayContainer) {
                clearRequested = true;
                pPushedSpec.reset();
            }
        }
        cv.notify_one();
    }

    std::vector<Process> Kernel::ListProcesses()
    {
        HandleMarshalledException_();
        win::ProcessMapBuilder builder;
        builder.FillWindowHandles();
        builder.FilterHavingWindow();
        auto pmap = builder.Extract();

        std::vector<Process> list;
        list.reserve(pmap.size());
        for (auto& entry : pmap) {
            using Win32Handle = ::pmon::util::win::Handle;
            Process proc = std::move(entry.second);
            if (proc.hWnd) {
                proc.windowName = win::GetWindowTitle(proc.hWnd);
                // determine whether each process is 32 or 64-bit
                ::pmon::util::win::Handle hProcess;
                if (auto hProcess = (Win32Handle)OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, proc.pid)) {
                    BOOL isWow64 = false;
                    if (IsWow64Process(hProcess, &isWow64)) {
                        proc.is32bit = isWow64;
                    }
                    else {
                        pmlog_error("Failed to query process WOW64 status").hr();
                    }
                }
                else {
                    pmlog_error("Failed to open process").hr();
                }
            }
            list.push_back(std::move(proc));
        }
        processListCache = list;
        return list;
    }

    void Kernel::SetAdapter(uint32_t id)
    {
        HandleMarshalledException_();
        std::lock_guard lk{ mtx };
        if (!pm) {
            pmlog_warn("presentmon not initialized");
            return;
        }
        pm->SetAdapter(id);
    }

    const pmapi::intro::Root& Kernel::GetIntrospectionRoot() const
    {
        HandleMarshalledException_();
        std::lock_guard g{ mtx };
        return pm->GetIntrospectionRoot();
    }

    std::vector<pmon::AdapterInfo> Kernel::EnumerateAdapters() const
    {
        HandleMarshalledException_();
        std::lock_guard lk{ mtx };
        if (!pm) {
            pmlog_warn("presentmon not initialized");
            return {};
        }
        try { return pm->EnumerateAdapters(); }
        catch (...) { 
            pmlog_warn("failed to enumerate adapters, returning empty set");
            return {};
        }
    }

    void Kernel::SetCapture(bool active)
    {
        HandleMarshalledException_();
        std::lock_guard lk{ mtx };
        pushedCaptureActive = active;
    }

    bool Kernel::IsIdle_() const
    {
        return !dying && !pPushedSpec && !pOverlayContainer;
    }

    std::unique_ptr<OverlaySpec> Kernel::PullSpec_()
    {
        std::lock_guard g{ mtx };
        return std::move(pPushedSpec);
    }

    void Kernel::HandleMarshalledException_() const
    {
        if (hasMarshalledException) {
            std::rethrow_exception(marshalledException);
        }
    }

    void Kernel::ThreadProcedure_()
    {
        try {
            // mutex that prevents frontend from accessing before pmon is connected
            std::unique_lock startLck{ mtx };

            // name this thread
            pmlog_info("== kernel thread starting ==");

            // command line options
            auto& opt = cli::Options::Get();

            // connect to wbem
            win::com::WbemConnection wbemConn;

            // connection names control from cli override / svc-as-child
            auto controlPipe = opt.controlPipe.AsOptional();
            auto shmName = opt.shmName.AsOptional();
            // force optionals filled with default values if not specified when launching service as child
            if (opt.svcAsChild) {
                controlPipe = *opt.controlPipe;
                shmName = *opt.shmName;
            }

            // create the PresentMon object
            try { pm.emplace(controlPipe, shmName); }
            catch (...) {
                pHandler->OnPresentmonInitFailed();
                pmlog_error("Failed to init presentmon api").no_trace();
                throw;
            }

            startLck.unlock();
            constructionSemaphore.release();

            while (!dying)
            {
                try
                {
                    {
                        std::unique_lock u{ mtx };
                        if (enableFlashInjection && lastProcessTargetted) {
                            namespace bp = boost::process;
                            const auto path = std::filesystem::current_path() / 
                                (lastProcessTargetted->is32bit ?
                                "FlashInjector-Win32.exe"s : "FlashInjector-x64.exe"s);
                            pmlog_dbg("launching injector child").pmwatch(path.string());
                            flashInjectorProcess.emplace(path.string(),
                                "--exe-name", lastProcessTargetted->name,
                                bp::windows::hide);
                        }
                        else if (flashInjectorProcess) {
                            pmlog_dbg("terminating injector child");
                            flashInjectorProcess.reset();
                        }
                        cv.wait(u, [this] {return !IsIdle_(); });
                    }
                    if (pPushedSpec && !dying)
                    {
                        // spawn overlay (container)
                        ConfigurePresentMon_(*pPushedSpec);
                        pOverlayContainer = std::make_unique<OverlayContainer>(wbemConn, std::move(pPushedSpec), &*pm);
                    }
                    if (pOverlayContainer && !dying)
                    {
                        // blocks while overlay is active
                        RunOverlayLoop_();
                    }
                }
                // this catch section handles target lost and overlay crashes
                // control app will still work, can attempt to instance another overlay
                catch (const TargetLostException&)
                {
                    if (pOverlayContainer) {
                        pHandler->OnTargetLost(pOverlayContainer->GetProcess().pid);
                        pOverlayContainer.reset();
                        pPushedSpec.reset();
                    }
                    else {
                        pHandler->OnStalePidSelected();
                    }
                }
                catch (...) {
                    pHandler->OnOverlayDied();
                    pmlog_error("Overlay died w/ except. => " + ReportException().first).no_trace();
                    pOverlayContainer.reset();
                    pPushedSpec.reset();
                }
            }

            pm.reset();

            pmlog_info("== kernel thread exiting ==");
        }
        // this catch section handles failures to initialize kernel, or rare error that escape the main loop catch
        // possibility to marshall exceptions to js whenever an interface function is called (async rejection path)
        catch (...) {
            pmlog_error(ReportException()).no_trace();
            marshalledException = std::current_exception();
            hasMarshalledException.store(true);
        }
        constructionSemaphore.release();

        // make sure all the logging messages from kernel thread are processed
        if (auto chan = log::GetDefaultChannel()) {
            chan->Flush();
        }
    }

    void Kernel::RunOverlayLoop_()
    {
        // this loop runs while the overlay window is active
        while (pOverlayContainer)
        {
            // checking thread sync signals
            {
                std::lock_guard lk{ mtx };
                if (dying || clearRequested)
                {
                    pOverlayContainer->InitiateClose();
                    pPushedSpec.reset();
                    clearRequested = false;
                    inhibitTargetLostSignal = true;
                }
                else if (pPushedSpec)
                {
                    auto& curSpec = pOverlayContainer->GetSpec();
                    if (pPushedSpec->pid != curSpec.pid) {
                        pOverlayContainer->InitiateClose();
                    }
                    else if (pPushedSpec->independentKernelWindow != curSpec.independentKernelWindow ||
                        pPushedSpec->upscale != curSpec.upscale ||
                        (pPushedSpec->upscale && pPushedSpec->upscaleFactor != curSpec.upscaleFactor)) {
                        ConfigurePresentMon_(*pPushedSpec);
                        inhibitTargetLostSignal = true;
                        pOverlayContainer->RebootOverlay(std::move(pPushedSpec));
                    }
                    else {
                        ConfigurePresentMon_(*pPushedSpec);
                        pOverlayContainer->RebuildDocument(std::move(pPushedSpec));
                    }
                }
                else if (pushedCaptureActive)
                {
                    std::wstring path = infra::util::FolderResolver::Get()
                        .Resolve(infra::util::FolderResolver::Folder::Documents) + L"\\Captures\\";
                    pOverlayContainer->SetCaptureState(*pushedCaptureActive, std::move(path), pOverlayContainer->GetSpec().captureName);
                    pushedCaptureActive.reset();
                }
            }
            pOverlayContainer->CheckAndProcessFullscreenTransition();
            // process windows messages
            {
                MSG msg;
                while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
                {
                    if (msg.message == WM_QUIT)
                    {
                        if (!dying && !inhibitTargetLostSignal) {
                            pHandler->OnTargetLost(pOverlayContainer->GetProcess().pid);
                        }
                        inhibitTargetLostSignal = false;
                        pOverlayContainer.reset();
                        break;
                    }
                    TranslateMessage(&msg);
                    DispatchMessageW(&msg);
                }
            }
            // handle data and overlay
            if (pOverlayContainer)
            {
                pOverlayContainer->RunTick();
            }
        }
    }

    void Kernel::ConfigurePresentMon_(const OverlaySpec& newSpec)
    {
        if (newSpec.telemetrySamplingPeriodMs != pm->GetGpuTelemetryPeriod()) {
            pm->SetGpuTelemetryPeriod(newSpec.telemetrySamplingPeriodMs);
        }        
        if (const auto currentEtwPeriod = pm->GetEtwFlushPeriod();
            newSpec.manualEtwFlush != bool(currentEtwPeriod) ||
            (currentEtwPeriod && *currentEtwPeriod != newSpec.etwFlushPeriod)) {
            pm->SetEtwFlushPeriod(newSpec.manualEtwFlush ?
                std::optional{ uint32_t(newSpec.etwFlushPeriod) } : std::nullopt);
        }
        if (auto i = rn::find(processListCache, newSpec.pid, &Process::pid); i != processListCache.end()) {
            lastProcessTargetted = *i;
        }
        enableFlashInjection = newSpec.enableFlashInjection;
    }
}
