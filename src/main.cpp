#include "ChebyHash/ChebyHash.hpp"
#include <cstdint>
#include <iostream>

int main()
{
    std::uint32_t y = 0x12345678;

    std::cout << std::hex << mix(0x00001111, y) << '\n';
    std::cout << std::hex << mix(0x11110000, y) << '\n';
    std::cout << std::hex << mix(0xFFFFFFFF, y) << '\n';
    std::cout << std::hex << mix(0x11111111, y) << '\n';
}
