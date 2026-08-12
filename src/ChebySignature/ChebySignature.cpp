#include "ChebySignature.hpp"
#include "../Utils/Utils.hpp"
#include <cmath>

ChebySignature::Hash128 ChebySignature::Signature::modularPower(Hash128 base, Hash128 exponent, Hash128 modulus)
{
    Hash128 result{0, 1};

    base = ChebyHash::ChebyHash128::mod(base, modulus);

    while (!ChebyHash::ChebyHash128::isZero(exponent))
    {
        if ((exponent.low & 1) != 0)
        {
            result = ChebyHash::ChebyHash128::mod(ChebyHash::ChebyHash128::multiply(result, base), modulus);
        }

        base = ChebyHash::ChebyHash128::mod(ChebyHash::ChebyHash128::multiply(base, base), modulus);

        exponent = ChebyHash::ChebyHash128::shiftRight(exponent, 1);
    }

    return result;
}

ChebySignature::Hash128 ChebySignature::Signature::sign(Hash128 messageHash, const PrivateKey& privateKey)
{
    return modularPower(messageHash, Hash128{0, privateKey.privateExponent}, privateKey.modulus);
}

ChebySignature::Hash128 ChebySignature::Signature::verify(Hash128 signature, const PublicKey& publicKey)
{
    return modularPower(signature, Hash128{0, publicKey.publicExponent}, publicKey.modulus);
}

std::uint64_t ChebySignature::Signature::modularInverse(std::uint64_t value, std::uint64_t modulus)
{
    auto oldR = modulus;
    auto r = value;

    std::int64_t oldT = 0;
    std::int64_t t = 1;

    while (r != 0)
    {
        auto quotient = oldR / r;

        // Fucking dog shit
        // Эта херня ищет НОД
        auto temp = oldR;
        oldR = r;
        r = temp - quotient * r;

        // А эта херня ищет коэффициент, который станет inverse.
        temp = oldT;
        oldT = t;
        t = temp - quotient * t;
    }

    if (oldR != 1)
    {
        return 0; // inverse - нема
    }

    if (oldT < 0)
    {
        oldT += modulus;
    }

    return oldT;
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