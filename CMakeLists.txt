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
    src/ChebyCoinApp/MainMenu.cpp
    src/ChebyCoinApp/App.cpp
    # Utils
    src/Utils/RandomStringGenerator.cpp
    src/Utils/ScreenUtils.cpp
    # main.cpp
    src/main.cpp
)