#include "ChebyChain.hpp"
#include "../Utils/Utils.hpp"
#include <chrono>
#include <cstddef>
#include <fstream>

std::uint64_t ChebyChain::Blockchain::getCurrentTimestamp() const
{
    return std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

ChebyChain::Blockchain::Blockchain()
{
    chain.emplace_back(
    0,
    getCurrentTimestamp(),
    "ChebyChain Genesis!",
    0
    );
}

void ChebyChain::Blockchain::addBlock(const std::string& data)
{
    chain.emplace_back(
    chain.back().getBlockIndex() + 1,
    getCurrentTimestamp(),
    data,
    chain.back().getBlockHash()
    );
}

void ChebyChain::Blockchain::addBlock(const Transaction& transaction)
{
    chain.emplace_back(
    chain.back().getBlockIndex() + 1,
    getCurrentTimestamp(),
    transaction,
    chain.back().getBlockHash()
    );
}

std::size_t ChebyChain::Blockchain::getBlockCount() const { return chain.size(); }

const ChebyChain::Block& ChebyChain::Blockchain::getBlock(std::size_t index) const { return chain.at(index); }

bool ChebyChain::Blockchain::isValid() const
{
    for (std::size_t blocks = 1; blocks < chain.size(); ++blocks)
    {
        const Block& current = chain[blocks];
        const Block& previous = chain[blocks - 1];

        if (current.getBlockPreviousHash() != previous.getBlockHash())
        {
            return false;
        }
        else if (current.getBlockHash() != current.calculateHash())
        {
            return false;
        }
    }

    return true;
}

bool ChebyChain::Blockchain::saveBlockchain(const std::string& path) const
{
    std::ofstream file(path, std::ios::binary | std::ios::trunc);

    if (!file)
    {
        return false;
    }

    if (!FileUtils::writeUint64(file, FileUtils::BLOCKCHAIN_MAGIC))
    {
        return false;
    }

    if (!FileUtils::writeUint32(file, FileUtils::BLOCKCHAIN_VERSION))
    {
        return false;
    }

    const std::uint64_t blockCount = chain.size();

    if (!FileUtils::writeUint64(file, blockCount))
    {
        return false;
    }

    for (const Block& block : chain)
    {
        if (!FileUtils::writeUint64(file, block.getBlockIndex()))
        {
            return false;
        }

        if (!FileUtils::writeUint64(file, block.getBlockTimestamp()))
        {
            return false;
        }

        if (!FileUtils::writeString(file, block.getBlockData()))
        {
            return false;
        }

        if (!FileUtils::writeUint64(file, block.getBlockPreviousHash()))
        {
            return false;
        }

        if (!FileUtils::writeUint64(file, block.getBlockHash()))
        {
            return false;
        }
    }

    return static_cast<bool>(file);
}

bool ChebyChain::Blockchain::loadBlockchain(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);

    if (!file)
    {
        return false;
    }

    std::uint64_t magic = 0;
    std::uint32_t version = 0;

    if (!FileUtils::readUint64(file, magic))
    {
        return false;
    }

    if (!FileUtils::readUint32(file, version))
    {
        return false;
    }

    if (magic != FileUtils::BLOCKCHAIN_MAGIC)
    {
        return false;
    }

    if (version != FileUtils::BLOCKCHAIN_VERSION)
    {
        return false;
    }

    std::uint64_t blockCount = 0;

    if (!FileUtils::readUint64(file, blockCount))
    {
        return false;
    }

    std::vector<Block> loadedChain;

    loadedChain.reserve(blockCount);

    for (std::uint64_t i = 0; i < blockCount; ++i)
    {
        std::uint64_t index = 0;
        std::uint64_t timestamp = 0;
        std::string data;
        std::uint64_t previousHash = 0;
        std::uint64_t savedHash = 0;

        if (!FileUtils::readUint64(file, index))
        {
            return false;
        }

        if (!FileUtils::readUint64(file, timestamp))
        {
            return false;
        }

        if (!FileUtils::readString(file, data))
        {
            return false;
        }

        if (!FileUtils::readUint64(file, previousHash))
        {
            return false;
        }

        if (!FileUtils::readUint64(file, savedHash))
        {
            return false;
        }

        Block block(
            index,
            timestamp,
            data,
            previousHash
        );

        if (block.getBlockHash() != savedHash)
        {
            return false;
        }

        if (!loadedChain.empty())
        {
            const Block& previous = loadedChain.back();

            if (block.getBlockPreviousHash() != previous.getBlockHash())
            {
                return false;
            }
        }

        loadedChain.emplace_back(block);
    }

    chain = std::move(loadedChain);

    return true;
}