#pragma once

#include <cstdint>
#include <string_view>

// WARNING:
// Experimental educational hash.
// NOT cryptographically secure.
// Do not use for real passwords, signatures,
// authentication, key derivation, or secure storage.

class ChebyHash32
{
private:
    static void round(std::uint32_t& x, std::uint32_t& y);
    static std::uint32_t mix(std::uint32_t x, std::uint32_t y);
public:
    static std::uint32_t hash(std::string_view input);
};
