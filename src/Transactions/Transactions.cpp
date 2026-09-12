#include "Transactions.hpp"
#include <cstdint>
#include <string>

Transaction::Transaction(
    const ChebyWallet::Wallet::Address& from, 
    const ChebyWallet::Wallet::Address& to,
    uint64_t amount
) : from(from), to(to), amount(amount)
{
}

std::string Transaction::getSigningData() const
{
    std::string signingData = std::to_string(from.value.high) + ":" +
                              std::to_string(from.value.low) + "|" +
                              std::to_string(to.value.high) + ":" +
                              std::to_string(to.value.low) + "|" +
                              std::to_string(amount);

    return signingData;
}

void Transaction::sign(const ChebySignature::KeyPair& keyPair)
{
    ChebyHash::ChebyHash128::Hash128 signingDataHash = ChebyHash::ChebyHash128::hash(getSigningData());
    ChebySignature::Hash128 dataSignature = ChebySignature::Signature::sign(signingDataHash, keyPair.privateKey);

    Transaction::signature = dataSignature;
    Transaction::publicKey = keyPair.publicKey;
}

bool Transaction::verifySignature() const
{
    ChebyHash::ChebyHash128::Hash128 signingDataHash = ChebyHash::ChebyHash128::hash(getSigningData());
    signingDataHash = ChebyHash::ChebyHash128::mod(signingDataHash, publicKey.modulus);

    ChebySignature::Hash128 messageHash = ChebySignature::Signature::verify(signature, publicKey);

    ChebyWallet::Wallet::Address addressFromPublicKey = ChebyWallet::Wallet::generateAddress(publicKey);

    if ((signingDataHash.high == messageHash.high && signingDataHash.low == messageHash.low) &&
        (addressFromPublicKey.value.high == from.value.high && addressFromPublicKey.value.low == from.value.low)
    )
    {
        return true;
    }
    
    return false;
}

bool Transaction::isValid() const
{
    if (verifySignature())
    {
        if (amount == 0)
        {
            return false;
        }

        return true;
    }

    return false;
}

std::uint64_t Transaction::getAmount() const { return amount; }
const ChebyWallet::Wallet::Address& Transaction::getFromAddress() const { return from; }
const ChebyWallet::Wallet::Address& Transaction::getToAddress() const { return to; }