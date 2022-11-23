#ifndef SYNDICATE_LOGGING_SETUP_H
#define SYNDICATE_LOGGING_SETUP_H
#include "color.hh"
#include <string>

namespace syndicate::logging
{
	bool setConsole(bool allocated);
	std::string timestamp();
}

#endif
