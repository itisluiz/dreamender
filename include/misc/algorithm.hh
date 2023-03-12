#ifndef SYNDICATE_MISC_ALGORITHM_H
#define SYNDICATE_MISC_ALGORITHM_H
#include <cstdint>

namespace syndicate::misc
{
    constexpr uint32_t const_hash(char const* input)
    {
        return *input ? static_cast<unsigned int>(*input) + 33 * const_hash(input + 1) : 5381;
    }
}

#endif
