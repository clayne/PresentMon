#pragma once
#include "../CommonUtilities/cli/CliFramework.h"
#include "../CommonUtilities/log/Level.h"

namespace clio
{
	using namespace pmon::util::cli;
	using namespace pmon::util::log;
	using namespace std::literals;
	struct Options : public OptionsBase<Options>
	{
		Option<std::string> exeName{ this, "--exe-name", "", "Name of the .exe module to target processes of" };
		Option<std::string> logFile{ this, "--log-file", "", "Path to file to output log entries to" };
		Flag waitForUserInput{ this, "--wait-for-user-input", "Display a pop-up to wait for user input" };
		Option<float> barSize{ this, "--bar-size", .25f, "Size of the flashing bar" };
		Option<float> barRightShift{ this, "--bar-right-shift", .5f, "Distance to offset the bar to the right" };
		Option<std::string> barColor{ this, "--bar-color", "white"s, "Color of the bar. Select from: 'white', 'back', 'magenta'" };
		Flag renderBackground{ this, "--render-background", "Always display a black background for the bar" };

		static constexpr const char* description = "Helper utility for drawing a rectangular flash within a target process via injection";
		static constexpr const char* name = "FlashInjector.exe";
	};
}