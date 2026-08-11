#include "ChebyChain.hpp"
#include <chrono>
#include <cstddef>

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