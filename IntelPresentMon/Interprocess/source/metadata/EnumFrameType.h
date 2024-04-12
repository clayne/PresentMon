#pragma once
#include "../../../PresentMonAPI2/PresentMonAPI.h"

// enum annotation (enum_name_fragment, key_name_fragment, name, short_name, description)
#define ENUM_KEY_LIST_FRAME_TYPE(X_) \
		X_(FRAME_TYPE, NOT_SET, "Application", "", "Frame rendered by the target application") \
		X_(FRAME_TYPE, UNSPECIFIED, "Unspecified", "", "Frame rendered by unspecified technique") \
		X_(FRAME_TYPE, APPLICATION, "Application", "", "Frame rendered by the target application") \
		X_(FRAME_TYPE, REPEATED, "Application", "", "Frame rendered by the taget application") \
		X_(FRAME_TYPE, INTEL_XEFG, "Intel XEFG", "", "Frame generated by Intel XEFG") \
		X_(FRAME_TYPE, AMD_AFMF, "AMD_AFMF", "", "Frame generated by AMD Fluid Motion Frames")
