cmake_minimum_required(VERSION 3.20)

project(ChebyCoin LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(FLTK CONFIG REQUIRED)

block() # Libs
    add_library(utils-lib STATIC # Not public API. Do not use this lol.
        src/Utils/Random.cpp
        src/Utils/CLIUtils.cpp
        src/Utils/FileUtils.cpp
    )
    target_include_directories(utils-lib
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        PRIVATE ${PROJECT_SOURCE_DIR}/src
    )

    add_library(chebyhash-lib STATIC
        src/Modules/ChebyHash/ChebyHash32.cpp
        src/Modules/ChebyHash/ChebyHash64.cpp
        src/Modules/ChebyHash/ChebyHash128/Hash128.cpp
        src/Modules/ChebyHash/ChebyHash128/ChebyHash128.cpp
    )
    target_include_directories(chebyhash-lib
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        PRIVATE ${PROJECT_SOURCE_DIR}/src
    )

    add_library(chebysignature-lib STATIC
        src/Modules/ChebySignature/ChebySignature.cpp
    )
    target_include_directories(chebysignature-lib
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        PRIVATE ${PROJECT_SOURCE_DIR}/src
    )
    target_link_libraries(chebysignature-lib PRIVATE
        chebyhash-lib
        utils-lib
    )
endblock()

block() # Main client apps
    # main-app - main chebycoin client app
    add_executable(main-app
        # ChebyChain
        src/Modules/ChebyChain/Block.cpp
        src/Modules/ChebyChain/Blockchain.cpp
        # ChebyCoinApp
        src/Apps/ChebyCoinApp/Menus/MainMenu.cpp
        src/Apps/ChebyCoinApp/Menus/WalletMenu.cpp
        src/Apps/ChebyCoinApp/Menus/BlockchainMenu.cpp
        src/Apps/ChebyCoinApp/App.cpp
        # ChebyWallet
        src/Modules/ChebyWallet/ChebyWallet.cpp
        # Transactions
        src/Modules/Transactions/Transactions.cpp
        # main.cpp
        src/Apps/ChebyCoinApp/main.cpp
    )
    target_link_libraries(main-app PRIVATE
        chebysignature-lib
        chebyhash-lib 
        utils-lib
    )

    add_executable(chebyhash-gui-app
        src/Apps/ChebyHashGui/main.cpp
        src/Apps/ChebyHashGui/MainWindow.cpp
        src/Apps/ChebyHashGui/Tabs/CalculatorTab/CalculatorTab.cpp
    )
    target_link_libraries(chebyhash-gui-app PRIVATE
       chebyhash-lib
       fltk::fltk
    )
endblock()

block() # Testers
    # ChebyHash32 Tester 
    add_executable(chebyhash32-tester
        src/Modules/ChebyHash/Testers/ChebyHash32Tester.cpp
    )
    target_link_libraries(chebyhash32-tester PRIVATE 
        chebyhash-lib
        utils-lib
    )

    # ChebyHash64 Tester 

    add_executable(chebyhash64-tester
        src/Modules/ChebyHash/Testers/ChebyHash64Tester.cpp
    )
    target_link_libraries(chebyhash64-tester PRIVATE 
        chebyhash-lib
        utils-lib
    )

    # ChebyHash128 Tester 

    add_executable(chebyhash128-tester
        src/Modules/ChebyHash/Testers/ChebyHash128Tester.cpp
    )
    target_link_libraries(chebyhash128-tester PRIVATE 
        chebyhash-lib
        utils-lib
    )

    # ChebyChain Tester 

    add_executable(chebychain-tester
        src/Modules/ChebyChain/Block.cpp
        src/Modules/ChebyChain/Blockchain.cpp 
        src/Modules/ChebyWallet/ChebyWallet.cpp 
        src/Modules/Transactions/Transactions.cpp
        src/Modules/ChebyChain/Testers/ChebyChainTester.cpp
    )
    target_link_libraries(chebychain-tester PRIVATE
        chebysignature-lib
        chebyhash-lib 
        utils-lib
    )

    # ChebySignature Tester - only chain tester binary

    add_executable(chebysignature-tester
        src/Modules/ChebySignature/Testers/ChebySignatureTester.cpp
    )
    target_link_libraries(chebysignature-tester PRIVATE
        chebysignature-lib
        chebyhash-lib 
        utils-lib
    )

    # ChebyWallet Tester - only wallet tester binary

    add_executable(chebywallet-tester
        src/Modules/ChebyWallet/ChebyWallet.cpp
        src/Modules/ChebyWallet/Testers/ChebyWalletTester.cpp
        src/Modules/Transactions/Transactions.cpp
    )
    target_link_libraries(chebywallet-tester PRIVATE
        chebysignature-lib
        chebyhash-lib 
        utils-lib
    )
endblock()