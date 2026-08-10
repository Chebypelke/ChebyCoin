#include "ChebyHash.hpp"
#include <bit>
#include <cstdint>
#include <iostream>

void ChebyHashTester()
{
    auto total = std::uint64_t{0};
    constexpr std::uint32_t TEST_COUNT = 10'000'000;

    for (std::uint32_t y = 0; y < TEST_COUNT; ++y)
    {
        if (y % 100000 == 0)
        {
            std::cout << "Attempt: " << y << '\n';
        }

        for(int bit = 0; bit < 32; bit++)
        {
            auto inputA = 0x00000001u;
            auto inputB = inputA ^ (1 << bit);
        
            auto hashA = mix(inputA, y);
            auto hashB = mix(inputB, y);

            auto diff = std::__popcount(hashA ^ hashB);

            total += diff;
        }   
    }

    auto average = static_cast<double>(total) / (TEST_COUNT * 32);

    std::cout << "Average: " << average << '\n';
}