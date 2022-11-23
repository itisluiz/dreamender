#include <feature/computerid.hh>
#include <internals/logging/macro.hh>

namespace syndicate::feature::computerid
{
	static uint32_t computerid;

	BOOL __stdcall hk_GetVersionExW(LPOSVERSIONINFOW lpVersionInformation)
	{
		LOG_DEBUG("hk_GetVersionExW called");
		lpVersionInformation->dwPlatformId = 0;
		return FALSE;
	}

	BOOL __stdcall hk_GetVolumeInformationA(LPCSTR lpRootPathName, LPSTR lpVolumeNameBuffer, DWORD nVolumeNameSize, LPDWORD lpVolumeSerialNumber, LPDWORD lpMaximumComponentLength, LPDWORD lpFileSystemFlags, LPSTR lpFileSystemNameBuffer, DWORD nFileSystemNameSize)
	{
		LOG_DEBUG("hk_GetVolumeInformationA called");
		*lpVolumeSerialNumber = computerid;
		return TRUE;
	}

	bool init(uint32_t id)
	{
		computerid = id;

		auto proc_GetVersionExW{ functional::Procedure(GetVersionExW) };
		auto proc_GetVolumeInformationA{ functional::Procedure(GetVolumeInformationA) };


		return proc_GetVersionExW.detourTo(hk_GetVersionExW) && proc_GetVolumeInformationA.detourTo(hk_GetVolumeInformationA);
	}

}