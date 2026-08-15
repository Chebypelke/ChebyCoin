#pragma once

#include "../ChebyHash/ChebyHash.hpp"
#include "../ChebySignature/ChebySignature.hpp"

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
    };
};