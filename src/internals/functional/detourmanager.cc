#include <internals/functional/detourmanager.hh>
#include <MinHook.h>

namespace syndicate::functional
{
	bool DetourManager::setup(bool init)
	{
		return (init ? MH_Initialize() : MH_Uninitialize()) == MH_OK;
	}

	void* DetourManager::create(void* target, void* callback, bool enable)
	{
		void* trampoline;

		if (MH_CreateHook(target, callback, &trampoline) == MH_OK)
		{
			enabled(target, enable);
			return trampoline;
		}

		return nullptr;
	}

	bool DetourManager::remove(void* target)
	{
		return MH_RemoveHook(target) == MH_OK;
	}

	bool DetourManager::enabled(void* target, bool enable)
	{
		return (enable ? MH_EnableHook(target) : MH_DisableHook(target)) == MH_OK;
	}

}