#include "ChebyCoinApp.hpp"
#include "../Utils/Utils.hpp"
#include "../ChebyWallet/ChebyWallet.hpp"
#include "Menus/Menus.hpp"
#include <iostream>
#include <limits>

void ChebyCoinApp::App::run()
{
    clearScreen();

    bool run = true;

    while (run) 
    {
        auto mainMenuChoice = mainMenu.mainMenu();

        switch (mainMenuChoice) 
        {
        case ChebyCoinApp::MainMenu::MainMenuChoice::Wallet: 
        {
            clearScreen();

            WalletMenu walletMenu(wallet);
            
            bool inWalletMenu = true;

            while (inWalletMenu)
            {
                auto walletMenuChoice = walletMenu.walletMenu();

                switch (walletMenuChoice) 
                {
                case ChebyCoinApp::WalletMenu::WalletMenuChoice::CreateWallet:
                {
                    clearScreen();

                    std::cout << "[*] Generating wallet..." << std::endl;

                    wallet = ChebyWallet::Wallet::generateWallet();

                    std::cout << "[+] Generating wallet... DONE!" << std::endl << std::endl;

                    std::cout << "Wallet address: "
                            << std::hex
                            << wallet->address.value.high << wallet->address.value.low 
                            << std::dec
                            << std::endl;

                    std::cout << "Wallet publickey: "
                            << std::hex
                            << wallet->keyPair.publicKey.publicExponent.high
                            << wallet->keyPair.publicKey.publicExponent.low
                            << wallet->keyPair.publicKey.modulus.high
                            << wallet->keyPair.publicKey.modulus.low
                            << std::dec
                            << std::endl;
                    
                    std::cout << "To turn back press enter";
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cin.get();

                    clearScreen();
                    break;
                }
                case ChebyCoinApp::WalletMenu::WalletMenuChoice::LoadWallet:
                {
                    clearScreen();
                    
                    auto loadedWallet = ChebyWallet::Wallet::loadWallet("wallet.cbcwallet");

                    if (loadedWallet)
                    {
                        wallet = *loadedWallet;

                        std::cout << "[+] Wallet loaded!" << std::endl;
                    }
                    else  
                    {
                        std::cout << "[-] Failed to load wallet!" << std::endl;
                    }

                    break;
                }
                case ChebyCoinApp::WalletMenu::WalletMenuChoice::WalletInfo: // Заглушка
                    clearScreen();
                    break;
                case ChebyCoinApp::WalletMenu::WalletMenuChoice::Balance: // Заглушка
                    clearScreen();
                    break;
                case ChebyCoinApp::WalletMenu::WalletMenuChoice::SendCoins: // Заглушка
                    clearScreen();
                    break;
                case ChebyCoinApp::WalletMenu::WalletMenuChoice::Transactions: // Заглушка
                    clearScreen();
                    break;
                case ChebyCoinApp::WalletMenu::WalletMenuChoice::SaveWallet:
                {                    
                    clearScreen();

                    bool success = ChebyWallet::Wallet::saveWallet(*wallet, "wallet.cbcwallet");

                    if (success)
                    {
                        std::cout << "[+] Wallet saved!" << std::endl;
                    }
                    else
                    {
                        std::cout << "[-] Failed to save wallet!" << std::endl;
                    }

                    break;
                }
                case ChebyCoinApp::WalletMenu::WalletMenuChoice::Back:
                    inWalletMenu = false;
                    clearScreen();
                    break;
                }
            }
            break; 
        }
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