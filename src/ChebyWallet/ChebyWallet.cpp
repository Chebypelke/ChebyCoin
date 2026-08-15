#include "ChebyWallet.hpp"
#include "../Utils/Utils.hpp"
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



bool ChebyWallet::Wallet::saveWallet(const WalletData& wallet, const std::string& path)
{
    std::ofstream file(path, std::ios::binary | std::ios::trunc);

    if (!file)
    {
        return false;
    }

    if (!FileUtils::writeUint64(file, FileUtils::WALLET_MAGIC))
    {
        return false;
    }

    if (!FileUtils::writeUint32(file, FileUtils::WALLET_VERSION))
    {
        return false;
    }

    const auto& publicKey = wallet.keyPair.publicKey;
    const auto& privateKey = wallet.keyPair.privateKey;

    if (!FileUtils::writeHash128(file, publicKey.modulus))
    {
        return false;
    }

    if (!FileUtils::writeHash128(file, publicKey.publicExponent))
    {
        return false;
    }

    if (!FileUtils::writeHash128(file, privateKey.modulus))
    {
        return false;
    }

    if (!FileUtils::writeHash128(file, privateKey.privateExponent))
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

    std::uint64_t magic = 0;
    std::uint32_t version = 0;

    if (!FileUtils::readUint64(file, magic))
    {
        return std::nullopt;
    }

    if (!FileUtils::readUint32(file, version))
    {
        return std::nullopt;
    }

    if (magic != FileUtils::WALLET_MAGIC)
    {
        return std::nullopt;
    }

    if (version != FileUtils::WALLET_VERSION)
    {
        return std::nullopt;
    }

    ChebySignature::KeyPair keyPair;

    if (!FileUtils::readHash128(file, keyPair.publicKey.modulus))
    {
        return std::nullopt;
    }

    if (!FileUtils::readHash128(file, keyPair.publicKey.publicExponent))
    {
        return std::nullopt;
    }

    if (!FileUtils::readHash128(file, keyPair.privateKey.modulus))
    {
        return std::nullopt;
    }

    if (!FileUtils::readHash128(file, keyPair.privateKey.privateExponent))
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