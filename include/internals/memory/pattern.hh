#ifndef SYNDICATE_MEMORY_PATTERN_H
#define SYNDICATE_MEMORY_PATTERN_H
#include <vector>
#include <string>
#include <optional>

namespace syndicate::memory
{
	class Pattern
	{
		std::vector<std::optional<uint8_t>> m_bytes{ };
		ptrdiff_t m_offset{ 0 };

	public:
		Pattern(const std::string& idaPattern, ptrdiff_t offset = 0);

	private:
		static inline bool predicate(const uint8_t& data, const std::optional<uint8_t>& pattern);

	public:
		std::string str() const;
		void* locate(void* start, void* end) const;

	};
}

#endif
