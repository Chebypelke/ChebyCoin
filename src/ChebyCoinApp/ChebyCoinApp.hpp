#pragma once

#include "Menus/Menus.hpp"

namespace ChebyCoinApp 
{
    class App
    {
    private:
        MainMenu mainMenu;

        std::optional<ChebyWallet::Wallet::WalletData> wallet;
    public:
        void run();
    };
};