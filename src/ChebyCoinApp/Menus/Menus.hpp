#pragma once

#include "../../ChebyWallet/ChebyWallet.hpp"
#include <optional>

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

        MainMenuChoice mainMenu();
    };

    class WalletMenu
    {
    private:
        std::optional<ChebyWallet::Wallet::WalletData>& wallet;
    public:
        enum class WalletMenuChoice
        {
            CreateWallet = 1,
            LoadWallet = 2,
            WalletInfo = 3,
            Balance = 4,
            SendCoins = 5,
            Transactions = 6,
            SaveWallet = 7,
            Back = 0
        };

        explicit WalletMenu(std::optional<ChebyWallet::Wallet::WalletData>& wallet);

        WalletMenuChoice walletMenu();
    };
};