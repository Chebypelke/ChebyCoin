#include "ChebyHashTesters.hpp"
#include "../ChebyHash.hpp"
#include "../../Utils/Utils.hpp"
#include <bit>
#include <cstdint>
#include <iostream>
#include <chrono>

void ChebyHash32Tester()
{
    auto start = std::chrono::high_resolution_clock::now();
    uint64_t last_hash = 0;
    auto total = std::uint64_t{0};

    constexpr std::uint32_t TEST_COUNT = 10'000'00;
    constexpr std::size_t INPUT_LENGTH = 16;

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
        
        auto inputA = RandomStringGenerator(INPUT_LENGTH);
        auto inputB = inputA;

        for (std::size_t bit = 0; bit < inputA.size() * 8; ++bit)
        {
            inputB = inputA;

            auto byte = bit / 8;
            auto bit_in_byte = bit % 8;

            inputB[byte] ^= static_cast<char>(1u << bit_in_byte);

            auto hashA = ChebyHash::ChebyHash32::hash(inputA);
            auto hashB = ChebyHash::ChebyHash32::hash(inputB);

            auto diff = std::__popcount(hashA ^ hashB);

            last_hash = hashB;
            total += diff;
        } 
    }

    auto average = static_cast<double>(total) / (TEST_COUNT * INPUT_LENGTH * 8);

    auto end = std::chrono::high_resolution_clock::now();
            
    auto duration = std::chrono::duration<double>(end - start);

    std::cout << "Average: " << average << std::endl 
              << "Duration: " << duration.count() << "s." << std::endl
              << "Last hash: " << std::hex << last_hash;
}