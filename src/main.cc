#include <main.hh>
#include <Windows.h>
#include <internals/winapi.hh>
#include <internals/logging/macro.hh>
#include <sdk/byond.hh>
#include <feature/byondmember.hh>
#include <feature/computerid.hh>
#include <feature/xray.hh>
#include <feature/aimbot.hh>
#include <feature/bind.hh>
#include <misc/keyhelper.hh>
#include <misc/configreader.hh>

namespace syndicate
{
	void setupFeatures()
	{
		if (!misc::createCfgIfNotExists())
			LOG_ERROR("Failed to create / open config file");

		uint32_t cfg_computerid{ misc::readConfig<uint32_t>("spoofing", "computer_id") };
		bool cfg_byondmember{ misc::readConfig<bool>("spoofing", "byondmember") };

		sdk::byond::init();

		if (cfg_byondmember)
		{
			LOG_INFO("Byond membership spoof: " << dye::light_green("Enabled"));
			feature::byondmember::init();
		}
		else
			LOG_INFO("Byond membership spoof: " << dye::grey("Disabled"));

		if (cfg_computerid)
		{
			LOG_INFO("Computer ID spoof: " << dye::light_green(cfg_computerid));
			feature::computerid::init(cfg_computerid);
		}
		else
			LOG_INFO("Computer ID spoof: " << dye::grey("Disabled"));

		feature::aimbot::init();
		feature::bind::init();
	}

	void init()
	{
		LOG_SETUP(true);
		functional::DetourManager::setup(true);

		SetConsoleTitleA("Syndicate Uplink");
		std::cout << dye::black_on_red("[-S-]") << dye::red(" Syndicate by itisluiz\n");
		setupFeatures();
		LOG_INFO("Press " << dye::light_blue("Home") << " to clear IE cookies");
		LOG_INFO("Press " << dye::light_blue("End") << " to eject");
	}

	void deinit()
	{
		LOG_SETUP(false);
		functional::DetourManager::setup(false);
	}

	void onKey(uint8_t vkCode, bool down)
	{
		if (down)
		{
			if (misc::isKeyDown(VK_MENU) && vkCode != VK_MENU && vkCode != VK_TAB)
			{
				feature::bind::makeBind(vkCode);
				return;
			}
			else if (misc::isKeyDown(VK_SHIFT) && vkCode != VK_SHIFT)
			{
				feature::bind::handleBind(vkCode);
				return;
			}

			switch (vkCode)
			{
				case VK_INSERT:
				{
					feature::xray::cycleMode();
					break;
				}
				case VK_HOME:
				{
					LOG_INFO("Cookie cleaner: " << dye::light_green("Running"));
					system("RunDll32.exe InetCpl.cpl,ClearMyTracksByProcess 1043");
					break;
				}
				case VK_END:
				{
					winapi::unload();
					break;
				}
			}
		}
	}

}