#include "ChebyChain.hpp"
#include <chrono>
#include <cstddef>

std::uint64_t Blockchain::getCurrentTimestamp() const
{
    return std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}

Blockchain::Blockchain()
{
    chain.emplace_back(
    0,
    getCurrentTimestamp(),
    "ChebyChain Genesis!",
    0
    );
}

void Blockchain::addBlock(const std::string& data)
{
    chain.emplace_back(
    chain.back().getBlockIndex() + 1,
    getCurrentTimestamp(),
    data,
    chain.back().getBlockHash()
    );
}

std::size_t Blockchain::getBlockCount() const { return chain.size(); }

const Block& Blockchain::getBlock(std::size_t index) const { return chain.at(index); }