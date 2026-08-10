#include "ChebyHashTesters.hpp"
#include "../ChebyHash32.hpp"
#include <bit>
#include <cstdint>
#include <iostream>
#include <chrono>

void ChebyHash32Tester()
{
    auto start = std::chrono::high_resolution_clock::now();
    
    auto total = std::uint64_t{0};
    constexpr std::uint32_t TEST_COUNT = 10'000'000;

    auto attempt_start = std::chrono::high_resolution_clock::now();

    for (std::uint32_t y = 0; y < TEST_COUNT; ++y)
    {
        if ((y + 1) % 100'000 == 0)
        {
            auto attempt_end = std::chrono::high_resolution_clock::now();
            
            auto attempt_duration = std::chrono::duration<double>(attempt_end - attempt_start);

            std::cout << "Attempt: " << y+1 << "," 
                      << " duration: " << attempt_duration.count() << "s." << std::endl;

            attempt_start = attempt_end;
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

    auto end = std::chrono::high_resolution_clock::now();
            
    auto duration = std::chrono::duration<double>(end - start);

    std::cout << "Average: " << average << std::endl 
              << "Duration: " << duration.count() << "s." << std::endl;
}