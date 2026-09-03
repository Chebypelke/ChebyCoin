#include "Menus.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>

ChebyCoinApp::MainMenu::MainMenuChoice ChebyCoinApp::MainMenu::mainMenu()
{
    int choice;

    while (true)
    {
        std::cout << "===== ChebyCoin App =====" << std::endl;

        std::cout << "1. Wallet" << std::endl;
        std::cout << "2. Transactions" << std::endl;
        std::cout << "3. Blockchain" << std::endl;
        std::cout << "4. Mining" << std::endl;
        std::cout << "0. Exit" << std::endl;

        std::cout << "Your choice: " << std::endl; 
        std::cout << "> ";

        if (!CLIUtils::readInt(choice)) {
		    std::cout << "ERROR: type number!" << std::endl; 
		    continue;
	    }

        switch (choice) {
        case 1:
            CLIUtils::clearScreen();
            return MainMenuChoice::Wallet;
        case 2: 
            CLIUtils::clearScreen();
            return MainMenuChoice::Transactions;
        case 3:
            CLIUtils::clearScreen();
            return MainMenuChoice::Blockchain;
        case 4:
            CLIUtils::clearScreen();
            return MainMenuChoice::Mining;
        case 0: 
            CLIUtils::clearScreen();
            return MainMenuChoice::Exit;
        default: 
            CLIUtils::clearScreen();
            std::cout << "ERROR: Invalid choice" << std::endl;
            break;
        }
    }
}