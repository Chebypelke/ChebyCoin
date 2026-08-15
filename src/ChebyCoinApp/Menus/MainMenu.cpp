#include "Menus.hpp"
#include "../../Utils/Utils.hpp"
#include <iostream>
#include <limits>

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

        if (!(std::cin >> choice)) {
		    std::cout << "ERROR: type number!" << std::endl; 
		    std::cin.clear();
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		    continue;
	    }

        switch (choice) {
        case 1:
            clearScreen();
            return MainMenuChoice::Wallet;
        case 2: 
            clearScreen();
            return MainMenuChoice::Transactions;
        case 3:
        {
            clearScreen();
            return MainMenuChoice::Blockchain;
        }
        case 4:
            clearScreen();
            return MainMenuChoice::Mining;
        case 0: return MainMenuChoice::Exit;
        default: 
            clearScreen();
            std::cout << "ERROR: Invalid choice" << std::endl;
            break;
        }
    }
}