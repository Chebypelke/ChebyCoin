#include "Menus.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>
#include <limits>

ChebyCoinApp::WalletMenu::WalletMenu(std::optional<ChebyWallet::Wallet::WalletData> &wallet) : wallet(wallet)
{
}

ChebyCoinApp::WalletMenu::WalletMenuChoice ChebyCoinApp::WalletMenu::walletMenu()
{
    int choice = 0;

    while (true)
    {
        std::cout << "===== ChebyCoin App - Wallet =====" << std::endl;

        if (wallet)
        {
            std::cout << "1. Wallet Info" << std::endl;
            std::cout << "2. Balance" << std::endl;
            std::cout << "3. Send Coins" << std::endl;
            std::cout << "4. Transactions" << std::endl;
            std::cout << "5. Save Wallet" << std::endl;
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
                return WalletMenuChoice::WalletInfo;
            case 2:
                CLIUtils::clearScreen();
                return WalletMenuChoice::Balance;
            case 3:
                CLIUtils::clearScreen();
                return WalletMenuChoice::SendCoins;
            case 4:
                CLIUtils::clearScreen();
                return WalletMenuChoice::Transactions;
            case 5:
                CLIUtils::clearScreen();
                return WalletMenuChoice::SaveWallet;
            case 0:
                CLIUtils::clearScreen();
                return WalletMenuChoice::Back;
            default:
                CLIUtils::clearScreen();
                std::cout << "ERROR: Invalid choice" << std::endl;
                break;
            }
        }

        std::cout << "1. Create Wallet" << std::endl;
        std::cout << "2. Load Wallet" << std::endl;
        std::cout << "0. Back" << std::endl;

        std::cout << "Your choice: " << std::endl;
        std::cout << "> ";

        if (!CLIUtils::readInt(choice))
        {
            std::cout << "ERROR: type number!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            CLIUtils::clearScreen();
            return WalletMenuChoice::CreateWallet;
        case 2:
            CLIUtils::clearScreen();
            return WalletMenuChoice::LoadWallet;
        case 0:
            CLIUtils::clearScreen();
            return WalletMenuChoice::Back;
        default:
            CLIUtils::clearScreen();
            std::cout << "ERROR: Invalid choice" << std::endl;
            break;
        }
    }
}