#include <misc/keyhelper.hh>
#include <Windows.h>
#include <sstream>

namespace syndicate::misc
{
	uint8_t getPressedKey()
	{
		// 0 - Z
		for (uint8_t vkCode{ 0x30 }; vkCode < 0x5A; ++vkCode)
		{
			// Skip unused
			if (vkCode == 0x3A)
				vkCode = 0x41;

			if (isKeyDown(vkCode))
				return vkCode;
		}

		return 0;
	}

	bool isKeyDown(uint8_t keyCode)
	{
		return GetKeyState(keyCode) & 0x8000;
	}

	std::string getKeyName(uint8_t keyCode)
	{
		char buffer[64];

		if (!GetKeyNameTextA(static_cast<LONG>(MapVirtualKeyA(keyCode, MAPVK_VK_TO_VSC)) << 16, buffer, sizeof(buffer)))
		{
			std::ostringstream unknKey("Unknown (0x", std::ios::app);
			unknKey.flags(std::ios::hex);
			unknKey << static_cast<short>(keyCode);
			unknKey << ')';

			return unknKey.str();
		}

		return { buffer };
	}

}