// Copyright (C) 2017-2024 Intel Corporation
// SPDX-License-Identifier: MIT
//
// This file originally generated by etw_list
//     version:    public 1b19f39ddb669f7a700a5d0c16cf079943e996d5
//     parameters: --no_event_structs --event=Present::Start --event=Present::Stop --event=PresentMultiplaneOverlay::Start --event=PresentMultiplaneOverlay::Stop --event=SwapChain::Start --event=ResizeBuffers::Start --provider=Microsoft-Windows-DXGI
#pragma once

namespace Microsoft_Windows_DXGI {

struct __declspec(uuid("{CA11C036-0102-4A2D-A6AD-F03CFED5D3C9}")) GUID_STRUCT;
static const auto GUID = __uuidof(GUID_STRUCT);

enum class Keyword : uint64_t {
    Objects                         = 0x1,
    Events                          = 0x2,
    JournalEntries                  = 0x4,
    Microsoft_Windows_DXGI_Analytic = 0x8000000000000000,
    Microsoft_Windows_DXGI_Logging  = 0x4000000000000000,
};

enum class Level : uint8_t {
    win_LogAlways = 0x0,
};

enum class Channel : uint8_t {
    Microsoft_Windows_DXGI_Analytic = 0x10,
    Microsoft_Windows_DXGI_Logging  = 0x11,
};

// Event descriptors:
#define EVENT_DESCRIPTOR_DECL(name_, id_, version_, channel_, level_, opcode_, task_, keyword_) struct name_ { \
    static uint16_t const Id      = id_; \
    static uint8_t  const Version = version_; \
    static uint8_t  const Channel = channel_; \
    static uint8_t  const Level   = level_; \
    static uint8_t  const Opcode  = opcode_; \
    static uint16_t const Task    = task_; \
    static Keyword  const Keyword = (Keyword) keyword_; \
};

EVENT_DESCRIPTOR_DECL(PresentMultiplaneOverlay_Start, 0x0037, 0x00, 0x10, 0x00, 0x01, 0x000e, 0x8000000000000002)
EVENT_DESCRIPTOR_DECL(PresentMultiplaneOverlay_Stop , 0x0038, 0x00, 0x10, 0x00, 0x02, 0x000e, 0x8000000000000002)
EVENT_DESCRIPTOR_DECL(Present_Start                 , 0x002a, 0x00, 0x10, 0x00, 0x01, 0x0009, 0x8000000000000002)
EVENT_DESCRIPTOR_DECL(Present_Stop                  , 0x002b, 0x00, 0x10, 0x00, 0x02, 0x0009, 0x8000000000000002)
EVENT_DESCRIPTOR_DECL(ResizeBuffers_Start           , 0x002d, 0x00, 0x10, 0x00, 0x01, 0x0005, 0x8000000000000002);
EVENT_DESCRIPTOR_DECL(SwapChain_Start               , 0x000a, 0x00, 0x10, 0x00, 0x01, 0x0002, 0x8000000000000001);

#undef EVENT_DESCRIPTOR_DECL

enum class DXGIPresentFlags : uint32_t {
    DXGI_PRESENT_TEST = 1,
    DXGI_PRESENT_DO_NOT_SEQUENCE = 2,
    DXGI_PRESENT_RESTART = 4,
    DXGI_PRESENT_DO_NOT_WAIT = 8,
    DXGI_PRESENT_STEREO_PREFER_RIGHT = 16,
    DXGI_PRESENT_STEREO_TEMPORARY_MONO = 32,
    DXGI_PRESENT_RESTRICT_TO_OUTPUT = 64,
};

enum class HybridPresentMode : uint32_t {
    NOT_HYBRID = 0,
    TWO_COPY_PATH = 1,
    ONE_COPY_PATH_CASO = 2,
};

}
