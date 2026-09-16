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

bool FileUtils::writeString(std::ofstream& file, const std::string& value)
{
    const std::uint64_t size = value.size();

    if (!writeUint64(file, size))
        return false;

    file.write(value.data(), static_cast<std::streamsize>(size));

    return static_cast<bool>(file);
}

bool FileUtils::readString(std::ifstream& file, std::string& value)
{
    std::uint64_t size;

    if (!readUint64(file, size))
        return false;

    value.resize(size);

    file.read(value.data(), static_cast<std::streamsize>(size));

    return static_cast<bool>(file);
}

bool FileUtils::writeTransaction(std::ofstream& file, const Transaction& transaction)
{
    if (!writeHash128(file, transaction.getFromAddress().value))
    {
        return false;
    }

    if (!writeHash128(file, transaction.getToAddress().value))
    {
        return false;
    }

    if (!writeUint64(file, transaction.getAmount()))
    {
        return false;
    }

    if (!writeHash128(file, transaction.getPublicKey().modulus))
    {
        return false;
    }

    if (!writeHash128(file, transaction.getPublicKey().publicExponent))
    {
        return false;
    }

    if (!writeHash128(file, transaction.getSignature()))
    {
        return false;
    }

    const std::uint8_t spawn = transaction.isSpawn() ? 1 : 0;
    file.write(reinterpret_cast<const char*>(&spawn), sizeof(spawn));

    return static_cast<bool>(file);
}

bool FileUtils::readTransaction(std::ifstream& file, Transaction& transaction)
{
    ChebyHash::ChebyHash128::Hash128 fromHash;
    ChebyHash::ChebyHash128::Hash128 toHash;

    std::uint64_t amount = 0;

    ChebySignature::PublicKey publicKey;
    ChebySignature::Hash128 signature;

    std::uint8_t spawn = 0;

    if (!readHash128(file, fromHash))
    {
        return false;
    }

    if (!readHash128(file, toHash))
    {
        return false;
    }

    if (!readUint64(file, amount))
    {
        return false;
    }

    if (!readHash128(file, publicKey.modulus))
    {
        return false;
    }

    if (!readHash128(file, publicKey.publicExponent))
    {
        return false;
    }

    if (!readHash128(file, signature))
    {
        return false;
    }
        

    file.read(reinterpret_cast<char*>(&spawn), sizeof(spawn));

    if (!file)
    {
        return false;
    } 

    ChebyWallet::Wallet::Address from;
    ChebyWallet::Wallet::Address to;

    from.value = fromHash;
    to.value = toHash;

    transaction = Transaction(
        from,
        to,
        amount,
        publicKey,
        signature,
        spawn != 0
    );

    return true;
}