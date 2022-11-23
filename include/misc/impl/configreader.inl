#ifndef SYNDICATE_MISC_CONFIGREADER_I
#define SYNDICATE_MISC_CONFIGREADER_I

namespace syndicate::misc
{
	template<typename T>
	T readConfig(const std::string& section, const std::string& keyName)
	{
		std::string configPath{ getConfigPath() };
		T result{ };

		if (configPath.empty())
			return result;
		
		char buffer[256];
		if (GetPrivateProfileStringA(section.c_str(), keyName.c_str(), NULL, buffer, sizeof(buffer), configPath.c_str()) <= 0)
			return result;

		std::istringstream valueParser{ buffer };
		valueParser >> result;

		return result;
	}


}

#endif