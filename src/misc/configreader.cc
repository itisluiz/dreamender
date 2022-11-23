#include <misc/configreader.hh>
#include <filesystem>
#include <fstream>

namespace syndicate::misc
{
	std::string getConfigPath()
	{
		HKEY byondUserpath;

		if (RegOpenKeyExA(HKEY_CURRENT_USER, "Software\\Dantom\\BYOND", 0, KEY_READ, &byondUserpath) != ERROR_SUCCESS)
			return { };

		char buffer[MAX_PATH];
		DWORD bufferSize{ sizeof(buffer) };

		if (RegQueryValueExA(byondUserpath, "userpath", NULL, NULL, reinterpret_cast<LPBYTE>(buffer), &bufferSize) != ERROR_SUCCESS)
		{
			RegCloseKey(byondUserpath);
			return { };
		}

		RegCloseKey(byondUserpath);
		std::string result{ buffer };
		return result + "syndicate.ini";
	}

	bool createCfgIfNotExists()
	{
		std::string configPath{ getConfigPath() };

		if (configPath.empty())
			return false;

		if (std::filesystem::exists(configPath))
			return true;

		std::ofstream newCfgFile{ configPath };

		if (!newCfgFile)
			return false;

		newCfgFile << "[spoofing]" "\r\n";
		newCfgFile << "byondmember=0" "\r\n";
		newCfgFile << "computer_id=0" "\r\n";
		newCfgFile.close();

		return true;
	}


}