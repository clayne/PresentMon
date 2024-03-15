#include "MsvcDebugDriver.h"
#include "ITextFormatter.h"
#include "../win/WinAPI.h"

namespace pmon::util::log
{
	MsvcDebugDriver::MsvcDebugDriver(std::shared_ptr<ITextFormatter> pFormatter)
		:
		pFormatter_{ std::move(pFormatter) }
	{}
	void MsvcDebugDriver::Submit(const Entry& e)
	{
		if (pFormatter_) {
			OutputDebugStringW(pFormatter_->Format(e).c_str());
		}
		// TODO: how to log stuff from log system itself?
	}
	void MsvcDebugDriver::SetFormatter(std::shared_ptr<ITextFormatter> pFormatter)
	{
		pFormatter_ = std::move(pFormatter);
	}
	void MsvcDebugDriver::Flush() {}
}