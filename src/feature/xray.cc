#include <feature/xray.hh>
#include <internals/logging/macro.hh>
#include <sdk/byond.hh>

namespace syndicate::feature::xray
{
	bool init(uint8_t mode)
	{
		sdk::Sight* pSight{ reinterpret_cast<sdk::Sight*>(**(&sdk::byond::Render) + 0x214) };
	
		switch (mode)
		{
			case 1:
				pSight->sight = 512;
				pSight->see_in_dark = 255;
				pSight->see_invisible = 15;
				LOG_INFO("X-Ray: " << dye::light_green("Night-vision"));
				break;
			case 2:
				pSight->sight = 514;
				pSight->see_in_dark = 255;
				pSight->see_invisible = 255;
				LOG_INFO("X-Ray: " << dye::light_blue("Esper"));
				break;
			default:
				pSight->sight = 0;
				pSight->see_in_dark = 2;
				pSight->see_invisible = 25;
				LOG_INFO("X-Ray: " << dye::grey("Disabled"));
				break;
		}

		return true;
	}

	void cycleMode()
	{
		static uint8_t mode{ 0 };

		if (++mode > 2)
			mode = 0;

		init(mode);
	}

}