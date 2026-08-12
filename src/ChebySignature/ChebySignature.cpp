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

ChebySignature::Hash128 ChebySignature::Signature::modularInverse(Hash128 value, Hash128 modulus)
{
    auto oldR = modulus;
    auto r = value;

    bool oldTNegative = false;
    Hash128 oldT{0, 0};
    bool tNegative = false;
    Hash128 t{0, 1};

    while (!ChebyHash::ChebyHash128::isZero(r))
    {
        auto quotient = ChebyHash::ChebyHash128::divide(oldR, r).quotient;

        // Fucking dog shit
        // Эта херня ищет НОД
        auto temp = oldR;
        oldR = r;
        r = ChebyHash::ChebyHash128::subtract(temp, ChebyHash::ChebyHash128::multiply(quotient, r));

        // А эта херня ищет коэффициент, который станет inverse.
        temp = oldT;
        bool tempNegative = oldTNegative;
        oldT = t;
        Hash128 multiplied = ChebyHash::ChebyHash128::multiply(quotient, t);
        bool multipliedNegative = tNegative;
        auto tSubstracted = ChebyHash::ChebyHash128::subtractSigned(temp, tempNegative, multiplied, multipliedNegative);
        t = tSubstracted.value;
        tNegative = tSubstracted.negative;
    }

    if (oldR.high != 0 || oldR.low != 1)
    {
        return Hash128{0, 0}; // inverse - нема
    }

    if (oldTNegative)
    {
        oldT = ChebyHash::ChebyHash128::subtract(modulus, oldT);
        oldTNegative = false;
    }

    oldT = ChebyHash::ChebyHash128::mod(oldT, modulus);

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

ChebySignature::KeyPair ChebySignature::Signature::generateKeyPair()
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
}

ChebySignature::Hash128 ChebySignature::Signature::sign(Hash128 messageHash, const PrivateKey& privateKey)
{
    return modularPower(messageHash, Hash128{0, privateKey.privateExponent}, privateKey.modulus);
}

ChebySignature::Hash128 ChebySignature::Signature::verify(Hash128 signature, const PublicKey& publicKey)
{
    return modularPower(signature, Hash128{0, publicKey.publicExponent}, publicKey.modulus);
}