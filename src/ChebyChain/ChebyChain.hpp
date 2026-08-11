#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace ChebyChain {
    class Block
    {
    private:
        std::uint64_t index;
        std::uint64_t timestamp;
        std::string data;

        std::uint64_t previousHash;
        std::uint64_t hash;

    public:
        Block(
            std::uint64_t index,
            std::uint64_t timestamp,
            std::string data,
            std::uint64_t previousHash
        );

        std::uint64_t calculateHash() const;

        std::uint64_t getBlockIndex() const;
        std::uint64_t getBlockHash() const;
        std::uint64_t getBlockPreviousHash() const;
    };

    class Blockchain
    {
    private:
        std::vector<Block> chain;

        std::uint64_t getCurrentTimestamp() const;
    public:
        Blockchain();

        void addBlock(const std::string& data);
        std::size_t getBlockCount() const;
        const Block& getBlock(std::size_t index) const;
        bool isValid() const;
    };
}
