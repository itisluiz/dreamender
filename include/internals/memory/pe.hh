#ifndef SYNDICATE_MEMORY_PE_H
#define SYNDICATE_MEMORY_PE_H
#include <Windows.h>
#include <string>

namespace syndicate::memory
{
	class PESection
	{
		PIMAGE_SECTION_HEADER m_section{ nullptr };

	public:
		PESection(const std::string& sectionName, const HMODULE hModule);
		PESection(const std::string& sectionName, const LPCSTR szModuleName);

	public:
		operator bool() const;

	public:
		size_t length() const;
		void* start() const;
		void* end() const;

	};

}

#endif