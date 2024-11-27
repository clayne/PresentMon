#pragma once
#include "../IntelPresentMon/CommonUtilities/cli/CliFramework.h"
#include <ranges>

namespace clio
{
	using namespace pmon::util::cli;
	struct Options : public OptionsBase<Options>
	{
	private: Group gf_{ this, "Files", "Input and output file paths" }; public:
		Option<std::string> inputFile{ this, "--input-file", "", "Path to input file to use", [this](CLI::Option* pOpt) {
			pOpt->required();
		} };
		Option<std::string> outputFile{ this, "--output-file", "", "Path for the trimmed output file. Omitting this enables analysis-only mode" };

	private: Group gt_{ this, "Trimming", "Options for trimming and pruning events" }; public:
		Flag provider{ this, "--provider,-p", "Enable pruning by provider (uses same provider set as PresentMon)" };
		Flag event{ this, "--event,-e", "Enable pruning by event (uses same event set as PresentMon)" };
		Flag trimState{ this, "--trim-state,-s", "Override default behavior that avoids discarding stateful events like process and DC start/stop when trimming by timestamp range" };
		Option<std::pair<uint64_t, uint64_t>> trimRange{ this, "--trim-range", {}, "Range of timestamps outside of which to trim" };

		static constexpr const char* description = "Postprocessing tool for trimming and pruning ETL files";
		static constexpr const char* name = "ETLTrimmer.exe";
	private:
		Dependency eventDep_{ event, provider };
		Dependency noTrimDep_{ trimState, trimRange };
	};
}