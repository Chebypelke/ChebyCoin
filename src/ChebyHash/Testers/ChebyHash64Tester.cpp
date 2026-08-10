#include "ChebyHashTesters.hpp"
#include "../ChebyHash64.hpp"
#include <bit>
#include <cstdint>
#include <iostream>
#include <chrono>

void ChebyHash64Tester()
{
    auto start = std::chrono::high_resolution_clock::now();
    
    auto total = std::uint64_t{0};
    constexpr std::uint32_t TEST_COUNT = 10'000'000;

    auto attempt_start = std::chrono::high_resolution_clock::now();

    for (std::uint64_t y = 0; y < TEST_COUNT; ++y)
    {
        if ((y + 1) % 100'000 == 0)
        {
            auto attempt_end = std::chrono::high_resolution_clock::now();
            
            auto attempt_duration = std::chrono::duration<double>(attempt_end - attempt_start);

            std::cout << "Attempt: " << y+1 << "," 
                      << " duration: " << attempt_duration.count() << "s." << std::endl;

            attempt_start = attempt_end;
        }

        for(int bit = 0; bit < 64; bit++)
        {
            auto inputA = 1;
            auto inputB = inputA ^ (std::uint64_t{1} << bit);
        
            auto hashA = mix(inputA, y);
            auto hashB = mix(inputB, y);

            auto diff = std::__popcount(hashA ^ hashB);

            total += diff;
        }   
    }

    auto average = static_cast<double>(total) / (TEST_COUNT * 64);

    auto end = std::chrono::high_resolution_clock::now();
            
    auto duration = std::chrono::duration<double>(end - start);

    std::cout << "Average: " << average << std::endl 
              << "Duration: " << duration.count() << "s." << std::endl;
}