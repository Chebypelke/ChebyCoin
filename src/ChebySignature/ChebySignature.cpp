#include "ChebySignature.hpp"
#include "../Utils/Utils.hpp"
#include <cmath>

ChebySignature::Hash128 ChebySignature::Signature::modularPower(
    Hash128 base, Hash128 exponent, const Hash128& modulus
)
{
    Hash128 result{0, 1};

    base = ChebyHash::ChebyHash128::mod(base, modulus);

    while (!ChebyHash::ChebyHash128::isZero(exponent))
    {
        if ((exponent.low & 1ULL) != 0)
        {
            result = ChebyHash::ChebyHash128::multiplyMod(
                result,
                base,
                modulus
            );
        }

        base = ChebyHash::ChebyHash128::multiplyMod(
            base,
            base,
            modulus
        );

        exponent =
            ChebyHash::ChebyHash128::shiftRight(exponent, 1);
    }

    return result;
}

ChebySignature::Hash128 ChebySignature::Signature::modularInverse(const Hash128& value, const Hash128& modulus)
{
    if (ChebyHash::ChebyHash128::isZero(modulus))
    {
        return Hash128{0, 0};
    }

    Hash128 valueMod = ChebyHash::ChebyHash128::mod(value, modulus);

    if (ChebyHash::ChebyHash128::isZero(valueMod))
    {
        return Hash128{0, 0};
    }

    if (valueMod.high != 0 || valueMod.low != 65537)
    {
        return Hash128{0, 0};
    }

    constexpr std::uint64_t e = 65537;

    ChebyHash::ChebyHash128::DivisionResult division =
        ChebyHash::ChebyHash128::divide(
            modulus,
            Hash128{0, e}
        );

    Hash128 quotient = division.quotient;
    Hash128 remainder = division.remainder;

    if (ChebyHash::ChebyHash128::isZero(remainder))
    {
        return Hash128{0, 0};
    }

    std::uint64_t r = remainder.low;
    std::uint64_t k = 0;

    for (std::uint64_t candidate = 1; candidate < e; ++candidate)
    {
        std::uint64_t temp = candidate * r + 1;

        if (temp % e == 0)
        {
            k = candidate;
            break;
        }
    }

    if (k == 0)
    {
        return Hash128{0, 0};
    }

    Hash128 firstPart =
        ChebyHash::ChebyHash128::multiply(
            quotient,
            Hash128{0, k}
        );

    std::uint64_t secondPart = (k * r + 1) / e;

    Hash128 result =
        ChebyHash::ChebyHash128::add(
            firstPart,
            Hash128{0, secondPart}
        );

    Hash128 check =
        ChebyHash::ChebyHash128::multiplyMod(
            valueMod,
            result,
            modulus
        );

    if (check.high != 0 || check.low != 1)
    {
        return Hash128{0, 0};
    }

    return result;
}

bool ChebySignature::Signature::isPrime(std::uint64_t value)
{
    if (value < 2)
    {
        return false;
    }

    for (std::uint64_t divisor = 2; divisor <= std::sqrt(value); ++divisor)
    {
        if (value % divisor == 0)
        {
            return false;
        }
    }

    return true;
}

std::uint64_t ChebySignature::Signature::generatePrime()
{
    std::uint64_t candidate = 0;

    while (!isPrime(candidate))
    {
        candidate = std::stoull(RandomNumberGenerator(16));
    }

    return candidate;
}

ChebySignature::KeyPair ChebySignature::Signature::generateKeyPair()
{
    while (true)
    {
        std::uint64_t p = generatePrime();
        std::uint64_t q = generatePrime();  

        while (p == q)
        {
            q = generatePrime();
        }

        Hash128 pHash{0, p};
        Hash128 qHash{0, q};    

        Hash128 modulus = ChebyHash::ChebyHash128::multiply(pHash, qHash);

        Hash128 pMinusOne = ChebyHash::ChebyHash128::subtract(pHash, Hash128{0, 1});
        Hash128 qMinusOne = ChebyHash::ChebyHash128::subtract(qHash, Hash128{0, 1});

        Hash128 phi = ChebyHash::ChebyHash128::multiply(pMinusOne, qMinusOne);

        Hash128 publicExponent{0, 65537};
        Hash128 privateExponent = modularInverse(publicExponent, phi);

        if (!ChebyHash::ChebyHash128::isZero(privateExponent))
        {
            return KeyPair{
                PublicKey
                {
                    modulus,
                    publicExponent
                },
                PrivateKey
                {
                    modulus,
                    privateExponent
                }
            };
        }
    }
}

ChebySignature::Hash128 ChebySignature::Signature::sign(Hash128 messageHash, const PrivateKey& privateKey)
{
    return modularPower(messageHash, privateKey.privateExponent, privateKey.modulus);
}

ChebySignature::Hash128 ChebySignature::Signature::verify(Hash128 signature, const PublicKey& publicKey)
{
    return modularPower(signature, publicKey.publicExponent, publicKey.modulus);
}