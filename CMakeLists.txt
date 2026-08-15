cmake_minimum_required(VERSION 3.20)

project(ChebyCoin)

add_executable(ChebyCoin
    # ChebyHash
    src/ChebyHash/ChebyHash32.cpp
    src/ChebyHash/ChebyHash64.cpp
    src/ChebyHash/Testers/ChebyHash32Tester.cpp
    src/ChebyHash/Testers/ChebyHash64Tester.cpp
    src/ChebyHash/Testers/ChebyHash128Tester.cpp
    src/ChebyHash/ChebyHash128/Hash128.cpp
    src/ChebyHash/ChebyHash128/ChebyHash128.cpp
    # ChebyChain
    src/ChebyChain/Block.cpp
    src/ChebyChain/Blockchain.cpp
    src/ChebyChain/Testers/ChebyChainTester.cpp
    # ChebyCoinApp
    src/ChebyCoinApp/Menus/MainMenu.cpp
    src/ChebyCoinApp/Menus/WalletMenu.cpp
    src/ChebyCoinApp/App.cpp
    # ChebySignature
    src/ChebySignature/ChebySignature.cpp
    src/ChebySignature/Testers/ChebySignatureTester.cpp 
    # ChebyWallet
    src/ChebyWallet/ChebyWallet.cpp
    src/ChebyWallet/Testers/ChebyWalletTester.cpp 
    # Utils
    src/Utils/RandomGenerators.cpp
    src/Utils/ScreenUtils.cpp
    src/Utils/FileUtils.cpp
    # main.cpp
    src/main.cpp
)