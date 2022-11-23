#ifndef SYNDICATE_WINAPI_H
#define SYNDICATE_WINAPI_H
#include <Windows.h>

namespace syndicate::winapi
{
	bool unload(size_t msDelay = 0u);
}

#endif