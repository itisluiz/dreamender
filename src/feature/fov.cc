#include <feature/fov.hh>
#include <internals/logging/macro.hh>
#include <sdk/byond.hh>

namespace syndicate::feature::fov
{
	bool init(bool increase)
	{
		uint32_t* pViewSize{ reinterpret_cast<uint32_t*>(*(&sdk::byond::ViewSize)) };
		uint32_t* pViewCenter{ reinterpret_cast<uint32_t*>(*(&sdk::byond::ViewCenter)) };
		static const uint32_t original[2]{ pViewSize[0], pViewSize[1] };

		if (increase)
		{
			LOG_INFO("FoV: " << dye::light_green("Increased"));
			pViewSize[0] = original[0] + 4;
			pViewSize[1] = original[1] + 4;
		}
		else
		{
			LOG_INFO("FoV: " << dye::grey("Default"));
			pViewSize[0] = original[0];
			pViewSize[1] = original[1];
		}

		pViewCenter[0]= pViewSize[0];
		pViewCenter[1] = pViewSize[1];
		return true;
	}

	void cycleMode()
	{
		static bool increase{ false };
		increase = !increase;

		init(increase);
	}

}