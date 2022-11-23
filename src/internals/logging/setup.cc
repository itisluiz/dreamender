#include <internals/logging/setup.hh>
#include <Windows.h>

namespace syndicate::logging
{
	bool setConsole(bool allocated)
	{
		FILE* bufferFile;
		FILE* stdFiles[]{ stdin, stdout, stderr };

		if (!allocated)
		{
			for (FILE* stdFile : stdFiles)
				fclose(stdFile);

			FreeConsole();
			return true;
		}

		if (!GetConsoleWindow() && !AllocConsole())
			return false;

		for (FILE* stdFile : stdFiles)
		{
			bool in{ stdFile == stdin };
			if (freopen_s(&bufferFile, in ? "CONIN$" : "CONOUT$", in ? "r" : "w", stdFile) != NULL)
				return false;
		}

		return true;
	}

	std::string timestamp()
	{
		SYSTEMTIME systemTime;
		GetLocalTime(&systemTime);

		char buffer[16];
		std::snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d.%02d", systemTime.wHour, systemTime.wMinute, systemTime.wSecond, systemTime.wMilliseconds / 10);

		return buffer;
	}

}