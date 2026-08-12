### [EN](README.md), [RU](README_RU.md)

# ChebyCoin

An experimental cryptocurrency and blockchain project written in C++.

The project is developed for educational purposes and focuses on learning C++, hashing algorithms, 128-bit arithmetic, digital signatures, blockchain architecture, and secure programming concepts.

## Features

- ChebyHash32|64|128
- String hashing API
- Custom 128-bit Hash128 type
- 128-bit arithmetic
- Avalanche effect testing
- ChebyChain
- Block structure
- Genesis Block
- Block linking through previous hashes
- Blockchain integrity verification
- ChebySignature
- RSA-style key generation
- Digital signature generation
- Digital signature verification

## ChebyHash

ChebyHash is an experimental hashing algorithm developed for ChebyCoin.

The project currently supports 32-, 64-, and 128-bit hash versions.

ChebyHash128 uses a custom Hash128 structure consisting of two 64-bit values:

- high
- low

128-bit arithmetic is implemented using these two 64-bit values.

### Hash128 Operations

ChebyHash128 provides operations including:

- Addition
- Subtraction
- XOR
- Comparison
- Multiplication
- Division
- Modulo
- Bit shifting
- Bit rotation
- Modular addition
- Modular multiplication

These operations are used by higher-level ChebyCoin components.

### Avalanche Effect

ChebyHash implementations are tested using avalanche testing.

The test changes a single input bit and measures how many output bits change.

| Algorithm    | Hash size | Average changed bits |
| ------------ | --------- | -------------------- |
| ChebyHash32  | 32 bits   | ~16                  |
| ChebyHash64  | 64 bits   | ~32                  |
| ChebyHash128 | 128 bits  | ~63.9                |

With an ideal avalanche effect, changing one input bit should change approximately half of the output bits.

ChebyHash128 was tested using 500,000 random inputs.

## ChebyChain

ChebyChain is an experimental blockchain implementation for ChebyCoin.

Each block contains information about the previous block and its own hash.

### Implemented

- Block structure
- Genesis Block
- Blockchain container
- Block linking through previous hashes
- Automatic block hash calculation
- Blockchain integrity verification
- Block access API
- Block count API

## ChebySignature

ChebySignature is an experimental digital signature component built on top of the custom Hash128 arithmetic.

It currently implements an educational RSA-style signing scheme.

### Implemented

- RSA-style key pair generation
- Public and private keys
- Modular inverse calculation
- Modular exponentiation
- Digital signature generation
- Digital signature verification
- Signature verification tests

The current implementation uses the public exponent e = 65537.

The private exponent is calculated as the modular inverse of e modulo Euler's totient:

d = e⁻¹ mod φ

The signing process calculates:

signature = hash^d mod n

Verification calculates:

verified = signature^e mod n

The implementation successfully verifies that the recovered hash matches the original hash.

### Important

ChebySignature is an educational implementation.

It is not cryptographically secure and must not be used for real authentication, digital signatures, cryptocurrencies, financial systems, or secure communications.

It currently does not implement production cryptographic standards such as RSA-PSS, PKCS#1 v1.5, secure padding, or cryptographically secure key generation.

## Testers

Testers provide a way to experiment with implemented ChebyCoin components.

### ChebyHash32|64|128 Tester

- Random string generation
- Hashing tests
- Avalanche testing
- Average changed bit measurement
- Execution time measurement

### ChebyChain Tester

- Creating new blocks
- Viewing blockchain size
- Viewing blocks by index
- Displaying hashes in decimal and hexadecimal format
- Blockchain integrity verification
- Console interface

### ChebySignature Tester

- RSA-style key generation
- Message hash signing
- Signature verification
- Original hash comparison
- PASS/FAIL verification output

## Build

1. Clone the repository:

git clone git@github.com:Chebypelke/ChebyCoin.git
cd ChebyCoin

2. Build the project using CMake:

cmake -S . -B build
cmake --build build

## Project Status

Current version: v0.0.4

### Implemented

- [x] ChebyHash32
- [x] ChebyHash64
- [x] ChebyHash128
- [x] String hashing
- [x] Avalanche testing
- [x] Hash testers
- [x] Hash128 arithmetic
- [x] Block structure
- [x] Genesis Block
- [x] Blockchain
- [x] Block linking
- [x] Blockchain integrity verification
- [x] Blockchain testers
- [x] First ChebyHash release
- [x] First ChebyChain release
- [x] First ChebyHash128 release
- [x] ChebySignature
- [x] RSA-style key generation
- [x] Digital signature generation
- [x] Digital signature verification
- [x] First ChebySignature release

### Planned

- [ ] Transactions
- [ ] Mining
- [ ] Proof-of-Work
- [ ] Wallets
- [ ] Network layer
- [ ] Transaction signing
- [ ] Secure key storage
- [ ] Persistent blockchain storage

## License

This project is distributed under the MIT License.

See the LICENSE file for details.

## Disclaimer

ChebyCoin is an experimental educational project.

ChebyHash, ChebyChain, and ChebySignature are not intended for use in real financial, cryptographic, authentication, or security systems.

The project is developed for educational purposes and is intended to explore:

- C++
- Algorithms
- Data structures
- Hash functions
- 128-bit arithmetic
- Digital signatures
- Blockchain architecture
- Cryptographic concepts
- Secure programming