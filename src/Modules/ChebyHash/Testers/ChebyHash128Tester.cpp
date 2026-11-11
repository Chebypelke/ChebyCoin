#include "ChebyHashTesters.hpp"
#include <ChebyHash/ChebyHash.hpp>
#include <Utils/CLIUtils.hpp>
#include <Utils/Random.hpp>
#include <bit>
#include <cstdint>
#include <iostream>
#include <chrono>

void ChebyHash::Testers::ChebyHash128Tester()
{
    CLIUtils::clearScreen();

    bool run = true;
    int choice = 0;

    ChebyHash128::Hash128 last_hash{0, 0};

    std::uint32_t avalache_test_count = 0;
    std::uint32_t determinism_test_count = 0;
    std::size_t input_length = 0;

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
        case 1: // Avalache test
        {
            CLIUtils::clearScreen();

            std::cout << "Type tests count: ";
            if (!CLIUtils::readUInt32(avalache_test_count)) 
            {
                std::cout << "ERROR: type number!" << std::endl; 
                break;
	        }
        
            std::cout << "Type input length: ";
            if (!CLIUtils::readSizeT(input_length)) 
            {
                std::cout << "ERROR: type number!" << std::endl; 
                break;
	        }

            auto start = std::chrono::high_resolution_clock::now();
            auto attempt_start = std::chrono::high_resolution_clock::now();
            std::uint32_t progressStep = std::max<std::uint32_t>(1, avalache_test_count / 10);

            auto total = std::uint64_t{0};

            for (std::uint32_t y = 0; y < avalache_test_count; ++y)
            {
                if ((y + 1) % progressStep == 0)
                {
                    auto attempt_end = std::chrono::high_resolution_clock::now();
                    
                    auto attempt_duration = std::chrono::duration<double>(attempt_end - attempt_start);

                    std::cout << "Attempt: " << std::dec << y+1 << "," 
                              << " duration: " << attempt_duration.count() << "s." << std::endl;

                    attempt_start = attempt_end;
                }
                
                auto inputA = Random::RandomStringGenerator(input_length);
                auto inputB = inputA;

                for (std::size_t bit = 0; bit < inputA.size() * 8; ++bit)
                {
                    inputB = inputA;

                    auto byte = bit / 8;
                    auto bit_in_byte = bit % 8;

                    inputB[byte] ^= static_cast<char>(1u << bit_in_byte);

                    auto hashA = ChebyHash::ChebyHash128::hash(inputA);
                    auto hashB = ChebyHash::ChebyHash128::hash(inputB);

                    auto diff = std::__popcount(hashA.high ^ hashB.high) + std::__popcount(hashA.low ^ hashB.low);

                    last_hash = hashB;
                    total += diff;
                } 
            }

            auto average = static_cast<double>(total) / (avalache_test_count * input_length * 8);

            auto end = std::chrono::high_resolution_clock::now();
                        
            auto duration = std::chrono::duration<double>(end - start);

            std::cout << "Average: " << average << std::endl 
                      << "Duration: " << duration.count() << "s." << std::endl
                      << "Last hash: " << std::hex << last_hash.high << last_hash.low << std::endl;

            break;
        }
        case 2: // Determinism test
        {
            CLIUtils::clearScreen();

            std::cout << "Type tests count: ";
            if (!CLIUtils::readUInt32(determinism_test_count)) 
            {
                std::cout << "ERROR: type number!" << std::endl; 
                break;
	        }
            
            std::cout << "Type input length: ";
            if (!CLIUtils::readSizeT(input_length)) 
            {
                std::cout << "ERROR: type number!" << std::endl; 
                break;
	        }

            auto start = std::chrono::high_resolution_clock::now();
            auto attempt_start = std::chrono::high_resolution_clock::now();
            std::uint32_t progressStep = std::max<std::uint32_t>(1, determinism_test_count / 10);

            auto inputA = Random::RandomStringGenerator(input_length);
            auto inputB = inputA;

            auto total = std::uint64_t{0};

            for (std::uint32_t y = 0; y < determinism_test_count; ++y)
            {
                if ((y + 1) % progressStep == 0)
                {
                    inputA = Random::RandomStringGenerator(input_length);
                    inputB = inputA;

                    auto attempt_end = std::chrono::high_resolution_clock::now();
                    
                    auto attempt_duration = std::chrono::duration<double>(attempt_end - attempt_start);

                    std::cout << "Attempt: " << std::dec << y + 1 << "," 
                              << " duration: " << attempt_duration.count() << "s." << std::endl;

                    attempt_start = attempt_end;
                }
                
                auto hashA = ChebyHash::ChebyHash128::hash(inputA);
                auto hashB = ChebyHash::ChebyHash128::hash(inputB);

                auto diff = std::__popcount(hashA.high ^ hashB.high) + std::__popcount(hashA.low ^ hashB.low);

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
            CLIUtils::clearScreen();
            run = false;
            break;
        }
    }
}

int main()
{
    ChebyHash::Testers::ChebyHash128Tester();
}