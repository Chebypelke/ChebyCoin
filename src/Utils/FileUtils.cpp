#include "Utils.hpp"
#include "../ChebyHash/ChebyHash.hpp"
#include <cstdint>
#include <fstream>

bool FileUtils::writeUint32(std::ofstream& file, std::uint32_t value)
{
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));

    return static_cast<bool>(file);
}

bool FileUtils::readUint32(std::ifstream& file, std::uint32_t& value)
{
    file.read(reinterpret_cast<char*>(&value), sizeof(value));

    return static_cast<bool>(file);
}

bool FileUtils::writeUint64(std::ofstream& file, std::uint64_t value)
{
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));

    return static_cast<bool>(file);
}

bool FileUtils::readUint64(std::ifstream& file, std::uint64_t& value)
{
    file.read(reinterpret_cast<char*>(&value), sizeof(value));

    return static_cast<bool>(file);
}

bool FileUtils::writeHash128(std::ofstream& file, const ChebyHash::ChebyHash128::Hash128& value)
{
    return writeUint64(file, value.high) && writeUint64(file, value.low);
}

bool FileUtils::readHash128(std::ifstream& file, ChebyHash::ChebyHash128::Hash128& value)
{
    return readUint64(file, value.high) && readUint64(file, value.low);
}

