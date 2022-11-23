#ifndef SYNDICATE_H
#define SYNDICATE_H
#include <cstdint>

namespace syndicate
{
	void init();
	void deinit();
	void onKey(uint8_t vkCode, bool down);
}

#endif