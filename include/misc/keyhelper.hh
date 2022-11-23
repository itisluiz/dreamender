#ifndef SYNDICATE_MISC_KEYHELPER_H
#define SYNDICATE_MISC_KEYHELPER_H
#include <string>


namespace syndicate::misc
{
	uint8_t getPressedKey();
	bool isKeyDown(uint8_t keyCode);
	std::string getKeyName(uint8_t keyCode);
	
}

#endif