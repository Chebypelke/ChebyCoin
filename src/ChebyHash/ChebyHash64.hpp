#pragma once

#include <cstdint>

// WARNING:
// Experimental educational hash.
// NOT cryptographically secure.
// Do not use for real passwords, signatures,
// authentication, key derivation, or secure storage.

void round(std::uint64_t& x, std::uint64_t& y);
std::uint64_t mix(std::uint64_t x, std::uint64_t y);