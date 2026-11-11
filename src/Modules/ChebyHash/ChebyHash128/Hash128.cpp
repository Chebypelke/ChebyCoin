#include <ChebyHash/ChebyHash.hpp>
#include <cstdint>
#include <utility>

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
    const Hash128& valueOne, bool valueOneNegative,
    const Hash128& valueTwo, bool valueTwoNegative
)
{
    if (isZero(valueOne))
    {
        return SignedHash128{valueTwo, !valueTwoNegative && !isZero(valueTwo)};
    }

    if (isZero(valueTwo))
    {
        return SignedHash128{valueOne, valueOneNegative};
    }

    if (valueOneNegative != valueTwoNegative)
    {
        Hash128 value = valueOne + valueTwo;

        return SignedHash128{value, valueOneNegative};
    }

    if (lessThan(valueOne, valueTwo))
    {
        Hash128 value = valueTwo - valueOne;

        return SignedHash128{value, !valueOneNegative};
    }

    Hash128 value = valueOne - valueTwo;

    if (isZero(value))
    {
        return SignedHash128{Hash128{0, 0}, false};
    }

    return SignedHash128{value, valueOneNegative};
}

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::Hash128::operator+(const Hash128& valueTwo) const
{
    std::uint64_t low = this->low + valueTwo.low;

    bool carry = low < this->low;

    std::uint64_t high = this->high + valueTwo.high + carry;

    return Hash128{high, low};
}

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::Hash128::operator-(const Hash128& valueTwo) const
{
    std::uint64_t low = this->low - valueTwo.low;

    bool borrow = low > this->low;

    std::uint64_t high = this->high - valueTwo.high - borrow;

    return Hash128{high, low};
}

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::Hash128::operator*(const Hash128& valueTwo) const
{
    unsigned __int128 lowProduct = static_cast<unsigned __int128>(low) * valueTwo.low;

    std::uint64_t resultLow = static_cast<std::uint64_t>(lowProduct);

    std::uint64_t resultHigh = static_cast<std::uint64_t>(lowProduct >> 64);

    resultHigh += high * valueTwo.low;
    resultHigh += low * valueTwo.high;

    return Hash128{resultHigh, resultLow};
}

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::Hash128::operator/(const Hash128& divisor) const
{
    return divide(*this, divisor).quotient;
}

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::Hash128::operator%(const Hash128& divisor) const
{
    return divide(*this, divisor).remainder;
}

ChebyHash::ChebyHash128::Hash128
ChebyHash::ChebyHash128::Hash128::operator^(const Hash128& valueTwo) const
{
    std::uint64_t high = this->high ^ valueTwo.high;
    std::uint64_t low = this->low ^ valueTwo.low;

    return Hash128{high, low};
}

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::shiftLeft(const Hash128& value, unsigned int shift)
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

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::shiftRight(const Hash128& value, unsigned int shift)
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

ChebyHash::ChebyHash128::DivisionResult 
ChebyHash::ChebyHash128::divide(const Hash128& value, const Hash128& divisor)
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
            remainder = remainder - divisor;

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

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::rotl(const Hash128& value, unsigned int shift)
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

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::rotr(const Hash128& value, unsigned int shift)
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

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::multiplyMod(
    const Hash128& valueOne, const Hash128& valueTwo, const Hash128& modulus
)
{
    if (isZero(modulus))
    {
        return Hash128{0, 0};
    }

    Hash128 result{0, 0};

    Hash128 value = valueOne % modulus;
    Hash128 multiplier = valueTwo;

    while (!isZero(multiplier))
    {
        if ((multiplier.low & 1ULL) != 0)
        {
            result = addMod(result, value, modulus);
        }

        value = addMod(value, value, modulus);

        multiplier = shiftRight(multiplier, 1);
    }

    return result;
}

ChebyHash::ChebyHash128::Hash128 
ChebyHash::ChebyHash128::addMod(
    const Hash128& valueOne, const Hash128& valueTwo, const Hash128& modulus
)
{
    if (isZero(modulus))
    {
        return Hash128{0, 0};
    }

    Hash128 aMod = valueOne % modulus;
    Hash128 bMod = valueTwo % modulus;
    
    Hash128 mMinusB = modulus - bMod;

    if (!lessThan(aMod, mMinusB))
    {
        return aMod - mMinusB;
    }

    return aMod + bMod;
}