// Copyright (C) 2017-2024 Intel Corporation
// SPDX-License-Identifier: MIT
#pragma once
#ifdef PRESENTMONAPI2_EXPORTS
#define PRESENTMON_API2_EXPORT __declspec(dllexport)
#else
#define PRESENTMON_API2_EXPORT __declspec(dllimport)
#endif

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif

	enum PM_STATUS
	{
		PM_STATUS_SUCCESS,
		PM_STATUS_FAILURE,
		PM_STATUS_BAD_ARGUMENT,
		PM_STATUS_BAD_HANDLE,
		PM_STATUS_SERVICE_ERROR,
		PM_STATUS_INVALID_ETL_FILE,
		PM_STATUS_INVALID_PID,
		PM_STATUS_ALREADY_TRACKING_PROCESS,
		PM_STATUS_UNABLE_TO_CREATE_NSM,
		PM_STATUS_INVALID_ADAPTER_ID,
		PM_STATUS_OUT_OF_RANGE,
		PM_STATUS_INSUFFICIENT_BUFFER,
		PM_STATUS_PIPE_ERROR,
		PM_STATUS_SESSION_NOT_OPEN,
		PM_STATUS_MIDDLEWARE_MISSING_PATH,
		PM_STATUS_NONEXISTENT_FILE_PATH,
		PM_STATUS_MIDDLEWARE_INVALID_SIGNATURE,
		PM_STATUS_MIDDLEWARE_MISSING_ENDPOINT,
		PM_STATUS_MIDDLEWARE_VERSION_LOW,
		PM_STATUS_MIDDLEWARE_VERSION_HIGH,
	};

	enum PM_METRIC
	{
		PM_METRIC_APPLICATION,
		PM_METRIC_SWAP_CHAIN_ADDRESS,
		PM_METRIC_GPU_VENDOR,
		PM_METRIC_GPU_NAME,
		PM_METRIC_CPU_VENDOR,
		PM_METRIC_CPU_NAME,
		PM_METRIC_CPU_START_TIME,
		PM_METRIC_CPU_START_QPC,
		PM_METRIC_CPU_FRAME_TIME,
		PM_METRIC_CPU_BUSY,
		PM_METRIC_CPU_WAIT,
		PM_METRIC_DISPLAYED_FPS,
		PM_METRIC_PRESENTED_FPS,
		PM_METRIC_GPU_TIME,
		PM_METRIC_GPU_BUSY,
		PM_METRIC_GPU_WAIT,
		PM_METRIC_DROPPED_FRAMES,
		PM_METRIC_DISPLAYED_TIME,
		PM_METRIC_SYNC_INTERVAL,
		PM_METRIC_PRESENT_FLAGS,
		PM_METRIC_PRESENT_MODE,
		PM_METRIC_PRESENT_RUNTIME,
		PM_METRIC_ALLOWS_TEARING,
		PM_METRIC_GPU_LATENCY,
		PM_METRIC_DISPLAY_LATENCY,
		PM_METRIC_CLICK_TO_PHOTON_LATENCY,
		PM_METRIC_GPU_SUSTAINED_POWER_LIMIT,
		PM_METRIC_GPU_POWER,
		PM_METRIC_GPU_VOLTAGE,
		PM_METRIC_GPU_FREQUENCY,
		PM_METRIC_GPU_TEMPERATURE,
		PM_METRIC_GPU_FAN_SPEED,
		PM_METRIC_GPU_UTILIZATION,
		PM_METRIC_GPU_RENDER_COMPUTE_UTILIZATION,
		PM_METRIC_GPU_MEDIA_UTILIZATION,
		PM_METRIC_GPU_POWER_LIMITED,
		PM_METRIC_GPU_TEMPERATURE_LIMITED,
		PM_METRIC_GPU_CURRENT_LIMITED,
		PM_METRIC_GPU_VOLTAGE_LIMITED,
		PM_METRIC_GPU_UTILIZATION_LIMITED,
		PM_METRIC_GPU_MEM_POWER,
		PM_METRIC_GPU_MEM_VOLTAGE,
		PM_METRIC_GPU_MEM_FREQUENCY,
		PM_METRIC_GPU_MEM_EFFECTIVE_FREQUENCY,
		PM_METRIC_GPU_MEM_TEMPERATURE,
		PM_METRIC_GPU_MEM_SIZE,
		PM_METRIC_GPU_MEM_USED,
		PM_METRIC_GPU_MEM_UTILIZATION,
		PM_METRIC_GPU_MEM_MAX_BANDWIDTH,
		PM_METRIC_GPU_MEM_WRITE_BANDWIDTH,
		PM_METRIC_GPU_MEM_READ_BANDWIDTH,
		PM_METRIC_GPU_MEM_POWER_LIMITED,
		PM_METRIC_GPU_MEM_TEMPERATURE_LIMITED,
		PM_METRIC_GPU_MEM_CURRENT_LIMITED,
		PM_METRIC_GPU_MEM_VOLTAGE_LIMITED,
		PM_METRIC_GPU_MEM_UTILIZATION_LIMITED,
		PM_METRIC_CPU_UTILIZATION,
		PM_METRIC_CPU_POWER_LIMIT,
		PM_METRIC_CPU_POWER,
		PM_METRIC_CPU_TEMPERATURE,
		PM_METRIC_CPU_FREQUENCY,
		PM_METRIC_CPU_CORE_UTILITY,
		PM_METRIC_APPLICATION_FPS,
		PM_METRIC_FRAME_TYPE,
		PM_METRIC_ANIMATION_ERROR,
		PM_METRIC_ALL_INPUT_TO_PHOTON_LATENCY,
		PM_METRIC_INSTRUMENTED_LATENCY,
		PM_METRIC_ANIMATION_TIME,
		PM_METRIC_GPU_EFFECTIVE_FREQUENCY,
		PM_METRIC_GPU_VOLTAGE_REGULATOR_TEMPERATURE,
		PM_METRIC_GPU_MEM_EFFECTIVE_BANDWIDTH,
		PM_METRIC_GPU_OVERVOLTAGE_PERCENT,
		PM_METRIC_GPU_TEMPERATURE_PERCENT,
		PM_METRIC_GPU_POWER_PERCENT,
		PM_METRIC_GPU_FAN_SPEED_PERCENT,
		PM_METRIC_GPU_CARD_POWER,
	};

	enum PM_METRIC_TYPE
	{
		PM_METRIC_TYPE_DYNAMIC,
		PM_METRIC_TYPE_STATIC,
		PM_METRIC_TYPE_FRAME_EVENT,
		PM_METRIC_TYPE_DYNAMIC_FRAME,
	};

	enum PM_DEVICE_VENDOR
	{
		PM_DEVICE_VENDOR_INTEL,
		PM_DEVICE_VENDOR_NVIDIA,
		PM_DEVICE_VENDOR_AMD,
		PM_DEVICE_VENDOR_UNKNOWN
	};

	enum PM_PRESENT_MODE
	{
		PM_PRESENT_MODE_UNKNOWN,
		PM_PRESENT_MODE_HARDWARE_LEGACY_FLIP,
		PM_PRESENT_MODE_HARDWARE_LEGACY_COPY_TO_FRONT_BUFFER,
		PM_PRESENT_MODE_HARDWARE_INDEPENDENT_FLIP,
		PM_PRESENT_MODE_COMPOSED_FLIP,
		PM_PRESENT_MODE_COMPOSED_COPY_WITH_GPU_GDI,
		PM_PRESENT_MODE_COMPOSED_COPY_WITH_CPU_GDI,
		PM_PRESENT_MODE_HARDWARE_COMPOSED_INDEPENDENT_FLIP=8,
	};

	enum PM_UNIT
	{
		PM_UNIT_DIMENSIONLESS,
		PM_UNIT_RATIO,
		PM_UNIT_BOOLEAN,
		PM_UNIT_PERCENT,
		PM_UNIT_FPS,
		PM_UNIT_MICROSECONDS,
		PM_UNIT_MILLISECONDS,
		PM_UNIT_SECONDS,
		PM_UNIT_MINUTES,
		PM_UNIT_HOURS,
		PM_UNIT_MILLIWATTS,
		PM_UNIT_WATTS,
		PM_UNIT_KILOWATTS,
		PM_UNIT_VERTICAL_BLANKS,
		PM_UNIT_MILLIVOLTS,
		PM_UNIT_VOLTS,
		PM_UNIT_HERTZ,
		PM_UNIT_KILOHERTZ,
		PM_UNIT_MEGAHERTZ,
		PM_UNIT_GIGAHERTZ,
		PM_UNIT_CELSIUS,
		PM_UNIT_RPM,
		PM_UNIT_BITS_PER_SECOND,
		PM_UNIT_KILOBITS_PER_SECOND,
		PM_UNIT_MEGABITS_PER_SECOND,
		PM_UNIT_GIGABITS_PER_SECOND,
		PM_UNIT_BYTES,
		PM_UNIT_KILOBYTES,
		PM_UNIT_MEGABYTES,
		PM_UNIT_GIGABYTES,
		PM_UNIT_QPC,
	};

	enum PM_STAT
	{
		PM_STAT_NONE,
		PM_STAT_AVG,
		PM_STAT_PERCENTILE_99,
		PM_STAT_PERCENTILE_95,
		PM_STAT_PERCENTILE_90,
		PM_STAT_PERCENTILE_01,
		PM_STAT_PERCENTILE_05,
		PM_STAT_PERCENTILE_10,
		PM_STAT_MAX,
		PM_STAT_MIN,
		PM_STAT_MID_POINT,
		PM_STAT_MID_LERP,
		PM_STAT_NEWEST_POINT,
		PM_STAT_OLDEST_POINT,
		PM_STAT_COUNT,
		PM_STAT_NON_ZERO_AVG,
	};

	enum PM_DATA_TYPE
	{
		PM_DATA_TYPE_DOUBLE,
		PM_DATA_TYPE_INT32,
		PM_DATA_TYPE_UINT32,
		PM_DATA_TYPE_ENUM,
		PM_DATA_TYPE_STRING,
		PM_DATA_TYPE_UINT64,
		PM_DATA_TYPE_BOOL,
		PM_DATA_TYPE_VOID,
	};

	enum PM_GRAPHICS_RUNTIME
	{
		PM_GRAPHICS_RUNTIME_UNKNOWN,
		PM_GRAPHICS_RUNTIME_DXGI,
		PM_GRAPHICS_RUNTIME_D3D9,
	};

	enum PM_FRAME_TYPE
	{
		PM_FRAME_TYPE_NOT_SET,
		PM_FRAME_TYPE_UNSPECIFIED,
		PM_FRAME_TYPE_APPLICATION,
		PM_FRAME_TYPE_REPEATED,
		PM_FRAME_TYPE_INTEL_XEFG = 50,
		PM_FRAME_TYPE_AMD_AFMF = 100,
	};

	enum PM_DEVICE_TYPE
	{
		PM_DEVICE_TYPE_INDEPENDENT,
		PM_DEVICE_TYPE_GRAPHICS_ADAPTER,
	};

	enum PM_METRIC_AVAILABILITY
	{
		PM_METRIC_AVAILABILITY_AVAILABLE,
		PM_METRIC_AVAILABILITY_UNAVAILABLE,
	};

	// this is required but has no external use
	enum PM_NULL_ENUM {};

	enum PM_ENUM
	{
		PM_ENUM_STATUS,
		PM_ENUM_METRIC,
		PM_ENUM_METRIC_TYPE,
		PM_ENUM_DEVICE_VENDOR,
		PM_ENUM_PRESENT_MODE,
		PM_ENUM_UNIT,
		PM_ENUM_STAT,
		PM_ENUM_DATA_TYPE,
		PM_ENUM_GRAPHICS_RUNTIME,
		PM_ENUM_FRAME_TYPE,
		PM_ENUM_DEVICE_TYPE,
		PM_ENUM_METRIC_AVAILABILITY,
		PM_ENUM_NULL_ENUM,
	};

	struct PM_INTROSPECTION_STRING
	{
		const char* pData;
	};

	struct PM_INTROSPECTION_OBJARRAY
	{
		const void** pData;
		size_t size;
	};

	struct PM_INTROSPECTION_ENUM_KEY
	{
		PM_ENUM enumId;
		int id;
		PM_INTROSPECTION_STRING* pSymbol;
		PM_INTROSPECTION_STRING* pName;
		PM_INTROSPECTION_STRING* pShortName;
		PM_INTROSPECTION_STRING* pDescription;
	};

	struct PM_INTROSPECTION_ENUM
	{
		PM_ENUM id;
		PM_INTROSPECTION_STRING* pSymbol;
		PM_INTROSPECTION_STRING* pDescription;
		PM_INTROSPECTION_OBJARRAY* pKeys;
	};

	struct PM_INTROSPECTION_DEVICE
	{
		uint32_t id;
		PM_DEVICE_TYPE type;
		PM_DEVICE_VENDOR vendor;
		PM_INTROSPECTION_STRING* pName;
	};

	struct PM_INTROSPECTION_DEVICE_METRIC_INFO
	{
		uint32_t deviceId;
		PM_METRIC_AVAILABILITY availability;
		uint32_t arraySize;
	};

	struct PM_INTROSPECTION_DATA_TYPE_INFO
	{
		PM_DATA_TYPE polledType;
		PM_DATA_TYPE frameType;
		PM_ENUM enumId;
	};

	struct PM_INTROSPECTION_STAT_INFO
	{
		PM_STAT stat;
	};

	struct PM_INTROSPECTION_METRIC
	{
		PM_METRIC id;
		PM_METRIC_TYPE type;
		PM_UNIT unit;
		PM_UNIT preferredUnitHint;
		PM_INTROSPECTION_DATA_TYPE_INFO* pTypeInfo;
		PM_INTROSPECTION_OBJARRAY* pStatInfo;
		PM_INTROSPECTION_OBJARRAY* pDeviceMetricInfo;
	};

	struct PM_INTROSPECTION_UNIT
	{
		PM_UNIT id;
		PM_UNIT baseUnitId;
		double scale;
	};

	struct PM_INTROSPECTION_ROOT
	{
		PM_INTROSPECTION_OBJARRAY* pMetrics;
		PM_INTROSPECTION_OBJARRAY* pEnums;
		PM_INTROSPECTION_OBJARRAY* pDevices;
		PM_INTROSPECTION_OBJARRAY* pUnits;
	};

	struct PM_QUERY_ELEMENT
	{
		PM_METRIC metric;
		PM_STAT stat;
		uint32_t deviceId;
		uint32_t arrayIndex;
		uint64_t dataOffset;
		uint64_t dataSize;
	};

	struct PM_VERSION
	{
		uint16_t major;
		uint16_t minor;
		uint16_t patch;
		char tag[26];
		char hash[8];
	};

	typedef struct PM_DYNAMIC_QUERY* PM_DYNAMIC_QUERY_HANDLE;
	typedef struct PM_FRAME_QUERY* PM_FRAME_QUERY_HANDLE;
	typedef struct PM_SESSION* PM_SESSION_HANDLE;

	// open a session (connection) to the PresentMon service, outputting a session handle required for most other API calls
	PRESENTMON_API2_EXPORT PM_STATUS pmOpenSession(PM_SESSION_HANDLE* pHandle);
	// open a session (connection) to the PresentMon service using a pipe name other than the default one
	PRESENTMON_API2_EXPORT PM_STATUS pmOpenSessionWithPipe(PM_SESSION_HANDLE* pHandle, const char* controlPipeName);
	// close an existing session by handle, deallocating all associated resources
	PRESENTMON_API2_EXPORT PM_STATUS pmCloseSession(PM_SESSION_HANDLE handle);
	// command the service to process and make available frame/metric data for the specified process id
	PRESENTMON_API2_EXPORT PM_STATUS pmStartTrackingProcess(PM_SESSION_HANDLE handle, uint32_t process_id);
	// command the service to cease processing and exporting frame/metric data for the specified process id
	PRESENTMON_API2_EXPORT PM_STATUS pmStopTrackingProcess(PM_SESSION_HANDLE handle, uint32_t process_id);
	// allocate and populate a tree data structure describing the available metrics, devices, etc.
	PRESENTMON_API2_EXPORT PM_STATUS pmGetIntrospectionRoot(PM_SESSION_HANDLE handle, const PM_INTROSPECTION_ROOT** ppRoot);
	// free the introspection tree structure
	PRESENTMON_API2_EXPORT PM_STATUS pmFreeIntrospectionRoot(const PM_INTROSPECTION_ROOT* pRoot);
	// sets the rate at which hardware telemetry (including CPU) is polled on a per-device basis
	PRESENTMON_API2_EXPORT PM_STATUS pmSetTelemetryPollingPeriod(PM_SESSION_HANDLE handle, uint32_t deviceId, uint32_t timeMs);
	// sets the rate at which ETW event buffers are flushed, affecting the delay of frame data reported by PresentMon
	PRESENTMON_API2_EXPORT PM_STATUS pmSetEtwFlushPeriod(PM_SESSION_HANDLE handle, uint32_t periodMs);
	// register a dynamic query used for polling metric data with (optional) statistic processing such as average or percentile
	PRESENTMON_API2_EXPORT PM_STATUS pmRegisterDynamicQuery(PM_SESSION_HANDLE sessionHandle, PM_DYNAMIC_QUERY_HANDLE* pHandle, PM_QUERY_ELEMENT* pElements, uint64_t numElements, double windowSizeMs, double metricOffsetMs);
	// free the resources associated with a registered dynamic query
	PRESENTMON_API2_EXPORT PM_STATUS pmFreeDynamicQuery(PM_DYNAMIC_QUERY_HANDLE handle);
	// poll a dynamic query, writing the query poll results into the specified memory blob (byte buffer)
	PRESENTMON_API2_EXPORT PM_STATUS pmPollDynamicQuery(PM_DYNAMIC_QUERY_HANDLE handle, uint32_t processId, uint8_t* pBlob, uint32_t* numSwapChains);
	// query a static metric immediately, writing the result into the specified memory blob (byte buffer)
	PRESENTMON_API2_EXPORT PM_STATUS pmPollStaticQuery(PM_SESSION_HANDLE sessionHandle, const PM_QUERY_ELEMENT* pElement, uint32_t processId, uint8_t* pBlob);
	// register a frame query used for consuming desired metrics from a queue of frame events
	PRESENTMON_API2_EXPORT PM_STATUS pmRegisterFrameQuery(PM_SESSION_HANDLE sessionHandle, PM_FRAME_QUERY_HANDLE* pHandle, PM_QUERY_ELEMENT* pElements, uint64_t numElements, uint32_t* pBlobSize);
	// consume frame event metric data based on the filter registered with pmRegisterFrameQuery
	PRESENTMON_API2_EXPORT PM_STATUS pmConsumeFrames(PM_FRAME_QUERY_HANDLE handle, uint32_t processId, uint8_t* pBlobs, uint32_t* pNumFramesToRead);
	// free the resources associated with a frame event query
	PRESENTMON_API2_EXPORT PM_STATUS pmFreeFrameQuery(PM_FRAME_QUERY_HANDLE handle);
	// retrieve the API version of the PresentMon service / middleware DLL
	PRESENTMON_API2_EXPORT PM_STATUS pmGetApiVersion(PM_VERSION* pVersion);

#ifdef __cplusplus
} // extern "C"
#endif
