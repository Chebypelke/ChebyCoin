# ChebyHash

ChebyHash is an experimental hashing algorithm developed for ChebyCoin.

32-, 64-, and 128-bit versions are supported.

ChebyHash128 uses a custom `Hash128` structure consisting of two 64-bit values:

- `high`
- `low`

128-bit arithmetic is implemented on top of these two 64-bit values.

## Hash128 Operations

ChebyHash128 supports the following operations:

- Addition
- Subtraction
- XOR
- Comparison
- Multiplication
- Division
- Modulo
- Bit shifts
- Bit rotations
- Modular addition
- Modular multiplication

These operations are used by higher-level ChebyCoin components.

## Avalanche Effect

The hashes are tested using an avalanche test.

The test flips a single bit in the input data and measures how many bits in the output hash changed.

| Algorithm    | Hash Size | Average Number of Changed Bits |
| ------------ | --------- | ------------------------------ |
| ChebyHash32  | 32 bits   | 16.0025                        |
| ChebyHash64  | 64 bits   | 32.0085                        |
| ChebyHash128 | 128 bits  | 63.9775                        |

With an ideal avalanche effect, changing a single input bit should cause approximately half of the output bits to change.

ChebyHash128 was tested on 500,000 random inputs.

## API

The main header file for ChebyHash is `src/ChebyHash/ChebyHash.hpp`.

The tester header is located at `src/ChebyHash/Testers/ChebyHashTesters.hpp`.

## Disclaimer

ChebyHash is an experimental hashing algorithm.

It is **not recommended for use in real-world cryptographic systems, protecting sensitive data, or any other applications that require a cryptographically secure hash function**.