cmake_minimum_required(VERSION 3.20)

project(ChebyCoin)

add_executable(ChebyCoin
    src/ChebyHash/ChebyHash32.cpp
    src/ChebyHash/ChebyHash64.cpp
    src/ChebyHash/Testers/ChebyHash32Tester.cpp
    src/ChebyHash/Testers/ChebyHash64Tester.cpp
    src/ChebyChain/Block.cpp
    src/ChebyChain/Blockchain.cpp
    src/ChebyChain/Testers/ChebyChainTester.cpp
    src/Utils/RandomStringGenerator.cpp
    src/main.cpp
)