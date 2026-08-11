#include "ChebyHash.hpp"
#include <bit>
#include <cstdint>
#include <string_view>

constexpr auto ROUND_COUNT = 32;

void ChebyHash::ChebyHash32::round(std::uint32_t& x, std::uint32_t& y)
{
    y += x;
    x ^= y;
    
    y = std::__rotr(y, 13);
    x = std::__rotl(x, 17);

    y ^= x;
    x += y;
}

std::uint32_t ChebyHash::ChebyHash32::mix(std::uint32_t x, std::uint32_t y)
{
    for (auto i = 0; i < ROUND_COUNT; ++i)
    {
        round(x, y);
    }

    return x;
}

std::uint32_t ChebyHash::ChebyHash32::hash(std::string_view input)
{
    std::uint32_t x = 0;
    std::uint32_t y = 0;

    for (std::size_t i = 0; i < input.size(); ++i)
    {
        if (i % 2 == 0)
            x ^= static_cast<std::uint32_t>(input[i]);
        else
            y ^= static_cast<std::uint32_t>(input[i]);
    }

    return mix(x, y);
}