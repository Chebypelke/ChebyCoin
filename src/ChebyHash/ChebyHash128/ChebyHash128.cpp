#include "../ChebyHash.hpp"

#include <bit>
#include <cstdint>

constexpr auto ROUND_COUNT = 32;

void ChebyHash::ChebyHash128::round(Hash128& x, Hash128& y)
{
    y = add(y, x);
    x = xorValues(x, y);
    
    y = rotr(y, 13);
    x = rotl(x, 17);

    y = xorValues(y, x);
    x = add(x, y);
}

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::mix(Hash128 x, Hash128 y)
{
    for (auto i = 0; i < ROUND_COUNT; ++i)
    {
        round(x, y);
    }

    return x;
}

ChebyHash::ChebyHash128::Hash128 ChebyHash::ChebyHash128::hash(std::string_view input)
{
    std::uint64_t byte = 0;

    Hash128 x{0, 0};
    Hash128 y{0, 0};

    for (std::size_t i = 0; i < input.size(); ++i)
    {
        byte = static_cast<std::uint64_t>(
            static_cast<unsigned char>(input[i])
        );

        if (i % 2 == 0)
        {
            x.high ^= std::__rotl(byte, 3);
            x.low ^= std::__rotr(byte, 7);
        }

        else
        {
            y.high ^= std::__rotl(byte, 5);
            y.low ^= std::__rotr(byte, 2);
        }
    }

    return mix(x, y);
}