#include "../ChebySignature.hpp"
#include "ChebySignatureTesters.hpp"

#include "../../Utils/Utils.hpp"
#include <cstddef>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>

void ChebySignature::Testers::ChebySignatureTester()
{
    int choice;
    std::string data;
    std::size_t blockIndex;
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

            Hash128 messageHash{2284252, 148867};

            auto keys = Signature::generateKeyPair();

            PrivateKey privateKey = keys.privateKey;

            PublicKey publicKey = keys.publicKey;

            Hash128 signature = Signature::sign(messageHash, privateKey);

            Hash128 verified = Signature::verify(signature, publicKey);

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
            break;
        }
        case 0:
            run = false;
            break;
        }
    }
}