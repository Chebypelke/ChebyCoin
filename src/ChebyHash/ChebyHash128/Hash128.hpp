#include <cstdint>

namespace ChebyHash::ChebyHash128
{
    struct Hash128
    {
        std::uint64_t high;
        std::uint64_t low;
    };

    Hash128 add(const Hash128& valueOne, const Hash128& valueTwo);
    Hash128 xorValues(const Hash128& valueOne, const Hash128& valueTwo);
    Hash128 rotl(const Hash128& value, unsigned int shift);
    Hash128 rotr(const Hash128& value, unsigned int shift);
}

