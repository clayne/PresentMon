#pragma once
#include "../Core/source/infra/opt/Framework.h"
#include <string>
#include <vector>

namespace pmon::ipc::mock::opt
{
	namespace impl
	{
		using namespace p2c::infra::opt::impl;
		struct OptionsStruct : public OptionStructBase_
		{
			// add options and switches here to augment the CLI
			Flag testF{ "--test-f", "Output test string from test function f() in ipc lib" };
			Flag basicMessage{ "--basic-message", "Do minimal IPC test transferring string across shared memory" };
			Flag destroyUptr{ "--destroy-uptr", "Test which destroys the uptr that is constructed by default" };
			Flag makeDestroyUptr{ "--make-destroy-uptr", "Test which makes and destroys the uptr such that leaks can be detected" };
			Flag sharedRootBasic{ "--shared-root-basic", "Basic test of creating root in shared memory" };

		protected:
			// edit application name and description here
			std::string GetName() const override
			{
				return "Interprocess Mock";
			}
			std::string GetDescription() const override
			{
				return "Application to mock interprocess communication endpoints for testing";
			}
		};
	}

	inline void init(int argc, char** argv) { impl::App<impl::OptionsStruct>::Init(argc, argv); }
	inline auto& get() { return impl::App<impl::OptionsStruct>::GetOptions(); }
}