#include "ChebyCoinApp.hpp"
#include "../Utils/Utils.hpp"
#include "../ChebyWallet/ChebyWallet.hpp"
#include "Menus/Menus.hpp"
#include <iostream>
#include <limits>

void ChebyCoinApp::App::runWalletMenu()
{
    WalletMenu walletMenu(wallet);

    bool inWalletMenu = true;

    while (inWalletMenu)
    {
        auto walletMenuChoice = walletMenu.walletMenu();

        switch (walletMenuChoice)
        {
        case ChebyCoinApp::WalletMenu::WalletMenuChoice::CreateWallet:
        {
            CLIUtils::clearScreen();

            std::cerr << "[+] Generating wallet...";

            wallet = ChebyWallet::Wallet::generateWallet();

            std::cerr << " DONE!" << std::endl << std::endl;

            std::cout << "Wallet address: " << std::hex << wallet->address.value.high << wallet->address.value.low
                      << std::dec << std::endl;

            std::cout << "Wallet publickey: " << std::hex << wallet->keyPair.publicKey.publicExponent.high
                      << wallet->keyPair.publicKey.publicExponent.low << wallet->keyPair.publicKey.modulus.high
                      << wallet->keyPair.publicKey.modulus.low << std::dec << std::endl;

            std::cout << "To turn back press enter";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            CLIUtils::clearScreen();
            break;
        }
        case ChebyCoinApp::WalletMenu::WalletMenuChoice::LoadWallet:
        {
            CLIUtils::clearScreen();

            std::cerr << "[*] Loading wallet...";

            auto loadedWallet = ChebyWallet::Wallet::loadWallet("wallet.cbcwallet");

            if (loadedWallet)
            {
                wallet = *loadedWallet;

                std::cerr << " DONE!" << std::endl;
            }
            else
            {
                std::cerr << " FAILED!" << std::endl;
            }

            std::cout << "To turn back press enter";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            CLIUtils::clearScreen();
            break;
        }
        case ChebyCoinApp::WalletMenu::WalletMenuChoice::WalletInfo:
        {
            CLIUtils::clearScreen();

            std::cerr << "[*] Reading wallet info...";
            std::cerr << " DONE!" << std::endl;

            std::cout << "Wallet address: " << std::hex << wallet->address.value.high << wallet->address.value.low
                      << std::dec << std::endl;

            std::cout << "Wallet publickey: " << std::hex << wallet->keyPair.publicKey.publicExponent.high
                      << wallet->keyPair.publicKey.publicExponent.low << wallet->keyPair.publicKey.modulus.high
                      << wallet->keyPair.publicKey.modulus.low << std::dec << std::endl;

            std::cout << "Wallet privatekey: " << std::hex << wallet->keyPair.privateKey.privateExponent.high
                      << wallet->keyPair.privateKey.privateExponent.low << wallet->keyPair.privateKey.modulus.high
                      << wallet->keyPair.privateKey.modulus.low << std::dec << std::endl;

            std::cerr << "[*] Verifying keys...";

            ChebySignature::Hash128 messageHash{
                5643093659353030982ULL, // FANFORIN
                6076003192308203604ULL  // TURNITUP
            };

            ChebySignature::PrivateKey privateKey = wallet->keyPair.privateKey;
            ChebySignature::PublicKey publicKey = wallet->keyPair.publicKey;
            ChebySignature::Hash128 signature = ChebySignature::Signature::sign(messageHash, privateKey);
            ChebySignature::Hash128 verified = ChebySignature::Signature::verify(signature, publicKey);

            auto expected = ChebyHash::ChebyHash128::mod(messageHash, publicKey.modulus);

            bool valid = verified.high == expected.high && verified.low == expected.low;

            std::cerr << " DONE!" 
                      << std::endl;

            std::cout << "Verified: " 
                      << (valid ? "YES" : "NO") 
                      << std::endl;

            std::cout << "To turn back press enter";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            CLIUtils::clearScreen();

            break;
        }
        case ChebyCoinApp::WalletMenu::WalletMenuChoice::Balance: // Заглушка
            CLIUtils::clearScreen();
            break;
        case ChebyCoinApp::WalletMenu::WalletMenuChoice::SendCoins: // Заглушка
            CLIUtils::clearScreen();
            break;
        case ChebyCoinApp::WalletMenu::WalletMenuChoice::Transactions: // Заглушка
            CLIUtils::clearScreen();
            break;
        case ChebyCoinApp::WalletMenu::WalletMenuChoice::SaveWallet:
        {
            CLIUtils::clearScreen();

            std::cerr << "[*] Saving wallet...";

            bool success = ChebyWallet::Wallet::saveWallet(*wallet, "wallet.cbcwallet");

            if (success)
            {
                std::cout << " DONE!" << std::endl;
            }
            else
            {
                std::cout << " FAILED!" << std::endl;
            }

            std::cout << "To turn back press enter";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            CLIUtils::clearScreen();
            break;
        }
        case ChebyCoinApp::WalletMenu::WalletMenuChoice::Back:
            CLIUtils::clearScreen();
            inWalletMenu = false;
            break;
        }
    }
}

void ChebyCoinApp::App::runBlockchainMenu()
{
    BlockchainMenu blockchainMenu(blockchain);

    bool inBlockchainMenu = true;

    while (inBlockchainMenu)
    {
        auto blockchainMenuChoice = blockchainMenu.blockchainMenu();

        switch (blockchainMenuChoice) 
        {
        case ChebyCoinApp::BlockchainMenu::BlockchainMenuChoice::LoadBlockchain:
        {
            CLIUtils::clearScreen();

            std::cerr << "[+] Loading blockchain...";

            blockchain.emplace();

            if (!blockchain->loadBlockchain("blockchain.cbcchain"))
            {
                std::cerr << " FAILED!" << std::endl << std::endl;
                blockchain.reset();
                break;
            }

            std::cerr << " DONE!" << std::endl << std::endl;

            std::cout << "To turn back press enter";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            CLIUtils::clearScreen();
            break;
        }
        case ChebyCoinApp::BlockchainMenu::BlockchainMenuChoice::BlockchainInfo:
        {
            CLIUtils::clearScreen();

            std::cerr << "[*] Reading blockchain info...";
            std::cerr << " DONE!" 
                      << std::endl;

            std::cout << "Blocks count: " << blockchain->getBlockCount() 
                      << std::endl;
            
            std::cout << "To turn back press enter";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            CLIUtils::clearScreen();
            break;
        }
        case ChebyCoinApp::BlockchainMenu::BlockchainMenuChoice::ValidateBlockchain:
        {
            CLIUtils::clearScreen();

            std::cerr << "[*] Validating blockchain...";

            bool valid = blockchain->isValid();

            std::cerr << " DONE!" 
                      << std::endl;
            
            std::cout << "Verified: " 
                      << (valid ? "YES" : "NO") 
                      << std::endl;

            std::cout << "To turn back press enter";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            CLIUtils::clearScreen();
            break;
        }
        case ChebyCoinApp::BlockchainMenu::BlockchainMenuChoice::ShowBlock:
        {
            CLIUtils::clearScreen();

            size_t blockNumber = 0;

            std::cout << "Enter block number: ";

            if (!CLIUtils::readSizeT(blockNumber)) {
		        std::cout << "ERROR: type a non-negative number!" << std::endl; 
		        continue;
	        }

            std::cerr << "[*] We locate block...";
            
            auto blockIndex = blockNumber - 1;

            if (blockNumber == 0)
            {
                std::cerr << " FAILED!" << std::endl;

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

                CLIUtils::clearScreen();
                break;
            }

            if (blockNumber > blockchain->getBlockCount())
            {
                std::cerr << " FAILED!" << std::endl;

                std::cout << "To turn back press enter";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();

                CLIUtils::clearScreen();
                break;
            }

            std::cerr << " DONE!" << std::endl;

            const ChebyChain::Block& block = blockchain->getBlock(blockIndex);

            std::cout << "Block index: " << block.getBlockIndex() 
                      << std::endl;

            std::cout << "Block hash: " << block.getBlockHash()
                      << " (" << std::hex << block.getBlockHash() << ")" << std::dec
                      << std::endl;
            
            std::cout << "Block previous hash: " << block.getBlockPreviousHash() 
                      << " (" << std::hex << block.getBlockPreviousHash() << ")" << std::dec
                      << std::endl;;

            std::cout << "To turn back press enter";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();

            CLIUtils::clearScreen();

            break; 
        }
        case ChebyCoinApp::BlockchainMenu::BlockchainMenuChoice::Back:
            CLIUtils::clearScreen();
            inBlockchainMenu = false;
            break;
        }
    }
}

void ChebyCoinApp::App::run()
{
    CLIUtils::clearScreen();

    bool run = true;

    while (run) 
    {
        auto mainMenuChoice = mainMenu.mainMenu();

        switch (mainMenuChoice) 
        {
        case ChebyCoinApp::MainMenu::MainMenuChoice::Wallet: 
        {
            CLIUtils::clearScreen();

            runWalletMenu();

            break;
        }
        case ChebyCoinApp::MainMenu::MainMenuChoice::Transactions: // Заглушка 
            CLIUtils::clearScreen();
            break; 
        case ChebyCoinApp::MainMenu::MainMenuChoice::Blockchain: 
        {
            CLIUtils::clearScreen();

            runBlockchainMenu();

            break; 
        }
        case ChebyCoinApp::MainMenu::MainMenuChoice::Mining: // Заглушка
            CLIUtils::clearScreen();
            break; 
        case ChebyCoinApp::MainMenu::MainMenuChoice::Exit: // Заглушка
            CLIUtils::clearScreen();
            run = false;
            break;
        }
    }
}