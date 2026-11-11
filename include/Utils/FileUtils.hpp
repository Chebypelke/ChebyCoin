#pragma once 

#include <cstdint>
#include <fstream>
#include <ChebyHash/ChebyHash.hpp>
#include <Transactions/Transactions.hpp>

namespace FileUtils 
{   
    bool writeUint32(std::ofstream& file, std::uint32_t value);
    bool readUint32(std::ifstream& file, std::uint32_t& value);
    bool writeUint64(std::ofstream& file, std::uint64_t value);
    bool readUint64(std::ifstream& file, std::uint64_t& value);
    bool writeHash128(std::ofstream& file, const ChebyHash::ChebyHash128::Hash128& value);
    bool readHash128(std::ifstream& file, ChebyHash::ChebyHash128::Hash128& value);
    bool writeString(std::ofstream& file, const std::string& value);
    bool readString(std::ifstream& file, std::string& value);
    bool writeTransaction(std::ofstream& file, const Transaction& value);
    bool readTransaction(std::ifstream& file, Transaction& value);
}