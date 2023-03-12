#include <feature/aimbot.hh>
#include <internals/logging/macro.hh>
#include <sstream>
#include <vector>
#include <chrono>
#include <sdk/byond.hh>
#include <misc/keyhelper.hh>

namespace syndicate::feature::aimbot
{
	functional::Procedure<bool(__stdcall)(sdk::MouseParams*)> tp_GenClickCommand;
	bool __stdcall hk_GenClickCommand(sdk::MouseParams* params)
	{
		if (misc::isKeyDown(VK_XBUTTON2))
		{
			sdk::Cid localPlayer{ sdk::Cid::getLocalPlayer() };
			sdk::Cid hitCid{ params->getCid() };

			if (hitCid.getType() != sdk::Cid::typeMob || hitCid == localPlayer)
			{
				sdk::Cid closestCid;

				for (sdk::Cid cid : sdk::Cid::availableCids(sdk::Cid::typeMob))
				{
					if (cid.getID() == localPlayer.getID())
						continue;
						
					uint32_t curDistance{ params->getWorldTile().sqrDistance(closestCid.getPos()) };
					uint32_t newDistance{ params->getWorldTile().sqrDistance(cid.getPos()) };

					if (!closestCid || newDistance < curDistance)
						closestCid = cid;

				}

				if (closestCid)
				{
					static sdk::MouseParams aimbotParams;
					aimbotParams = sdk::MouseParams(closestCid);

					LOG_INFO("Aimbot targetting " << dye::red(closestCid.getName()));


					return tp_GenClickCommand(&aimbotParams);
				}

			}

		}
		else if (misc::isKeyDown(VK_XBUTTON1))
		{
			static sdk::MouseParams playerParams;
			playerParams = sdk::MouseParams(sdk::Cid::getLocalPlayer());

			if (!misc::isKeyDown(VK_SHIFT))
				return sdk::byond::GenMouseDropCommand(params, &playerParams);

			return sdk::byond::GenMouseDropCommand(&playerParams, params);
		}

		return tp_GenClickCommand(params);
	}

	bool init()
	{
		tp_GenClickCommand = sdk::byond::GenClickCommand.detourTo(hk_GenClickCommand);

		return tp_GenClickCommand;
	}

}