#pragma once

#include <cstdint>
#include <string_view>

/**
 * @defgroup ChebyHash ChebyHash
 * @brief Experimental hashing library.
 *
 * @warning
 * ChebyHash is NOT cryptographically secure.
 * Do not use it for passwords, authentication,
 * digital signatures or key derivation.
 */

namespace ChebyHash
{
    /**
     * @brief Number of mixing rounds used by the hash algorithms.
     */
    constexpr auto ROUND_COUNT = 32;

    class ChebyHash32
    {
    private:
        /**
        * @brief Performs one mixing round on two 32-bit values.
        *
        * Modifies both input values in place using arithmetic, bitwise XOR,
        * and bit rotation operations.
        *
        * @param x First 32-bit value, modified during the round.
        * @param y Second 32-bit value, modified during the round.
        */
        static void round(std::uint32_t& x, std::uint32_t& y);
        /**
        * @brief Mixes two 32-bit values through multiple rounds.
        *
        * Performs multiple mixing rounds on local copies of the input values.
        * The original arguments remain unchanged.
        *
        * @param x First input value.
        * @param y Second input value.
        * @return The resulting 32-bit value after mixing.
         */
        static std::uint32_t mix(std::uint32_t x, std::uint32_t y);
    public:
        /**
        * @brief Calculates a 32-bit hash of the input string.
        * 
        * @param input String to be hashed.
        * @return 32-bit hash value.
        */
        static std::uint32_t hash(std::string_view input);
    };

    class ChebyHash64
    {
    private:
        /**
        * @brief Performs one mixing round on two 64-bit values.
        *
        * Modifies both input values in place using arithmetic, bitwise XOR,
        * and bit rotation operations.
        *
        * @param x First 64-bit value, modified during the round.
        * @param y Second 64-bit value, modified during the round.
         */
        static void round(std::uint64_t& x, std::uint64_t& y);
        /**
        * @brief Mixes two 64-bit values through multiple rounds.
        *
        * Performs multiple mixing rounds on local copies of the input values.
        * The original arguments remain unchanged.
        *
        * @param x First input value.
        * @param y Second input value.
        * @return The resulting 64-bit value after mixing.
         */
        static std::uint64_t mix(std::uint64_t x, std::uint64_t y);
    public:
        /**
        * @brief Calculates a 64-bit hash of the input string.
        * 
        * @param input String to be hashed.
        * @return 64-bit hash value.
         */
        static std::uint64_t hash(std::string_view input);
    };

    class ChebyHash128
    {
    public:
        /**
        * @brief Represents an unsigned 128-bit integer.
        *
        * @param high Upper 64 bits.
        * @param low  Lower 64 bits.
         */
        struct Hash128
        {
            std::uint64_t high;
            std::uint64_t low;

            /**
            * @brief Adds two unsigned 128-bit integers.
            *
            * Performs addition with carry propagation from the lower
            * 64 bits to the upper 64 bits.
            *
            * @param valueTwo The second operand.
            * @return The sum modulo 2^128.
             */
            Hash128 operator+(const Hash128& valueTwo) const;
            /**
            * @brief Subtracts one unsigned 128-bit integer from another.
            *
            * Performs subtraction with borrow propagation from the lower
            * 64 bits to the upper 64 bits.
            *
            * @param valueTwo The value to subtract.
            * @return The difference modulo 2^128.
             */
            Hash128 operator-(const Hash128& valueTwo) const;
            /**
            * @brief Multiplies two unsigned 128-bit integers.
            *
            * Uses an intermediate 128-bit product to calculate the lower
            * 128 bits of the multiplication result.
            *
            * @param valueTwo The second operand.
            * @return The product modulo 2^128.
             */
            Hash128 operator*(const Hash128& valueTwo) const;
            /**
            * @brief Divides one unsigned 128-bit integer by another.
            *
            * @param divisor The divisor.
            * @return The quotient of the division.
            *
            * @note Division by zero behavior depends on the implementation
            * of the internal divide() function.
             */
            Hash128 operator/(const Hash128& divisor) const;
            /**
            * @brief Calculates the remainder of unsigned 128-bit division.
            *
            * @param divisor The divisor.
            * @return The remainder of the division.
            *
            * @note Division by zero behavior depends on the implementation
            * of the internal divide() function.
             */
            Hash128 operator%(const Hash128& divisor) const;
            /**
            * @brief Performs a bitwise XOR operation on two unsigned 128-bit integers.
            *
            * Applies XOR independently to the upper and lower 64-bit parts.
            *
            * @param valueTwo The second operand.
            * @return The bitwise XOR result.
             */
            Hash128 operator^(const Hash128& valueTwo) const;
        };

        /**
        * @brief Represents a signed 128-bit value.
        *
        * @param value    Absolute magnitude of the value.
        * @param negative Indicates whether the value is negative.
         */
        struct SignedHash128
        {
            Hash128 value;
            bool negative;
        };

        /**
        * @brief Stores the result of a 128-bit division.
        *
        * @param quotient  Division result.
        * @param remainder Remainder of the division.
         */
        struct DivisionResult
        {
            Hash128 quotient;
            Hash128 remainder;
        };

        static bool lessThan(const Hash128& valueOne, const Hash128& valueTwo);
        static bool isZero(const Hash128& value);
        static SignedHash128 subtractSigned(
            const Hash128& valueOne, bool valueOneNegative, const Hash128& valueTwo, bool valueTwoNegative
        );
        
        static Hash128 shiftLeft(const Hash128& value, unsigned int shift);
        static Hash128 shiftRight(const Hash128& value, unsigned int shift);
        static DivisionResult divide(const Hash128& value, const Hash128& divisor);
        static Hash128 rotl(const Hash128& value, unsigned int shift);
        static Hash128 rotr(const Hash128& value, unsigned int shift);
        static Hash128 multiplyMod(const Hash128& valueOne, const Hash128& valueTwo, const Hash128& modulus);
        static Hash128 addMod(const Hash128& valueOne, const Hash128& valueTwo, const Hash128& modulus);
        
    private:
        /**
        * @brief Performs one mixing round on two 128-bit values.
        *
        * Modifies both input values in place using arithmetic, bitwise XOR,
        * and bit rotation operations.
        *
        * @param x First 128-bit value, modified during the round.
        * @param y Second 128-bit value, modified during the round.
         */
        static void round(Hash128& x, Hash128& y);
        /**
        * @brief Mixes two 128-bit values through multiple rounds.
        *
        * Performs multiple mixing rounds on local copies of the input values.
        * The original arguments remain unchanged.
        *
        * @param x First input value.
        * @param y Second input value.
        * @return The resulting 128-bit value after mixing.
         */
        static Hash128 mix(Hash128 x, Hash128 y);
    public:
        /**
        * @brief Calculates a 128-bit hash of the input string.
        * 
        * @param input String to be hashed.
        * @return 128-bit hash value.
         */
        static Hash128 hash(std::string_view input);
    };
};