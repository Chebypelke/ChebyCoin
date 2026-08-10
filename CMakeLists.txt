cmake_minimum_required(VERSION 3.20)

project(ChebyCoin)

add_executable(ChebyCoin
    src/ChebyHash/ChebyHash32.cpp
    src/ChebyHash/Testers/ChebyHash32Tester.cpp
    src/main.cpp
)