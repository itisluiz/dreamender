#ifndef SYNDICATE_FUNCTIONAL_PROCEDURE_H
#define SYNDICATE_FUNCTIONAL_PROCEDURE_H
#include <internals/functional/detourmanager.hh>
#include <internals/memory/pattern.hh>
#include <internals/memory/pe.hh>
#include <type_traits>

namespace syndicate::functional
{
	template<typename Fn>
	class Procedure
	{
		Fn* m_address;

	public:
		Procedure(Fn* function);
		Procedure(uintptr_t address);
		Procedure(void* address = nullptr);

	public:
		static Procedure<Fn> fromOffset(HMODULE hModule, ptrdiff_t offset);
		static Procedure<Fn> fromOffset(const std::string& moduleName, ptrdiff_t offset);

		static Procedure<Fn> fromExport(HMODULE hModule, const std::string& exportName);
		static Procedure<Fn> fromExport(const std::string& moduleName, const std::string& exportName);

		static Procedure<Fn> fromPattern(HMODULE hModule, const memory::Pattern& pattern);
		static Procedure<Fn> fromPattern(const std::string& moduleName, const memory::Pattern& pattern);

	public:
		operator bool() const;
		Fn* operator&() const;
		
		template<typename... Args> 
		std::result_of_t<Fn& (Args...)> operator()(Args... args);

	public:
		Procedure<Fn> detourTo(const Procedure<Fn>& callback, bool enable = true);
		bool setDetour(bool enable);

	};

}

#include "impl/procedure.inl"
#endif
