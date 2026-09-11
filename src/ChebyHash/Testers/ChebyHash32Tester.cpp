#include "ChebyHashTesters.hpp"
#include "../ChebyHash.hpp"
#include "../../Utils/Utils.hpp"
#include <bit>
#include <cstdint>
#include <iostream>
#include <chrono>

void ChebyHash::Testers::ChebyHash32Tester()
{
    bool run = true;
    int choice = 0;

    uint64_t last_hash = 0;

    std::uint32_t TEST_COUNT = 0;
    constexpr std::uint32_t DETERMINISM_TEST_COUNT = 10'000;
    constexpr std::size_t INPUT_LENGTH = 16;

    while (run)
    {
        std::cout << "===== ChebyHash32 Tester =====" << std::endl;

        std::cout << "1. Avalache test" << std::endl;
        std::cout << "2. Determinism test" << std::endl;
        std::cout << "0. Exit" << std::endl;

        std::cout << "Your choice: "; 
        if (!CLIUtils::readInt(choice))
        {
            std::cout << "ERROR: type number!" << std::endl; 
            continue;
        }

        switch (choice) {
        case 1:
        {
            CLIUtils::clearScreen();
            std::cout << "Type tests count: ";

            if (!CLIUtils::readUInt32(TEST_COUNT)) 
            {
                std::cout << "ERROR: type number!" << std::endl; 
                break;
	        }

            auto start = std::chrono::high_resolution_clock::now();
            auto attempt_start = std::chrono::high_resolution_clock::now();
            std::uint32_t progressStep = std::max<std::uint32_t>(1, TEST_COUNT / 10);

            auto total = std::uint64_t{0};

            for (std::uint32_t y = 0; y < TEST_COUNT; ++y)
            {
                if ((y + 1) % progressStep == 0)
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
                      << "Last hash: " << std::hex << last_hash << std::endl;

            break;
        }
        case 2: 
        {
            CLIUtils::clearScreen();

            auto start = std::chrono::high_resolution_clock::now();
            auto attempt_start = std::chrono::high_resolution_clock::now();
            std::uint32_t progressStep = std::max<std::uint32_t>(1, DETERMINISM_TEST_COUNT / 10);

            auto inputA = RandomStringGenerator(INPUT_LENGTH);
            auto inputB = inputA;

            auto total = std::uint64_t{0};

            for (std::uint32_t y = 0; y < DETERMINISM_TEST_COUNT; ++y)
            {
                if ((y + 1) % progressStep == 0)
                {
                    inputA = RandomStringGenerator(INPUT_LENGTH);
                    inputB = inputA;

                    auto attempt_end = std::chrono::high_resolution_clock::now();
                    
                    auto attempt_duration = std::chrono::duration<double>(attempt_end - attempt_start);

                    std::cout << "Attempt: " << y + 1 << "," 
                              << " duration: " << attempt_duration.count() << "s." << std::endl;

                    attempt_start = attempt_end;
                }
                
                auto hashA = ChebyHash::ChebyHash32::hash(inputA);
                auto hashB = ChebyHash::ChebyHash32::hash(inputB);

                auto diff = std::__popcount(hashA ^ hashB);

                total += diff;
            } 

            auto end = std::chrono::high_resolution_clock::now();
                        
            auto duration = std::chrono::duration<double>(end - start);

            if (total != 0)
            {
                std::cout << "Test: FAIL" << std::endl 
                          << "Duration: " << duration.count() << "s." << std::endl;
                
                break;
            }

            std::cout << "Test: PASS" << std::endl 
                      << "Duration: " << duration.count() << "s." << std::endl;
            
            break; 
        }
        case 0:
        {
            run = false;
            break;
        }

        }
    }
}

int main()
{
    ChebyHash::Testers::ChebyHash32Tester();
}