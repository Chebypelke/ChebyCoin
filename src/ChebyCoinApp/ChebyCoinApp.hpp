#pragma once

namespace ChebyCoinApp 
{
    class MainMenu
    {
    public:
        enum class MainMenuChoice {
            Wallet = 1,
            Transactions = 2,
            Blockchain = 3,
            Mining = 4,
            Exit = 0
        };

        MainMenu::MainMenuChoice mainMenu();
    };

    class App
    {
    private:
        MainMenu mainMenu;
    public:
        void run();
    };
};