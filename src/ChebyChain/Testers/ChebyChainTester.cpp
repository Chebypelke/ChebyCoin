#include "ChebyChainTesters.hpp"
#include "../ChebyChain.hpp"
#include "../../Utils/Utils.hpp"
#include <cstddef>
#include <iostream>
#include <limits>
#include <ostream>
#include <string>

void ChebyChain::Testers::ChebyChainTester()
{
    Blockchain blockchain;
    int choice;
    std::string data;
    std::size_t blockIndex;
    bool run = true;

    while (run)
    {
        std::cout << "===== ChebyChain Tester =====" << std::endl;

        std::cout << "1. New block" << std::endl;
        std::cout << "2. Blocks count" << std::endl;
        std::cout << "3. Block by index" << std::endl;
        std::cout << "4. Validate blockchain" << std::endl;
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
            clearScreen();
            std::cout << "Type block data: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (!(std::getline(std::cin, data)))
            {
                std::cin.clear();
		        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		        continue;
            }

            blockchain.addBlock(data);
            break;
        case 2: 
            clearScreen();
            std::cout << "Blocks count: " << blockchain.getBlockCount() << std::endl;
            break; 
        case 3:
        {
            clearScreen();
            std::cout << "Enter block index: ";
            
            if (!(std::cin >> blockIndex)) {
		        std::cout << "ERROR: type number!" << std::endl; 
		        std::cin.clear();
		        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		        continue;
	        }
            
            const Block& block = blockchain.getBlock(blockIndex);
            std::cout << "Block index: " << block.getBlockIndex() << std::endl;
            std::cout << "Block hash: " << block.getBlockHash()
                                        << " (" << std::hex << block.getBlockHash() << ")" << std::dec
                                        << std::endl;
            std::cout << "Block previous hash: " << block.getBlockPreviousHash() 
                                                 << " (" << std::hex << block.getBlockPreviousHash() << ")" << std::dec
                                                 << std::endl;;

            break; 
        }
        case 4:
            clearScreen();

            if (!blockchain.isValid())
            {
                std::cout << "Blockchain is invalid!" << std::endl;
                break;
            }
            
            std::cout << "Blockchain is valid!" << std::endl;
            break;
        case 0:
            run = false;
            break;
        }
    }
}