#pragma once

#include <cstdint>
#include <string>

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
};