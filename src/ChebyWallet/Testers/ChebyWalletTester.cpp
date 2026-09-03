#include "ChebyWalletTesters.hpp"
#include "../ChebyWallet.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>
#include <limits>
#include <ostream>
#include <chrono>

void ChebyWallet::Testers::ChebyWalletTester()
{
    CLIUtils::clearScreen();

    int choice;
    bool run = true;

    while (run)
    {
        std::cout << "===== ChebyWallet Tester =====" << std::endl;

        std::cout << "1. Create wallet" << std::endl;
        std::cout << "2. Test address determinism" << std::endl;
        std::cout << "3. Test unique addresses" << std::endl;
        std::cout << "0. Exit" << std::endl;

        std::cout << "Your choice: "; 
        if (!(std::cin >> choice)) {
		    std::cout << "ERROR: type number!" << std::endl; 
		    std::cin.clear();
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		    continue;
	    }

        switch (choice) {
        case 1: // Create Wallet
        {
            CLIUtils::clearScreen();

            auto start = std::chrono::high_resolution_clock::now();

            // GENERATING WALLET - START

            std::cout << "[*] Generating wallet..." << std::endl;

            auto intermediateStart = std::chrono::high_resolution_clock::now();

            auto wallet = ChebyWallet::Wallet::generateWallet();

            auto intermediateEnd = std::chrono::high_resolution_clock::now();
            auto intermediateDuration = std::chrono::duration<double>(intermediateEnd - intermediateStart);

            // GENERATING WALLET - END
            
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double>(end - start);

            std::cout << "[+] Generating wallet... DONE!" 
                      << " ("  << intermediateDuration.count() << " s.)" 
                      << std::endl << std::endl;

            std::cout << "Wallet address: "
                      << std::hex
                      << wallet.address.value.high << wallet.address.value.low 
                      << std::dec
                      << std::endl;

            std::cout << "Wallet publickey: "
                      << std::hex
                      << wallet.keyPair.publicKey.publicExponent.high
                      << wallet.keyPair.publicKey.publicExponent.low
                      << wallet.keyPair.publicKey.modulus.high
                      << wallet.keyPair.publicKey.modulus.low
                      << std::dec
                      << std::endl;
                      
            std::cout << "Duration: " 
                      << duration.count() << "s." 
                      << std::endl;
            
            break;
        }
        case 2: // Test address determinism
        {
            CLIUtils::clearScreen();

            auto start = std::chrono::high_resolution_clock::now();

            std::uint32_t TEST_COUNT = 0;
            std::uint32_t pass = 0;
            std::uint32_t fail = 0;

            std::cout << "Type test count: "; 
            if (!(std::cin >> TEST_COUNT)) {
		        std::cout << "ERROR: type number!" << std::endl; 
		        std::cin.clear();
		        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		        continue;
	        }

            const std::uint32_t progressSteps = 10;
            const std::uint32_t progressInterval = std::max<std::uint32_t>(1, TEST_COUNT / progressSteps);

            auto keyPair = ChebySignature::Signature::generateKeyPair();
            const auto& PUBLICKEY = keyPair.publicKey;

            auto attemptStart = std::chrono::high_resolution_clock::now();
            
            for (std::uint32_t y = 0; y < TEST_COUNT; ++y)
            {
                if ((y + 1) % progressInterval == 0 || y + 1 == TEST_COUNT)
                {
                    const auto progress = static_cast<std::uint32_t>(
                        ((y + 1) * 100ULL) / TEST_COUNT
                    );

                    auto attemptEnd = std::chrono::high_resolution_clock::now();
                    auto attemptDuration =
                        std::chrono::duration<double>(attemptEnd - attemptStart);

                    std::cout << "[*] Progress: " << progress << "%"
                              << " | Attempt: " << y + 1 << "/" << TEST_COUNT
                              << " | Duration: " << attemptDuration.count() << "s."
                              << std::endl;

                    attemptStart = attemptEnd;
                }

                auto address1 = Wallet::generateAddress(PUBLICKEY);
                auto address2 = Wallet::generateAddress(PUBLICKEY);
                
                if (address1.value.high == address2.value.high && address1.value.low == address2.value.low)
                {
                    pass += 1;
                }
                else 
                {
                    fail += 1;
                    std::cout << "[-] Different addresses found! "
                              << "Attempt: " << y
                              << std::endl;
                }
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double>(end - start);

            std::cout << "Attempts: " << TEST_COUNT 
                      << std::endl;
                      
            std::cout << "PASS: " << pass
                      << std::endl
                      << "FAIL: " << fail 
                      << std::endl;

            std::cout << "Duration: " 
                      << duration.count() << "s." 
                      << std::endl;
        break;
        }
        case 3: // Test unique addresses
        {
            CLIUtils::clearScreen();

            auto start = std::chrono::high_resolution_clock::now();

            std::uint32_t TEST_COUNT = 0;
            std::uint32_t pass = 0;
            std::uint32_t fail = 0;

            std::cout << "Type test count: "; 
            if (!(std::cin >> TEST_COUNT)) {
		        std::cout << "ERROR: type number!" << std::endl; 
		        std::cin.clear();
		        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		        continue;
	        }

            const std::uint32_t progressSteps = 10;
            const std::uint32_t progressInterval = std::max<std::uint32_t>(1, TEST_COUNT / progressSteps);

            auto attemptStart = std::chrono::high_resolution_clock::now();
            
            for (std::uint32_t y = 0; y < TEST_COUNT; ++y)
            {
                if ((y + 1) % progressInterval == 0 || y + 1 == TEST_COUNT)
                {
                    const auto progress = static_cast<std::uint32_t>(
                        ((y + 1) * 100ULL) / TEST_COUNT
                    );

                    auto attemptEnd = std::chrono::high_resolution_clock::now();
                    auto attemptDuration =
                        std::chrono::duration<double>(attemptEnd - attemptStart);

                    std::cout << "[*] Progress: " << progress << "%"
                              << " | Attempt: " << y + 1 << "/" << TEST_COUNT
                              << " | Duration: " << attemptDuration.count() << "s."
                              << std::endl;

                    attemptStart = attemptEnd;
                }

                auto keyPair1 = ChebySignature::Signature::generateKeyPair();
                auto keyPair2 = ChebySignature::Signature::generateKeyPair();
                auto address1 = Wallet::generateAddress(keyPair1.publicKey);
                auto address2 = Wallet::generateAddress(keyPair2.publicKey);
                
                if (address1.value.high != address2.value.high || address1.value.low != address2.value.low)
                {
                    pass += 1;

                }
                else 
                {
                    fail += 1;
                    std::cout << "[-] Duplicate addresses found! "
                              << "Attempt: " << y
                              << std::endl;
                }
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double>(end - start);

            std::cout << "Attempts: " << TEST_COUNT 
                      << std::endl;
                      
            std::cout << "PASS: " << pass
                      << std::endl
                      << "FAIL: " << fail 
                      << std::endl;

            std::cout << "Duration: " 
                      << duration.count() << "s." 
                      << std::endl;
            break;
        }
        case 0:
            run = false;
            break;
        }
    }
}