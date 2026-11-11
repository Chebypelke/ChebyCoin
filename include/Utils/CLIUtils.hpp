#pragma once 

#include <cstdint>
#include <string>
#include <ChebyHash/ChebyHash.hpp>

namespace CLIUtils 
{
    void clearScreen();

    bool readInt(int& int_data);
    bool readSizeT(std::size_t& size_t_data);
    bool readString(std::string& string_data);
    bool readUInt32(std::uint32_t& uint32_t_data);
    bool readHash128(ChebyHash::ChebyHash128::Hash128& hash);
    bool readDouble(double& double_data);
}