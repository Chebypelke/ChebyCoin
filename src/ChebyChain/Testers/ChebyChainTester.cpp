#include "ChebyChainTesters.hpp"
#include "../ChebyChain.hpp"
#include "../../Utils/Utils.hpp"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>

void ChebyChain::Testers::ChebyChainTester()
{
    Blockchain blockchain;
    int choice;
    std::string data;
    std::size_t blockIndex;
    bool run = true;

    while (run)
    {
        std::cout << "===== ChebyChain Tester =====" << std::endl;

        std::cout << "1. New block" << std::endl;
        std::cout << "2. Blocks count" << std::endl;
        std::cout << "3. Block by index" << std::endl;
        std::cout << "4. Validate blockchain" << std::endl;
        std::cout << "5. Save blockchain" << std::endl;
        std::cout << "6. Load blockchain" << std::endl;
        std::cout << "7. Transaction test" << std::endl;
        std::cout << "8. Get transactions data" << std::endl;
        std::cout << "0. Exit" << std::endl;

        std::cout << "Your choice: "; 
        if (!CLIUtils::readInt(choice))
        {
            std::cout << "ERROR: type number!" << std::endl; 
            continue;
        }

        switch (choice) {
        case 1:
        {
            CLIUtils::clearScreen();

            std::cout << "Type block data: ";

            if(!CLIUtils::readString(data))
            {
                break;
            }

            blockchain.addBlock(data);

            break;
        }
        case 2: 
        {            
            CLIUtils::clearScreen();

            std::cout << "Blocks count: " << blockchain.getBlockCount() << std::endl;
            
            break; 
        }
        case 3:
        {
            CLIUtils::clearScreen();

            std::cout << "Enter block index: ";
            
            if (!CLIUtils::readSizeT(blockIndex))
            {
                std::cout << "ERROR: type a non-negative number!" << std::endl; 
                break;
            }
            
            const Block& block = blockchain.getBlock(blockIndex);
            std::cout << "Block index: " << block.getBlockIndex() 
                                         << std::endl;

            std::cout << "Block hash: " << block.getBlockHash()
                                        << " (" << std::hex << block.getBlockHash() << ")" << std::dec
                                        << std::endl;

            std::cout << "Block previous hash: " << block.getBlockPreviousHash() 
                                                 << " (" << std::hex << block.getBlockPreviousHash() << ")" << std::dec
                                                 << std::endl;;

            break; 
        }
        case 4:
        {
            CLIUtils::clearScreen();

            if (!blockchain.isValid())
            {
                std::cout << "Blockchain is invalid!" << std::endl;
                break;
            }
            
            std::cout << "Blockchain is valid!" << std::endl;

            break;
        }
        case 5:
        {
            CLIUtils::clearScreen();

            if (!blockchain.saveBlockchain("blockchain.cbcchain"))
            {
                std::cout << "Blockchain not saved!" << std::endl;
                break;
            }
            
            std::cout << "Blockchain saved!" << std::endl;
            break;
        }
        case 6:
        {
            CLIUtils::clearScreen();

            if (!blockchain.loadBlockchain("blockchain.cbcchain"))
            {
                std::cout << "Blockchain not loaded!" << std::endl;
                break;
            }

            std::cout << "Blockchain loaded" << std::endl;
            break;
        }
        case 7:
        {
            CLIUtils::clearScreen();

            ChebyWallet::Wallet::WalletData walletA = ChebyWallet::Wallet::generateWallet();
            ChebyWallet::Wallet::WalletData walletB = ChebyWallet::Wallet::generateWallet();

            Transaction transaction(walletA.address, walletB.address, 100);

            transaction.sign(walletA.keyPair);

            if (transaction.verifySignature())
            {
                std::cerr << "SIGNATURE OK!\n";
            }
            else
            {
                std::cerr << "SIGNATURE BAD!\n";
            }

            if (transaction.isValid())
            {
                std::cerr << "VALID!\n";
                blockchain.addBlock(transaction);
            }
            else
            {
                std::cerr << "INVALID!\n";
            }

            break;
        }
        case 8:
        {
            CLIUtils::clearScreen();

            for (std::size_t blocks = 1; blocks < blockchain.getBlockCount(); ++blocks)
            {
                const Block& current = blockchain.getBlock(blocks);

                if (current.getBlockTransaction())
                {
                    std::cout << current.getBlockTransaction()->getSigningData() << std::endl;
                }
            }

            break;
        }
        case 0:
            CLIUtils::clearScreen();

            run = false;

            break;
        }
    }
}

int main()
{
    ChebyChain::Testers::ChebyChainTester();
}