#include "../ChebySignature.hpp"
#include "ChebySignatureTesters.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>
#include <limits>
#include <ostream>
#include <chrono>

void ChebySignature::Testers::ChebySignatureTester()
{
    int choice;
    bool run = true;

    while (run)
    {
        std::cout << "===== ChebySignature Tester =====" << std::endl;

        std::cout << "1. Sign test" << std::endl;
        //std::cout << "2. modularInverse test" << std::endl;
        std::cout << "0. Exit" << std::endl;

        std::cout << "Your choice: "; 
        if (!(std::cin >> choice)) {
		    std::cout << "ERROR: type number!" << std::endl; 
		    std::cin.clear();
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		    continue;
	    }

        switch (choice) {
        case 1:
        {
            clearScreen();

            auto start = std::chrono::high_resolution_clock::now();

            Hash128 messageHash{2284252, 148867};

            // GENERATING KEYS

            std::cout << "[*] Generating keys..." << std::endl;

            auto intermediateStart = std::chrono::high_resolution_clock::now();

            auto keys = Signature::generateKeyPair();

            PrivateKey privateKey = keys.privateKey;
            PublicKey publicKey = keys.publicKey;

            auto intermediateEnd = std::chrono::high_resolution_clock::now();
            auto intermediateDuration = std::chrono::duration<double>(intermediateEnd - intermediateStart);

            std::cout << "[+] Generating keys... DONE!" 
                      << " ("  << intermediateDuration.count() << " s.)" 
                      << std::endl << std::endl;

            // GENERATING SIGNATURE
            std::cout << "[*] Generating signature..." << std::endl;
            intermediateStart = std::chrono::high_resolution_clock::now();

            Hash128 signature = Signature::sign(messageHash, privateKey);

            intermediateEnd = std::chrono::high_resolution_clock::now();
            intermediateDuration = std::chrono::duration<double>(intermediateEnd - intermediateStart);

            std::cout << "[+] Generating signature... DONE!"                       
                      << " ("  << intermediateDuration.count() << " s.)" 
                      << std::endl << std::endl;

            // VERIFYING SIGNATURE
            std::cout << "[*] Verifying signature..." << std::endl;
            intermediateStart = std::chrono::high_resolution_clock::now();

            Hash128 verified = Signature::verify(signature, publicKey);
            
            intermediateEnd = std::chrono::high_resolution_clock::now();
            intermediateDuration = std::chrono::duration<double>(intermediateEnd - intermediateStart);

            std::cout << "[+] Verifying signature... DONE!"                      
                      << " ("  << intermediateDuration.count() << " s.)" 
                      << std::endl << std::endl;

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double>(end - start);

            std::cout << "Original:  "
                      << messageHash.high << ":" << messageHash.low 
                      << std::endl;

            std::cout << "Signature: "
                      << signature.high << ":" << signature.low 
                      << std::endl;

            std::cout << "Verified:  "
                      << verified.high << ":" << verified.low 
                      << std::endl;

            std::cout << "Result: "
                      << (verified.high == messageHash.high && verified.low == messageHash.low ? "PASS" : "FAIL")
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