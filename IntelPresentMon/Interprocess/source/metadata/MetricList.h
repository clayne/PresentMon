// Copyright (C) 2017-2024 Intel Corporation
// SPDX-License-Identifier: MIT
#pragma once
#include "../../../PresentMonAPI2/PresentMonAPI.h"
#include "StatsShortcuts.h"

#define METRIC_LIST(X_) \
		X_(PM_METRIC_APPLICATION, PM_METRIC_TYPE_STATIC, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_STRING, PM_DATA_TYPE_STRING, 0, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_NONE) \
		X_(PM_METRIC_SWAP_CHAIN_ADDRESS, PM_METRIC_TYPE_FRAME_EVENT, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_UINT64, PM_DATA_TYPE_UINT64, 0, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_MID_POINT) \
\
		X_(PM_METRIC_GPU_VENDOR, PM_METRIC_TYPE_STATIC, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_ENUM, PM_DATA_TYPE_ENUM, PM_ENUM_DEVICE_VENDOR, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, PM_STAT_NONE) \
		X_(PM_METRIC_GPU_NAME, PM_METRIC_TYPE_STATIC, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_STRING, PM_DATA_TYPE_STRING, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, PM_STAT_NONE) \
		X_(PM_METRIC_CPU_VENDOR, PM_METRIC_TYPE_STATIC, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_ENUM, PM_DATA_TYPE_ENUM, PM_ENUM_DEVICE_VENDOR, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_NONE) \
		X_(PM_METRIC_CPU_NAME, PM_METRIC_TYPE_STATIC, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_STRING, PM_DATA_TYPE_STRING, 0, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_NONE) \
\
		X_(PM_METRIC_CPU_START_TIME, PM_METRIC_TYPE_FRAME_EVENT, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_VOID, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_NONE) \
		X_(PM_METRIC_CPU_START_QPC, PM_METRIC_TYPE_FRAME_EVENT, PM_UNIT_QPC, PM_DATA_TYPE_UINT64, PM_DATA_TYPE_UINT64, 0, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_NONE) \
		X_(PM_METRIC_CPU_FRAME_TIME, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_CPU_BUSY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_CPU_WAIT, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
\
		X_(PM_METRIC_DISPLAYED_FPS, PM_METRIC_TYPE_DYNAMIC, PM_UNIT_FPS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_VOID, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_APPLICATION_FPS, PM_METRIC_TYPE_DYNAMIC, PM_UNIT_FPS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_VOID, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_PRESENTED_FPS, PM_METRIC_TYPE_DYNAMIC, PM_UNIT_FPS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_VOID, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
\
		X_(PM_METRIC_GPU_TIME, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_GPU_BUSY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_GPU_WAIT, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
\
		X_(PM_METRIC_DROPPED_FRAMES, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
\
		X_(PM_METRIC_DISPLAYED_TIME, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_ANIMATION_ERROR, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
        X_(PM_METRIC_ANIMATION_TIME, PM_METRIC_TYPE_FRAME_EVENT, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_NONE) \
\
		X_(PM_METRIC_SYNC_INTERVAL, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_VERTICAL_BLANKS, PM_DATA_TYPE_INT32, PM_DATA_TYPE_INT32, 0, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_MID_POINT) \
		X_(PM_METRIC_PRESENT_FLAGS, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_UINT32, PM_DATA_TYPE_UINT32, 0, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_MID_POINT) \
		X_(PM_METRIC_PRESENT_MODE, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_ENUM, PM_DATA_TYPE_ENUM, PM_ENUM_PRESENT_MODE, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_MID_POINT) \
		X_(PM_METRIC_PRESENT_RUNTIME, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_ENUM, PM_DATA_TYPE_ENUM, PM_ENUM_GRAPHICS_RUNTIME, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_MID_POINT) \
		X_(PM_METRIC_ALLOWS_TEARING, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_FRAME_TYPE, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_DIMENSIONLESS, PM_DATA_TYPE_ENUM, PM_DATA_TYPE_ENUM, PM_ENUM_FRAME_TYPE, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_NONE) \
\
		X_(PM_METRIC_GPU_LATENCY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_DISPLAY_LATENCY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_CLICK_TO_PHOTON_LATENCY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_NON_ZERO_AVG, PM_STAT_PERCENTILE_01, PM_STAT_PERCENTILE_05, PM_STAT_PERCENTILE_10, PM_STAT_MAX) \
\
		X_(PM_METRIC_GPU_SUSTAINED_POWER_LIMIT, PM_METRIC_TYPE_STATIC, PM_UNIT_WATTS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, PM_STAT_NONE) \
		X_(PM_METRIC_GPU_POWER, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_WATTS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_VOLTAGE, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_VOLTS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_FREQUENCY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MEGAHERTZ, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_TEMPERATURE, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_CELSIUS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_FAN_SPEED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_RPM, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_UTILIZATION, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_PERCENT, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_RENDER_COMPUTE_UTILIZATION, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_PERCENT, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEDIA_UTILIZATION, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_PERCENT, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
\
		X_(PM_METRIC_GPU_POWER_LIMITED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BOOLEAN, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_TEMPERATURE_LIMITED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BOOLEAN, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_CURRENT_LIMITED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BOOLEAN, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_VOLTAGE_LIMITED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BOOLEAN, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_UTILIZATION_LIMITED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BOOLEAN, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
\
		X_(PM_METRIC_GPU_MEM_POWER, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_WATTS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_VOLTAGE, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_VOLTS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_FREQUENCY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MEGAHERTZ, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_EFFECTIVE_FREQUENCY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MEGAHERTZ, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_TEMPERATURE, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_CELSIUS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
\
		X_(PM_METRIC_GPU_MEM_SIZE, PM_METRIC_TYPE_STATIC, PM_UNIT_BYTES, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_UINT64, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, PM_STAT_NONE) \
		X_(PM_METRIC_GPU_MEM_USED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BYTES, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_UINT64, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_UTILIZATION, PM_METRIC_TYPE_DYNAMIC, PM_UNIT_PERCENT, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_VOID, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_MAX_BANDWIDTH, PM_METRIC_TYPE_STATIC, PM_UNIT_BITS_PER_SECOND, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_UINT64, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, PM_STAT_NONE) \
		X_(PM_METRIC_GPU_MEM_WRITE_BANDWIDTH, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BITS_PER_SECOND, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_READ_BANDWIDTH, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BITS_PER_SECOND, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
\
		X_(PM_METRIC_GPU_MEM_POWER_LIMITED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BOOLEAN, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_TEMPERATURE_LIMITED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BOOLEAN, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_CURRENT_LIMITED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BOOLEAN, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_VOLTAGE_LIMITED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BOOLEAN, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_UTILIZATION_LIMITED, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_BOOLEAN, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_BOOL, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
\
		X_(PM_METRIC_CPU_UTILIZATION, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_PERCENT, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_CPU_POWER_LIMIT, PM_METRIC_TYPE_STATIC, PM_UNIT_WATTS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, PM_STAT_MID_POINT) \
		X_(PM_METRIC_CPU_POWER, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_WATTS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_CPU_TEMPERATURE, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_CELSIUS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_CPU_FREQUENCY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MEGAHERTZ, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_CPU_CORE_UTILITY, PM_METRIC_TYPE_DYNAMIC, PM_UNIT_PERCENT, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_VOID, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_ALL_INPUT_TO_PHOTON_LATENCY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, PM_STAT_NON_ZERO_AVG, PM_STAT_PERCENTILE_01, PM_STAT_PERCENTILE_05, PM_STAT_PERCENTILE_10, PM_STAT_MAX) \
\
        X_(PM_METRIC_INSTRUMENTED_LATENCY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MILLISECONDS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_INDEPENDENT, FULL_STATS) \
		X_(PM_METRIC_GPU_EFFECTIVE_FREQUENCY, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_MEGAHERTZ, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_VOLTAGE_REGULATOR_TEMPERATURE, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_CELSIUS, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_MEM_EFFECTIVE_BANDWIDTH, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_GIGABITS_PER_SECOND, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_OVERVOLTAGE_PERCENT, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_PERCENT, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_TEMPERATURE_PERCENT, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_PERCENT, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_POWER_PERCENT, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_PERCENT, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS) \
		X_(PM_METRIC_GPU_FAN_SPEED_PERCENT, PM_METRIC_TYPE_DYNAMIC_FRAME, PM_UNIT_PERCENT, PM_DATA_TYPE_DOUBLE, PM_DATA_TYPE_DOUBLE, 0, PM_DEVICE_TYPE_GRAPHICS_ADAPTER, FULL_STATS)