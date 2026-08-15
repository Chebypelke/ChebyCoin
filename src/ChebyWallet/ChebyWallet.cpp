#include "ChebyWallet.hpp"
#include <string>
#include <fstream>
#include <cstdint>

ChebyWallet::Wallet::Address ChebyWallet::Wallet::generateAddress(const ChebySignature::PublicKey& publicKey)
{
    const auto& publicKeyExponent = publicKey.publicExponent;
    const auto& publicKeyModulus = publicKey.modulus;
    auto data = std::to_string(publicKeyExponent.high) + ":" + std::to_string(publicKeyExponent.low) + 
                ":" + 
                std::to_string(publicKeyModulus.high) + ":" + std::to_string(publicKeyModulus.low);

    auto address = ChebyHash::ChebyHash128::hash(data);

    return Address{address};
}

ChebyWallet::Wallet::WalletData ChebyWallet::Wallet::generateWallet()
{
    auto keyPair = ChebySignature::Signature::generateKeyPair();
    const auto& publicKey = keyPair.publicKey;

    auto address = generateAddress(publicKey);

    return WalletData{keyPair, address};
}

namespace
{
    constexpr std::uint32_t WALLET_MAGIC = 0x4348574C; // "CHWL"
    constexpr std::uint32_t WALLET_VERSION = 1;

    bool writeUint64(std::ofstream& file, std::uint64_t value)
    {
        file.write(reinterpret_cast<const char*>(&value), sizeof(value));

        return static_cast<bool>(file);
    }

    bool readUint64(std::ifstream& file, std::uint64_t& value)
    {
        file.read(reinterpret_cast<char*>(&value), sizeof(value));

        return static_cast<bool>(file);
    }

    bool writeHash128(std::ofstream& file, const ChebyHash::ChebyHash128::Hash128& value)
    {
        return writeUint64(file, value.high) && writeUint64(file, value.low);
    }

    bool readHash128(std::ifstream& file, ChebyHash::ChebyHash128::Hash128& value)
    {
        return readUint64(file, value.high) && readUint64(file, value.low);
    }

    bool writeUint32(std::ofstream& file, std::uint32_t value)
    {
        file.write(reinterpret_cast<const char*>(&value), sizeof(value));

        return static_cast<bool>(file);
    }

    bool readUint32(std::ifstream& file, std::uint32_t& value)
    {
        file.read(reinterpret_cast<char*>(&value), sizeof(value));

        return static_cast<bool>(file);
    }
}

bool ChebyWallet::Wallet::saveWallet(const WalletData& wallet, const std::string& path)
{
    std::ofstream file(path, std::ios::binary | std::ios::trunc);

    if (!file)
    {
        return false;
    }

    if (!writeUint32(file, WALLET_MAGIC))
    {
        return false;
    }

    if (!writeUint32(file, WALLET_VERSION))
    {
        return false;
    }

    const auto& publicKey = wallet.keyPair.publicKey;
    const auto& privateKey = wallet.keyPair.privateKey;

    if (!writeHash128(file, publicKey.modulus))
    {
        return false;
    }

    if (!writeHash128(file, publicKey.publicExponent))
    {
        return false;
    }

    if (!writeHash128(file, privateKey.modulus))
    {
        return false;
    }

    if (!writeHash128(file, privateKey.privateExponent))
    {
        return false;
    }

    return static_cast<bool>(file);
}

std::optional<ChebyWallet::Wallet::WalletData> ChebyWallet::Wallet::loadWallet(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file)
    {
        return std::nullopt;
    }

    std::uint32_t magic = 0;
    std::uint32_t version = 0;

    if (!readUint32(file, magic))
    {
        return std::nullopt;
    }

    if (!readUint32(file, version))
    {
        return std::nullopt;
    }

    if (magic != WALLET_MAGIC)
    {
        return std::nullopt;
    }

    if (version != WALLET_VERSION)
    {
        return std::nullopt;
    }

    ChebySignature::KeyPair keyPair;

    if (!readHash128(file, keyPair.publicKey.modulus))
    {
        return std::nullopt;
    }

    if (!readHash128(file, keyPair.publicKey.publicExponent))
    {
        return std::nullopt;
    }

    if (!readHash128(file, keyPair.privateKey.modulus))
    {
        return std::nullopt;
    }

    if (!readHash128(file, keyPair.privateKey.privateExponent))
    {
        return std::nullopt;
    }

    if (keyPair.publicKey.modulus.high !=
        keyPair.privateKey.modulus.high ||
        keyPair.publicKey.modulus.low !=
        keyPair.privateKey.modulus.low)
    {
        return std::nullopt;
    }

    auto address = generateAddress(keyPair.publicKey);

    return WalletData{keyPair, address};
}