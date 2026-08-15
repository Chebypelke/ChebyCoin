#include "ChebyWallet.hpp"
#include <string>

ChebyWallet::Wallet::Address ChebyWallet::Wallet::generateAddress(const ChebySignature::PublicKey& publicKey)
{
    const auto& publicKeyExponent = publicKey.publicExponent;
    const auto& publicKeyModulus = publicKey.modulus;
    auto data = std::to_string(publicKeyExponent.high) + ":" + std::to_string(publicKeyExponent.low) + 
                ":" + 
                std::to_string(publicKeyModulus.high) + ":" + std::to_string(publicKeyModulus.low);

    auto address = ChebyHash::ChebyHash128::hash(data);

    return Address{address};
}

ChebyWallet::Wallet::WalletData ChebyWallet::Wallet::generateWallet()
{
    auto keyPair = ChebySignature::Signature::generateKeyPair();
    const auto& publicKey = keyPair.publicKey;

    auto address = generateAddress(publicKey);

    return WalletData{keyPair, address};
}