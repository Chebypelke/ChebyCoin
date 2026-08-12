#pragma once

#include "../ChebyHash/ChebyHash.hpp"

#include <cstdint>

namespace ChebySignature
{
    using Hash128 = ChebyHash::ChebyHash128::Hash128;

    struct PublicKey
    {
        Hash128 modulus;
        Hash128 publicExponent;
    };

    struct PrivateKey
    {
        Hash128 modulus;
        Hash128 privateExponent;
    };

    struct KeyPair
    {
        PublicKey publicKey;
        PrivateKey privateKey;
    };

    class Signature
    {
    private:
        static Hash128 modularPower(Hash128 base, Hash128 exponent, const Hash128& modulus);

        static std::uint64_t gcd(std::uint64_t first, std::uint64_t second);

        static std::int64_t extendedGcd(std::int64_t first, std::int64_t second, std::int64_t& coefficientOne, std::int64_t& coefficientTwo);

        static Hash128 modularInverse(const Hash128& value, const Hash128& modulus);

        static bool isPrime(std::uint64_t value);
        static std::uint64_t generatePrime();
    public:
        static KeyPair generateKeyPair();

        static Hash128 sign(Hash128 messageHash, const PrivateKey& privateKey);

        static Hash128 verify(Hash128 signature, const PublicKey& publicKey);
    };
}