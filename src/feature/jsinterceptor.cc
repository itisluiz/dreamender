#include <feature/jsinterceptor.hh>
#include <internals/logging/macro.hh>
#include <sdk/byond.hh>
#include <misc/keyhelper.hh>
#include <algorithm>

namespace syndicate::feature::jsinterceptor
{
	functional::Procedure<void(__fastcall)(void*, void*, void*, void*)> tp_OnDocumentCompleteBrowser;
	void __fastcall hk_OnDocumentCompleteBrowser(void* htmlctrl, void* edx, void* dispatch, void* variant)
	{
		tp_OnDocumentCompleteBrowser(htmlctrl, edx, dispatch, variant);
		sdk::byond::InvokeScript(htmlctrl, edx, 
#			include<feature/js/autopickpocket.js>
#			include<feature/js/autogenetics.js>
			, nullptr);
	}

	bool init()
	{
		tp_OnDocumentCompleteBrowser = sdk::byond::OnDocumentCompleteBrowser.detourTo(hk_OnDocumentCompleteBrowser);

		return tp_OnDocumentCompleteBrowser;
	}

}