// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: MIT
#include "PresentMon.h"
#include <Core/source/infra/log/Logging.h>
#include <PresentMonAPI/PresentMonAPI.h>
#include <PresentMonAPI2/source/PresentMonAPI.h>
#include <PresentMonAPIWrapper/source/PresentMonAPIWrapper.h>
#include <Core/source/infra/util/Util.h>
#include "metric/NoisySineFakeMetric.h"
#include "metric/SquareWaveMetric.h"
#include "metric/DynamicPollingMetric.h"
#include "EnumMap.h"
#include "RawFrameDataWriter.h"

namespace p2c::pmon
{
	PresentMon::PresentMon(std::optional<std::string> namedPipeName, std::optional<std::string> sharedMemoryName, double window_in, double offset_in, uint32_t telemetrySamplePeriodMs_in)
	{
		const auto RemoveDoubleQuotes = [](std::string s) {
			if (s.front() == '"' && s.back() == '"' && s.size() >= 2) {
				s = s.substr(1, s.size() - 2);
			}
			return s;
		};
		if (namedPipeName && sharedMemoryName) {
			auto pipeName = RemoveDoubleQuotes(*namedPipeName);
			auto shmName = RemoveDoubleQuotes(*sharedMemoryName);
			p2clog.info(std::format(L"Connecting to service with custom pipe [{}] and nsm [{}]",
				infra::util::ToWide(pipeName),
				infra::util::ToWide(shmName)
			)).commit();
			pSession = std::make_unique<pmapi::Session>(std::move(pipeName), std::move(shmName));
		}
		else {
			p2clog.info(L"Connecting to service with default pipe name").commit();
			pSession = std::make_unique<pmapi::Session>();
		}

		// acquire introspection data
		pIntrospectionRoot = pSession->GetIntrospectionRoot();

		// populate lookup for enumerations in dynamic metrics
		EnumMap::Init(*pIntrospectionRoot);

		// Build table of available metrics using introspection
		using namespace met;

		for (auto m : pIntrospectionRoot->GetMetrics()) {
			// not excluding any metric to keep index stability for the time being
			// exclude metrics when there is no device supporting them
			// if (std::ranges::none_of(m.GetDeviceMetricInfo(), [](auto&& i) { return i.IsAvailable(); })) continue;
			// loop over all indexes for max array size among all available devices
			// const auto maxIndex = DynamicPollingMetric::CalculateMaxArrayIndex(m.GetId(), *pIntrospectionRoot);
			// instead of checking index, we're going to hardcode that fan speed has 5 elements
			// this is to keep stablitity of the metric index on the frontend
			// TODO: give fully-configured metrics a uid OR make frontend specify widget with id/stat/index instead of
			// just registered metric container index
			const auto maxIndex = m.GetId() == PM_METRIC_GPU_FAN_SPEED ? 5u : 1u;
			for (uint32_t i = 0; i < maxIndex; i++) {
				for (auto s : m.GetStatInfo()) {
					// skip STAT_NONE (it's only for frame event data)
					if (s.GetStat() == PM_STAT_NONE) continue;
					AddMetric(std::make_unique<DynamicPollingMetric>(m.GetId(), i, s.GetStat(), *pIntrospectionRoot));
				}
			}
		}

		// fake metrics for testing
#ifdef _DEBUG
		AddMetric(std::make_unique<NoisySineFakeMetric>(L"Fake Noisy Sinusoid", 0.1f, 0.f, 30.f, 50.f, 3.f, 3.f));
		AddMetric(std::make_unique<NoisySineFakeMetric>(L"Fake Pure Sinusoid", 2.f, 0.f, 40.f, 50.f, 3.f, 0.f));
		AddMetric(std::make_unique<NoisySineFakeMetric>(L"Fake Slow Sinusoid", 0.05f, 0.f, 40.f, 50.f, 3.f, 0.f));
		AddMetric(std::make_unique<SquareWaveMetric>(L"Fake Square Wave", 1., 0.f, 100.f));
#endif

		// establish initial sampling / window / processing setting values
		SetWindow(window_in);
		SetOffset(offset_in);
		SetGpuTelemetryPeriod(telemetrySamplePeriodMs_in);
	}
	PresentMon::~PresentMon() = default;
	void PresentMon::StartTracking(uint32_t pid_)
	{
		if (pTracker) {
			if (pTracker->GetPid() == pid_) {
				return;
			}
			p2clog.warn(std::format(L"Starting stream [{}] while previous stream [{}] still active",
				pid_, pTracker->GetPid())).commit();
		}
		pTracker = pSession->TrackProcess(pid_);
		p2clog.info(std::format(L"started pmon stream for pid {}", pid_)).commit();
	}
	void PresentMon::StopTracking()
	{
		if (!pTracker) {
			p2clog.warn(L"Cannot stop stream: no stream active").commit();
			return;
		}
		const auto pid = pTracker->GetPid();
		pTracker.reset();
		// TODO: caches cleared here maybe
		p2clog.info(std::format(L"stopped pmon stream for pid {}", pid)).commit();
	}
	double PresentMon::GetWindow() const { return window; }
	void PresentMon::SetWindow(double window_) { window = window_; }
	double PresentMon::GetOffset() const { return offset; }
	void PresentMon::SetOffset(double offset_) { offset = offset_; }
	void PresentMon::SetGpuTelemetryPeriod(uint32_t period)
	{
		pSession->SetTelemetryPollingPeriod(1, period);
		telemetrySamplePeriod = period;
	}
	uint32_t PresentMon::GetGpuTelemetryPeriod()
	{
		return telemetrySamplePeriod;
	}
	std::wstring PresentMon::GetCpuName() const
	{
		char buffer[512];
		uint32_t bufferSize = sizeof(buffer);
		if (auto sta = pmGetCpuName(buffer, &bufferSize); sta != PM_STATUS_SUCCESS) {
			p2clog.warn(L"could not get cpu name").code(sta).commit();
			return {};
		}
		if (bufferSize >= sizeof(buffer)) {
			p2clog.warn(std::format(L"insufficient buffer size to get cpu name. written: {}", bufferSize)).commit();
		}
		return infra::util::ToWide(std::string{ buffer, bufferSize });
	}
	met::Metric* PresentMon::GetMetricByIndex(size_t index) { return metrics.at(index).get(); };
	std::vector<met::Metric::Info> PresentMon::EnumerateMetrics() const
	{
		std::vector<met::Metric::Info> info;
		size_t index = 0;
		for (auto& m : metrics)
		{
			info.push_back(m->GetInfo(index));
			index++;
		}
		return info;
	}
	std::vector<AdapterInfo> PresentMon::EnumerateAdapters() const
	{
		std::vector<AdapterInfo> infos;
		for (const auto& info : pIntrospectionRoot->GetDevices()) {
			if (info.GetType() != PM_DEVICE_TYPE_GRAPHICS_ADAPTER) {
				continue;
			}
			infos.push_back(AdapterInfo{
				.id = info.GetId(),
				.vendor = info.IntrospectVendor().GetName(),
				.name = info.GetName(),
			});
		}
		return infos;
	}
	void PresentMon::SetAdapter(uint32_t id)
	{
		if (id == 0) {
			p2clog.warn(L"Adapter was set to id 0; resetting").commit();
			selectedAdapter.reset();
		}
		else {
			selectedAdapter = id;
		}
	}
	std::optional<uint32_t> PresentMon::GetPid() const {
		return bool(pTracker) ? pTracker->GetPid() : std::optional<uint32_t>{};
	}
	std::shared_ptr<RawFrameDataWriter> PresentMon::MakeRawFrameDataWriter(std::wstring path,
		std::optional<std::wstring> statsPath, uint32_t pid, std::wstring procName)
	{
		return std::make_shared<RawFrameDataWriter>(std::move(path), pid, std::move(procName),
			*pSession, std::move(statsPath), *pIntrospectionRoot);
	}
	std::optional<uint32_t> PresentMon::GetSelectedAdapter() const
	{
		return selectedAdapter;
	}
	const pmapi::intro::Root& PresentMon::GetIntrospectionRoot() const
	{
		return *pIntrospectionRoot;
	}
	pmapi::Session& PresentMon::GetSession()
	{
		return *pSession;
	}
	void PresentMon::AddMetric(std::unique_ptr<met::Metric> metric_)
	{
		metrics.push_back(std::move(metric_));
	}
}