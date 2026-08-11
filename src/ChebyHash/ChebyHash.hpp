#pragma once

#include <cstdint>
#include <string_view>

// WARNING:
// Experimental educational hash.
// NOT cryptographically secure.
// Do not use for real passwords, signatures,
// authentication, key derivation, or secure storage.

namespace ChebyHash
{
    class ChebyHash32
    {
    private:
        static void round(std::uint32_t& x, std::uint32_t& y);
        static std::uint32_t mix(std::uint32_t x, std::uint32_t y);
    public:
        static std::uint32_t hash(std::string_view input);
    };

    class ChebyHash64
    {
    private:
        static void round(std::uint64_t& x, std::uint64_t& y);
        static std::uint64_t mix(std::uint64_t x, std::uint64_t y);
    public:
        static std::uint64_t hash(std::string_view input);
    };
    class ChebyHash128
    {
    public:
        struct Hash128
        {
            std::uint64_t high;
            std::uint64_t low;
        };

        static Hash128 add(const Hash128& valueOne, const Hash128& valueTwo);
        static Hash128 xorValues(const Hash128& valueOne, const Hash128& valueTwo);
        static Hash128 rotl(const Hash128& value, unsigned int shift);
        static Hash128 rotr(const Hash128& value, unsigned int shift);
    private:
        static void round(Hash128& x, Hash128& y);
        static Hash128 mix(Hash128 x, Hash128 y);
    public:
        static Hash128 hash(std::string_view input);
    };
};