#pragma once

#include <cstdint>
#include <string_view>

// WARNING:
// Experimental educational hash.
// NOT cryptographically secure.
// Do not use for real passwords, signatures,
// authentication, key derivation, or secure storage.

class ChebyHash64
{
private:
    void round(std::uint64_t& x, std::uint64_t& y);
    std::uint64_t mix(std::uint64_t x, std::uint64_t y);
public:
    std::uint64_t hash(std::string_view input);
};
