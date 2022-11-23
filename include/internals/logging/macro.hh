#ifndef SYNDICATE_LOGGING_MACRO_H
#define SYNDICATE_LOGGING_MACRO_H
#include "setup.hh"

#define LOG_LEVEL 1

#define LOG_SETUP(init) if constexpr(LOG_LEVEL > 0) { syndicate::logging::setConsole(init); } 
#define LOG_GENERIC(loglevel, prefix, msg) if constexpr(LOG_LEVEL >= loglevel) { std::cout << '[' << syndicate::logging::timestamp() << ']' << prefix << ' ' << msg << '\n'; }

#define LOG_INFO(msg) LOG_GENERIC(1, "[+]", msg)
#define LOG_ERROR(msg) LOG_GENERIC(1, dye::light_red("[!]"), msg)
#define LOG_DEBUG(msg) LOG_GENERIC(2, dye::light_yellow("[/]"), msg)

#endif
