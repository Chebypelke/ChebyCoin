#pragma once

#include "../ChebyHash/ChebyHash.hpp"

#include <cstdint>

/**
 * @defgroup ChebySignature ChebySignature
 * @brief Experimental toy-rsa library.
 *
 * @warning
 * ChebySignature is NOT cryptographically secure.
 * Do not use it for passwords, authentication,
 * digital signatures or key derivation.
 */

namespace ChebySignature
{
    constexpr std::uint64_t e = 65537;

    using Hash128 = ChebyHash::ChebyHash128::Hash128;
    
    /**
    * @brief Public key.
    *
    * @param modulus         Product of two large prime numbers (p and q).
    * @param publicExponent  Public exponent (e), commonly set to 65537. Used in RSA encryption and digital signature verification.
    */
    struct PublicKey
    {
        Hash128 modulus;
        Hash128 publicExponent;
    };

    /**
     * @brief Private key.
     *
     * @param modulus          Product of two large, secret prime numbers(p and q)
     * @param privateExponent  Private exponent (d), computed as the modular inverse of the public exponent (e) modulo Euler's totient φ(n).
     */
    struct PrivateKey
    {
        Hash128 modulus;
        Hash128 privateExponent;
    };

    /**
    * @brief Cryptographic key pair containing mathematically related public and private keys.
    *
    * @param publicKey   Public key used for encryption and digital signature verification.
    * @param privateKey  Private key used for decryption and digital signing.
    */
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