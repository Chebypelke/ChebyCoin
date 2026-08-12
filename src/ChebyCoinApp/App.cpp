#include "ChebyCoinApp.hpp"
#include "../Utils/Utils.hpp"

void ChebyCoinApp::App::run()
{
    bool run = true;

    while (run) 
    {
        auto choice = mainMenu.mainMenu();

        switch (choice) 
        {
        case ChebyCoinApp::MainMenu::MainMenuChoice::Wallet: // Заглушка
            clearScreen();
            break; 
        case ChebyCoinApp::MainMenu::MainMenuChoice::Transactions: // Заглушка 
            clearScreen();
            break; 
        case ChebyCoinApp::MainMenu::MainMenuChoice::Blockchain: // Заглушка
            clearScreen();
            break; 
        case ChebyCoinApp::MainMenu::MainMenuChoice::Mining: // Заглушка
            clearScreen();
            break; 
        case ChebyCoinApp::MainMenu::MainMenuChoice::Exit: // Заглушка
            clearScreen();
            run = false;
            break;
        }
    }
}