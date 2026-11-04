cmake_minimum_required(VERSION 3.20)

project(ChebyCoin LANGUAGES CXX)

# =========================
# Libraries
# =========================

# ChebyHash

add_library(ChebyHash STATIC
    src/ChebyHash/ChebyHash32.cpp
    src/ChebyHash/ChebyHash64.cpp
    src/ChebyHash/ChebyHash128/Hash128.cpp
    src/ChebyHash/ChebyHash128/ChebyHash128.cpp
)
target_include_directories(ChebyHash PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

# ChebySignature

add_library(ChebySignature STATIC
    src/ChebySignature/ChebySignature.cpp
)
target_include_directories(ChebySignature PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(ChebySignature PUBLIC
    ChebyHash
)


# =========================
# Executables
# =========================

# main-app - main chebycoin client app

add_executable(main-app
    # ChebyChain
    src/ChebyChain/Block.cpp
    src/ChebyChain/Blockchain.cpp
    # ChebyCoinApp
    src/ChebyCoinApp/Menus/MainMenu.cpp
    src/ChebyCoinApp/Menus/WalletMenu.cpp
    src/ChebyCoinApp/Menus/BlockchainMenu.cpp
    src/ChebyCoinApp/App.cpp
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
target_link_libraries(main-app PRIVATE
    ChebyHash 
    ChebySignature
)

# Testers(only tester and dependencies)
# ChebyHash32 Tester 

add_executable(chebyhash32-tester
    src/Utils/Utils.cpp
    src/Utils/RandomGenerators.cpp
    src/ChebyHash/Testers/ChebyHash32Tester.cpp
)
target_link_libraries(chebyhash32-tester PRIVATE 
    ChebyHash
)

# ChebyHash64 Tester 

add_executable(chebyhash64-tester
    src/Utils/Utils.cpp 
    src/Utils/RandomGenerators.cpp 
    src/ChebyHash/Testers/ChebyHash64Tester.cpp
)
target_link_libraries(chebyhash64-tester PRIVATE 
    ChebyHash
)

# ChebyHash128 Tester 

add_executable(chebyhash128-tester
    src/Utils/Utils.cpp 
    src/Utils/RandomGenerators.cpp 
    src/ChebyHash/Testers/ChebyHash128Tester.cpp
)
target_link_libraries(chebyhash128-tester PRIVATE 
    ChebyHash
)

# ChebyChain Tester 

add_executable(chebychain-tester
    src/Utils/Utils.cpp 
    src/Utils/FileUtils.cpp 
    src/Utils/RandomGenerators.cpp 
    src/ChebyChain/Block.cpp
    src/ChebyChain/Blockchain.cpp 
    src/ChebyWallet/ChebyWallet.cpp 
    src/Transactions/Transactions.cpp
    src/ChebyChain/Testers/ChebyChainTester.cpp
)
target_link_libraries(chebychain-tester PRIVATE
    ChebyHash 
    ChebySignature
)

# ChebySignature Tester - only chain tester binary

add_executable(chebysignature-tester
    src/Utils/Utils.cpp 
    src/Utils/RandomGenerators.cpp 
    src/ChebySignature/Testers/ChebySignatureTester.cpp
)
target_link_libraries(chebysignature-tester PRIVATE
    ChebyHash 
    ChebySignature
)


# ChebyWallet Tester - only wallet tester binary

add_executable(chebywallet-tester
    src/Utils/Utils.cpp 
    src/Utils/FileUtils.cpp 
    src/Utils/RandomGenerators.cpp 
    src/ChebyWallet/ChebyWallet.cpp
    src/ChebyWallet/Testers/ChebyWalletTester.cpp
    src/Transactions/Transactions.cpp
)
target_link_libraries(chebywallet-tester PRIVATE
    ChebyHash 
    ChebySignature
)