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

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::subtract(const Hash128& valueOne, const Hash128& valueTwo)
{
    std::uint64_t low = valueOne.low - valueTwo.low;

    bool borrow = low > valueOne.low;

    std::uint64_t high = valueOne.high - valueTwo.high - borrow;

    return Hash128{high, low};
}  

bool ChebyHash::ChebyHash128::lessThan(const Hash128& valueOne, const Hash128& valueTwo)
{
    if (valueOne.high < valueTwo.high)
    {
        return true;
    }
    
    if (valueOne.high > valueTwo.high)
    {
        return false;
    }

    return valueOne.low < valueTwo.low;
}

bool ChebyHash::ChebyHash128::isZero(const Hash128& value)
{
    return value.high == 0 && value.low == 0;
}

ChebyHash::ChebyHash128::SignedHash128 ChebyHash::ChebyHash128::subtractSigned(
    const Hash128& valueOne, const bool& valueOneNegative, const Hash128& valueTwo, const bool& valueTwoNegative
)
{
    if (valueOneNegative != valueTwoNegative)
    {
        Hash128 value = ChebyHash::ChebyHash128::add(valueOne, valueTwo);

        return SignedHash128{value, valueOneNegative};
    }
    else
    {
        std::uint64_t low = valueOne.low - valueTwo.low;

        bool borrow = low > valueOne.low;

        std::uint64_t high = valueOne.high - valueTwo.high - borrow;

        if (lessThan(valueOne, valueTwo))
        {
            low = valueTwo.low - valueOne.low;
            borrow = low > valueTwo.low;
            high = valueTwo.high - valueOne.high - borrow;

            return SignedHash128{Hash128{high, low}, !valueOneNegative};
        }
        else
        {
            return SignedHash128{Hash128{high, low}, valueOneNegative};
        }
    }
}  

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::multiply(const Hash128& valueOne, const Hash128& valueTwo)
{
    unsigned __int128 lowProduct = static_cast<unsigned __int128>(valueOne.low) * valueTwo.low;

    std::uint64_t low = static_cast<std::uint64_t>(lowProduct);

    std::uint64_t high = static_cast<std::uint64_t>(lowProduct >> 64);

    high += valueOne.high * valueTwo.low;
    high += valueOne.low * valueTwo.high;

    return Hash128{high, low};
}

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::shiftLeft(const Hash128& value, unsigned int shift)
{
    if (shift >= 128)
    {
        return Hash128{0, 0};
    }

    if (shift == 0)
    {
        return value;
    }

    if (shift < 64)
    {
        return Hash128{(value.high << shift) | (value.low >> (64 - shift)), value.low << shift};
    }

    return Hash128{value.low << (shift - 64), 0};

}

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::shiftRight(const Hash128& value, unsigned int shift)
{
    if (shift >= 128)
    {
        return Hash128{0, 0};
    }

    if (shift == 0)
    {
        return value;
    }

    if (shift < 64)
    {
        return Hash128{value.high >> shift, (value.low >> shift) | (value.high << (64 - shift))};
    }

    return Hash128{0, value.high >> (shift - 64)};
}

ChebyHash::ChebyHash128::DivisionResult ChebyHash::ChebyHash128::divide(const Hash128& value, const Hash128& divisor)
{
    if (isZero(divisor))
    {
        return DivisionResult{Hash128{0, 0}, Hash128{0, 0}};
    }

    Hash128 remainder{0, 0};
    Hash128 quotient{0, 0};

    for (int bit = 127; bit >= 0; --bit)
    {
        remainder = shiftLeft(remainder, 1);

        if (bit >= 64)
        {
            remainder.low |= (value.high >> (bit - 64)) & 1;
        }
        else
        {
            remainder.low |= (value.low >> bit) & 1;
        }

        if (!lessThan(remainder, divisor))
        {
            remainder = subtract(remainder, divisor);

            if (bit >= 64)
            {
                quotient.high |= 1ULL << (bit - 64);
            }
            else
            {
                quotient.low |= 1ULL << bit;
            }
        }
    }

    return DivisionResult{quotient, remainder};
}

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::mod(const Hash128& value, const Hash128& divisor)
{
    return divide(value, divisor).remainder;
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

