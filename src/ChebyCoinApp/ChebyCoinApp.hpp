#pragma once

#include "Menus/Menus.hpp"

namespace ChebyCoinApp 
{
    class App
    {
    private:
        MainMenu mainMenu;

        std::optional<ChebyWallet::Wallet::WalletData> wallet;
        std::optional<ChebyChain::Blockchain> blockchain;

        void runWalletMenu();
        void runBlockchainMenu();
    public:
        void run();
    };
};