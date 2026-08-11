#include "../ChebyHash.hpp"
#include <cstdint>
#include <utility>

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::add(const Hash128& valueOne, const Hash128& valueTwo)
{
    std::uint64_t low = valueOne.low + valueTwo.low;

    bool carry = low < valueOne.low;

    std::uint64_t high = valueOne.high + valueTwo.high + carry;

    return Hash128{high, low};
}

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::xorValues(const Hash128& valueOne, const Hash128& valueTwo)
{
    std::uint64_t high = valueOne.high ^ valueTwo.high;
    std::uint64_t low = valueOne.low ^ valueTwo.low;

    return Hash128{high, low};
}   

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::rotl(const Hash128& value, unsigned int shift)
{
    Hash128 result = value;
    shift %= 128;

    if (shift == 0)
    {
        return result;
    }
    while (shift >= 64)
    {
        std::swap(result.high, result.low);
        shift -= 64;

        if (shift == 0)
        {
            return result;
        }
    }

    uint64_t newHigh = (result.high << shift) | (result.low >> (64 - shift));
    uint64_t newLow = (result.low << shift) | (result.high >> (64 - shift));

    return Hash128{newHigh, newLow};
}

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::rotr(const Hash128& value, unsigned int shift)
{
    Hash128 result = value;
    shift %= 128;

    if (shift == 0)
    {
        return result;
    }
    while (shift >= 64)
    {
        std::swap(result.high, result.low);
        shift -= 64;

        if (shift == 0)
        {
            return result;
        }
    }

    uint64_t newHigh = (result.high >> shift) | (result.low << (64 - shift));
    uint64_t newLow = (result.low >> shift) | (result.high << (64 - shift));

    return Hash128{newHigh, newLow};
}