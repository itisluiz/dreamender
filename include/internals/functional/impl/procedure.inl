#ifndef SYNDICATE_FUNCTIONAL_PROCEDURE_I
#define SYNDICATE_FUNCTIONAL_PROCEDURE_I

namespace syndicate::functional
{
	template<typename Fn>
	Procedure<Fn>::Procedure(Fn* function)
		: m_address(function) { }

	template<typename Fn>
	Procedure<Fn>::Procedure(uintptr_t address)
		: m_address(reinterpret_cast<Fn*>(address)) { }

	template<typename Fn>
	Procedure<Fn>::Procedure(void* address)
		: m_address(reinterpret_cast<Fn*>(address)) { }

	template<typename Fn>
	Procedure<Fn> Procedure<Fn>::fromOffset(HMODULE hModule, ptrdiff_t offset)
	{
		return Procedure<Fn>(reinterpret_cast<uintptr_t>(hModule) + offset);
	}

	template<typename Fn>
	Procedure<Fn> Procedure<Fn>::fromOffset(const std::string& moduleName, ptrdiff_t offset)
	{
		return fromOffset(GetModuleHandleA(moduleName.c_str()), offset);
	}

	template<typename Fn>
	Procedure<Fn> Procedure<Fn>::fromExport(HMODULE hModule, const std::string& exportName)
	{
		return Procedure<Fn>(GetProcAddress(hModule, exportName.c_str()));
	}

	template<typename Fn>
	Procedure<Fn> Procedure<Fn>::fromExport(const std::string& moduleName, const std::string& exportName)
	{
		return fromExport(GetModuleHandleA(moduleName.c_str()), exportName);
	}

	template<typename Fn>
	Procedure<Fn> Procedure<Fn>::fromPattern(HMODULE hModule, const memory::Pattern& pattern)
	{
		memory::PESection codeSection{ memory::PESection(".text", hModule) };
		return Procedure<Fn>(pattern.locate(codeSection.start(), codeSection.end()));
	}

	template<typename Fn>
	Procedure<Fn> Procedure<Fn>::fromPattern(const std::string& moduleName, const memory::Pattern& pattern)
	{
		return fromPattern(GetModuleHandleA(moduleName.c_str()), pattern);
	}

	template<typename Fn>
	Procedure<Fn>::operator bool() const
	{
		return m_address != nullptr;
	}

	template<typename Fn>
	Fn* Procedure<Fn>::operator&() const
	{
		return m_address;
	}

	template<typename Fn>
	template<typename... Args>
	std::result_of_t<Fn& (Args...)> Procedure<Fn>::operator()(Args... args)
	{
		return m_address(std::forward<Args>(args)...);
	}

	template<typename Fn>
	Procedure<Fn> Procedure<Fn>::detourTo(const Procedure<Fn>& callback, bool enable)
	{
		if (m_address == callback.m_address)
		{
			DetourManager::remove(m_address);
			return *this;
		}

		return { DetourManager::create(m_address, callback.m_address, enable) };
	}

	template<typename Fn>
	bool Procedure<Fn>::setDetour(bool enable)
	{
		return DetourManager::enabled(m_address, enable);
	}

}

#endif