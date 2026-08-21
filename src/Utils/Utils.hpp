#include "../ChebyHash/ChebyHash.hpp"
#include <string>

std::string RandomStringGenerator(size_t length);
std::string RandomNumberGenerator(size_t length);
void clearScreen();

namespace FileUtils {
    constexpr std::uint64_t WALLET_MAGIC = 0x43484357414C4C45;      // "CHCWALLE"
    constexpr std::uint64_t BLOCKCHAIN_MAGIC = 0x434843424C4F434B; // "CHCBLOCK"
    constexpr std::uint32_t WALLET_VERSION = 1;
    constexpr std::uint32_t BLOCKCHAIN_VERSION = 1;

    bool writeUint32(std::ofstream& file, std::uint32_t value);
    bool readUint32(std::ifstream& file, std::uint32_t& value);
    bool writeUint64(std::ofstream& file, std::uint64_t value);
    bool readUint64(std::ifstream& file, std::uint64_t& value);
    bool writeHash128(std::ofstream& file, const ChebyHash::ChebyHash128::Hash128& value);
    bool readHash128(std::ifstream& file, ChebyHash::ChebyHash128::Hash128& value);
    bool writeString(std::ofstream& file, const std::string& value);
    bool readString(std::ifstream& file, std::string& value);
}