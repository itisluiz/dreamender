#include <feature/byondmember.hh>
#include <internals/logging/macro.hh>

namespace syndicate::feature::byondmember
{
	bool __stdcall hk_IsByondMember(void* visa)
	{
		LOG_DEBUG("hk_IsByondMember called");
		return true;
	}

	bool init()
	{
		auto proc_client_IsByondMember{ functional::Procedure<decltype(hk_IsByondMember)>::fromExport("byondcore.dll", "?IsByondMember@DungClient@@QAE_NPAJ@Z") };
		auto proc_pager_IsByondMember{ functional::Procedure<decltype(hk_IsByondMember)>::fromExport("byondcore.dll", "?IsByondMember@DungPager@@QAE_NPAJ@Z") };

		return proc_client_IsByondMember.detourTo(hk_IsByondMember) && proc_pager_IsByondMember.detourTo(hk_IsByondMember);
	}

}