#pragma once

#include "../ChebyWallet/ChebyWallet.hpp"

class Transaction
{
public:
    Transaction(
        const ChebyWallet::Wallet::Address& from,
        const ChebyWallet::Wallet::Address& to,
        uint64_t amount
    );

    std::string getSigningData() const;

    void sign(const ChebySignature::KeyPair& keyPair);

    bool verifySignature() const;
    bool isValid() const;

private:
    ChebyWallet::Wallet::Address from;
    ChebyWallet::Wallet::Address to;
    uint64_t amount;

    ChebySignature::PublicKey publicKey;
    ChebySignature::Hash128 signature;
};