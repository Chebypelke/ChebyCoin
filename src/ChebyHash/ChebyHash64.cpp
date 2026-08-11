#include "ChebyHash64.hpp"
#include <bit>
#include <cstdint>

constexpr auto ROUND_COUNT = 32;

void ChebyHash64::round(std::uint64_t& x, std::uint64_t& y)
{
    y += x;
    x ^= y;
    
    y = std::__rotr(y, 13);
    x = std::__rotl(x, 17);

    y ^= x;
    x += y;
}

std::uint64_t ChebyHash64::mix(std::uint64_t x, std::uint64_t y)
{
    for (auto i = 0; i < ROUND_COUNT; ++i)
    {
        round(x, y);
    }

    return x;
}

std::uint64_t ChebyHash64::hash(std::string_view input)
{
    std::uint64_t x = 0;
    std::uint64_t y = 0;

    for (std::size_t i = 0; i < input.size(); ++i)
    {
        if (i % 2 == 0)
            x ^= static_cast<std::uint64_t>(input[i]);
        else
            y ^= static_cast<std::uint64_t>(input[i]);
    }

    return mix(x, y);
}