#include "ChebyHash64.hpp"
#include <bit>
#include <cstdint>

constexpr auto ROUND_COUNT = 32;

void round(std::uint64_t& x, std::uint64_t& y)
{
    y += x;
    x ^= y;
    
    y = std::__rotr(y, 13);
    x = std::__rotl(x, 17);

    y ^= x;
    x += y;
}

std::uint32_t mix(std::uint64_t x, std::uint64_t y)
{
    for (auto i = 0; i < ROUND_COUNT; ++i)
    {
        round(x, y);
    }

    return x;
}