#pragma once

#include "../ChebyWallet/ChebyWallet.hpp"

class Transaction
{
private:
    ChebyWallet::Wallet::Address from;
    ChebyWallet::Wallet::Address to;
    std::uint64_t amount;

    ChebySignature::PublicKey publicKey;
    ChebySignature::Hash128 signature;

    bool spawn = false;

public:
    Transaction(
        const ChebyWallet::Wallet::Address& from,
        const ChebyWallet::Wallet::Address& to,
        std::uint64_t amount
    );

    Transaction(
        const ChebyWallet::Wallet::Address& to,
        std::uint64_t amount
    );

    Transaction(
        const ChebyWallet::Wallet::Address& from,
        const ChebyWallet::Wallet::Address& to,
        std::uint64_t amount,
        const ChebySignature::PublicKey& publicKey,
        const ChebySignature::Hash128& signature,
        bool spawn
    );

    std::string getSigningData() const;

    void sign(const ChebySignature::KeyPair& keyPair);

    bool verifySignature() const;
    bool isValid() const;

    std::uint64_t getAmount() const;
    const ChebyWallet::Wallet::Address& getFromAddress() const;
    const ChebyWallet::Wallet::Address& getToAddress() const;
    const ChebySignature::PublicKey& getPublicKey() const;
    const ChebySignature::Hash128& getSignature() const;
    bool isSpawn() const;
};