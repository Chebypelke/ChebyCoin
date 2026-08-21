#include "Menus.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>
#include <limits>

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

            if (!(std::cin >> choice))
            {
                std::cout << "ERROR: type number!" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            switch (choice)
            {
            case 1:
                clearScreen();
                return BlockchainMenuChoice::BlockchainInfo;
            case 2:
                clearScreen();
                return BlockchainMenuChoice::ValidateBlockchain;
            case 3:
                clearScreen();
                return BlockchainMenuChoice::ShowBlock;
            case 0:
                clearScreen();
                return BlockchainMenuChoice::Back;
            default:
                clearScreen();
                std::cout << "ERROR: Invalid choice" << std::endl;
                break;
            }
        }

        std::cout << "1. Load Blockchain" << std::endl;
        std::cout << "0. Back" << std::endl;

        std::cout << "Your choice: " << std::endl;
        std::cout << "> ";

        if (!(std::cin >> choice))
        {
            std::cout << "ERROR: type number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            clearScreen();
            return BlockchainMenuChoice::LoadBlockchain;
        case 0:
            clearScreen();
            return BlockchainMenuChoice::Back;
        default:
            clearScreen();
            std::cout << "ERROR: Invalid choice" << std::endl;
            break;
        }
    }
}