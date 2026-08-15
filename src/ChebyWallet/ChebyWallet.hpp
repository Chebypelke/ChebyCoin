#pragma once

#include "../ChebyHash/ChebyHash.hpp"
#include "../ChebySignature/ChebySignature.hpp"
#include <optional>
#include <string>

namespace ChebyWallet 
{
    class Wallet
    {
    public:
        struct Address 
        {
            ChebyHash::ChebyHash128::Hash128 value;
        };

        struct WalletData
        {
            ChebySignature::KeyPair keyPair;
            Address address;
        };
        
        static Address generateAddress(const ChebySignature::PublicKey& publicKey);
        static WalletData generateWallet();

        static bool saveWallet(const WalletData& wallet, const std::string& path);
        static std::optional<WalletData> loadWallet(const std::string& path);
    };
};