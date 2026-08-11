#include "ChebyChain.hpp"
#include "../ChebyHash/ChebyHash.hpp"
#include <string>

std::uint64_t ChebyChain::Block::calculateHash() const
{
    auto toHash = std::to_string(index) + "|" +
                std::to_string(timestamp) + "|" +
                data + "|" +
                std::to_string(previousHash);

    return ChebyHash::ChebyHash64::hash(toHash);
}

ChebyChain::Block::Block(std::uint64_t blockIndex, std::uint64_t blockTimestamp, std::string blockData, 
    std::uint64_t blockPreviousHash)
    : index(blockIndex), timestamp(blockTimestamp), data(blockData),
    previousHash(blockPreviousHash)
{
    hash = calculateHash();
}

std::uint64_t ChebyChain::Block::getBlockIndex() const { return index; }
std::uint64_t ChebyChain::Block::getBlockHash() const { return hash; }
std::uint64_t ChebyChain::Block::getBlockPreviousHash() const { return previousHash; }