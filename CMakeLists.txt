cmake_minimum_required(VERSION 3.20)

project(ChebyCoin)

add_executable(main-app
    # ChebyHash
    src/ChebyHash/ChebyHash32.cpp
    src/ChebyHash/ChebyHash64.cpp
    src/ChebyHash/ChebyHash128/Hash128.cpp
    src/ChebyHash/ChebyHash128/ChebyHash128.cpp
    # ChebyChain
    src/ChebyChain/Block.cpp
    src/ChebyChain/Blockchain.cpp
    # ChebyCoinApp
    src/ChebyCoinApp/Menus/MainMenu.cpp
    src/ChebyCoinApp/Menus/WalletMenu.cpp
    src/ChebyCoinApp/Menus/BlockchainMenu.cpp
    src/ChebyCoinApp/App.cpp
    # ChebySignature
    src/ChebySignature/ChebySignature.cpp
    # ChebyWallet
    src/ChebyWallet/ChebyWallet.cpp
    # Transactions
    src/Transactions/Transactions.cpp
    # Utils
    src/Utils/RandomGenerators.cpp
    src/Utils/Utils.cpp
    src/Utils/FileUtils.cpp
    # main.cpp
    src/main.cpp
)

add_executable(chebyhash32-tester
    src/ChebyHash/ChebyHash32.cpp
    src/Utils/Utils.cpp
    src/Utils/RandomGenerators.cpp
    src/ChebyHash/Testers/ChebyHash32Tester.cpp
)

add_executable(chebyhash64-tester
    src/Utils/Utils.cpp 
    src/Utils/RandomGenerators.cpp 
    src/ChebyHash/ChebyHash64.cpp 
    src/ChebyHash/Testers/ChebyHash64Tester.cpp
)

add_executable(chebyhash128-tester
    src/Utils/Utils.cpp 
    src/Utils/RandomGenerators.cpp 
    src/ChebyHash/ChebyHash128/ChebyHash128.cpp 
    src/ChebyHash/ChebyHash128/Hash128.cpp 
    src/ChebyHash/Testers/ChebyHash128Tester.cpp
)

add_executable(chebychain-tester
    src/Utils/Utils.cpp 
    src/Utils/FileUtils.cpp 
    src/ChebyChain/Block.cpp
    src/ChebyChain/Blockchain.cpp 
    src/Utils/RandomGenerators.cpp 
    src/ChebyHash/ChebyHash64.cpp 
    src/ChebyHash/ChebyHash128/ChebyHash128.cpp 
    src/ChebyHash/ChebyHash128/Hash128.cpp 
    src/ChebySignature/ChebySignature.cpp
    src/ChebyWallet/ChebyWallet.cpp 
    src/Transactions/Transactions.cpp
    src/ChebyChain/Testers/ChebyChainTester.cpp
)

add_executable(chebysignature-tester
    src/Utils/Utils.cpp 
    src/Utils/RandomGenerators.cpp 
    src/ChebyHash/ChebyHash128/ChebyHash128.cpp 
    src/ChebyHash/ChebyHash128/Hash128.cpp 
    src/ChebySignature/ChebySignature.cpp 
    src/ChebySignature/Testers/ChebySignatureTester.cpp
)

add_executable(chebywallet-tester
    src/Utils/Utils.cpp 
    src/Utils/FileUtils.cpp 
    src/Utils/RandomGenerators.cpp 
    src/ChebyHash/ChebyHash128/ChebyHash128.cpp 
    src/ChebyHash/ChebyHash128/Hash128.cpp 
    src/ChebySignature/ChebySignature.cpp 
    src/ChebyWallet/ChebyWallet.cpp
    src/ChebyWallet/Testers/ChebyWalletTester.cpp
)