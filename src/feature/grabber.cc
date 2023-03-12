#include <feature/grabber.hh>
#include <internals/logging/macro.hh>
#include <vector>
#include <sdk/byond.hh>

namespace syndicate::feature::grabber
{
	std::vector<sdk::Cid> getNearObjects()
	{
		sdk::Cid localPlayer{ sdk::Cid::getLocalPlayer() };
		std::vector<sdk::Cid> cids{ sdk::Cid::availableCids(sdk::Cid::typeObject, 8196, 262144) };
		cids.erase(std::remove_if(cids.begin(), cids.end(), [&](sdk::Cid cid) { return localPlayer.getPos().sqrDistance(cid.getPos()) > 2; }), cids.end());

		return cids;
	}

	bool grabWhitelisted()
	{
		std::vector<sdk::Cid> cids{ getNearObjects() };

		for (sdk::Cid nearCid : cids)
		{
			uint32_t nearHash{ misc::const_hash(nearCid.getName()) };
			for (uint32_t hash : grab_hash)
			{
				if (nearHash == hash)
				{
					sdk::MouseParams nearParams(nearCid);
					sdk::byond::GenClickCommand(&nearParams);
					LOG_INFO("Grabbing " << dye::grey("hashed ") << dye::aqua(nearCid.getName()));
					return true;
				}

			}

			for (const char* keyword : grab_keywords)
			{
				if (strstr(nearCid.getName(), keyword))
				{
					sdk::MouseParams nearParams(nearCid);
					sdk::byond::GenClickCommand(&nearParams);
					LOG_INFO("Grabbing " << dye::grey("keyworded ") << dye::aqua(nearCid.getName()));
					return true;
				}
			}

		}

		return false;
	}


	HANDLE hGrabThread;
	bool shouldRunGrab{ false };

	DWORD WINAPI grabThread(LPVOID param)
	{
		sdk::Cid localPlayer{ sdk::Cid::getLocalPlayer() };
		std::vector<sdk::Cid> oldCids{ getNearObjects() };
		sdk::Coords oldPos{ localPlayer.getPos() };

		while (shouldRunGrab)
		{
			Sleep(25);

			std::vector<sdk::Cid> cids{ getNearObjects() };
			sdk::Coords pos{ localPlayer.getPos() };

			if (oldPos.sqrDistance(pos) > 0)
			{
				oldCids = cids;
				oldPos = pos;
				continue;
			}

			if (oldCids.size() == cids.size())
				continue;

			for (sdk::Cid& cid : cids)
			{
				bool found{ false };
				for (sdk::Cid& oldCid : oldCids)
				{
					if (cid == oldCid)
					{
						found = true;
						break;
					}
				}

				if (!found)
				{
					sdk::MouseParams nearParams(cid);
					sdk::byond::GenClickCommand(&nearParams);
					LOG_INFO("Grabbing " << dye::grey("dropped ") << dye::aqua(cid.getName()));

					shouldRunGrab = false;
					CloseHandle(hGrabThread);
					break;
				}
			}

			oldCids = cids;
		}

		return 0;
	}

	void grabThreaded(bool enabled)
	{
		if (shouldRunGrab == enabled)
			return;

		if (!enabled)
		{
			shouldRunGrab = false;
			WaitForSingleObject(hGrabThread, INFINITE);
			CloseHandle(hGrabThread);
		}
		else
		{
			shouldRunGrab = true;
			hGrabThread = CreateThread(NULL, 0, grabThread, NULL, 0, NULL);
		}

	}

}