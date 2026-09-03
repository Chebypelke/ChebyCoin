#include "Menus.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>

ChebyCoinApp::BlockchainMenu::BlockchainMenu(std::optional<ChebyChain::Blockchain>& blockchain) : blockchain(blockchain)
{
}

ChebyCoinApp::BlockchainMenu::BlockchainMenuChoice ChebyCoinApp::BlockchainMenu::blockchainMenu()
{
    int choice = 0;

    while (true)
    {
        std::cout << "===== ChebyCoin App - Wallet =====" << std::endl;

        if (blockchain)
        {
            std::cout << "1. Blockchain Info" << std::endl;
            std::cout << "2. Validate Blockchain" << std::endl;
            std::cout << "3. Show Block" << std::endl;
            std::cout << "0. Back" << std::endl;

            std::cout << "Your choice: " << std::endl;
            std::cout << "> ";

            if (!CLIUtils::readInt(choice))
            {
                std::cout << "ERROR: type number!" << std::endl;
                continue;
            }

            switch (choice)
            {
            case 1:
                CLIUtils::clearScreen();
                return BlockchainMenuChoice::BlockchainInfo;
            case 2:
                CLIUtils::clearScreen();
                return BlockchainMenuChoice::ValidateBlockchain;
            case 3:
                CLIUtils::clearScreen();
                return BlockchainMenuChoice::ShowBlock;
            case 0:
                CLIUtils::clearScreen();
                return BlockchainMenuChoice::Back;
            default:
                CLIUtils::clearScreen();
                std::cout << "ERROR: Invalid choice" << std::endl;
                break;
            }
        }

        std::cout << "1. Load Blockchain" << std::endl;
        std::cout << "0. Back" << std::endl;

        std::cout << "Your choice: " << std::endl;
        std::cout << "> ";

        if (!CLIUtils::readInt(choice))
        {
            std::cout << "ERROR: type number!" << std::endl;
            continue;
        }

        switch (choice)
        {
        case 1:
            CLIUtils::clearScreen();
            return BlockchainMenuChoice::LoadBlockchain;
        case 0:
            CLIUtils::clearScreen();
            return BlockchainMenuChoice::Back;
        default:
            CLIUtils::clearScreen();
            std::cout << "ERROR: Invalid choice" << std::endl;
            break;
        }
    }
}