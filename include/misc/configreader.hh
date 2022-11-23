#ifndef SYNDICATE_MISC_CONFIGREADER_H
#define SYNDICATE_MISC_CONFIGREADER_H
#include <string>
#include <sstream>
#include <Windows.h>

namespace syndicate::misc
{
	std::string getConfigPath();
	bool createCfgIfNotExists();

	template<typename T>
	T readConfig(const std::string& section, const std::string& keyName);

}

#include "impl/configreader.inl"
#endif