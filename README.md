### EN, [RU](README_ru.md)

# ChebyCoin

An experimental cryptocurrency and blockchain project written in C++.

The project was created for educational purposes to study C++, hashing algorithms, 128-bit arithmetic, digital signatures, blockchain architecture, and safe programming principles.

It utilizes custom components built during development (ChebyHash, ChebySignature, etc.).

## Features

- ChebyHash32|64|128
- String hashing API
- Custom 128-bit `Hash128` type
- 128-bit arithmetic
- Avalanche effect testing
- ChebyChain
- Block structure
- Genesis Block
- Block linking via previous hashes
- Blockchain integrity verification
- ChebySignature
- RSA-like key generation
- Digital signature creation
- Digital signature verification

## [ChebyHash](docs/EN/ChebyHash_en.md)

## ChebyChain

ChebyChain is an experimental blockchain implementation for ChebyCoin.

Each block contains information about the previous block and its own hash.

### Implemented

- Block structure
- Genesis Block
- Blockchain container
- Block linking via previous hashes
- Automatic block hash calculation
- Blockchain integrity verification
- Block access API
- Retrieving block count

## ChebySignature

ChebySignature is an experimental digital signature component built on top of the custom 128-bit `Hash128` arithmetic.

The current version implements an educational RSA-like digital signature scheme.

### Implemented

- RSA-like key pair generation
- Public key
- Private key
- Modular inverse calculation
- Modular exponentiation
- Digital signature creation
- Digital signature verification
- Signature verification testing

The current implementation uses the public exponent e = 65537.

The private exponent is calculated as the modular inverse of e modulo Euler's totient function:

d = e⁻¹ mod φ

Signature creation is performed using the formula:

signature = hash^d mod n

Signature verification is performed using the formula:

verified = signature^e mod n

The implementation successfully verifies that the recovered hash matches the original one.

### Important Notice

ChebySignature is an educational implementation.

It is **not** cryptographically secure and is not intended for use in production authentication systems, digital signatures, cryptocurrencies, financial systems, or secure communications.

The current implementation does not use industry cryptographic standards such as RSA-PSS, PKCS#1 v1.5, secure padding schemes, or cryptographically secure key generation.

## Testers

The interactive testers allow you to experiment with the implemented ChebyCoin components.

### ChebyHash32|64|128 Tester

- Random string generation
- Hashing tests
- Avalanche effect testing
- Measurement of the average number of flipped bits
- Execution time measurement

### ChebyChain Tester

- Creation of new blocks
- Viewing the block count
- Inspecting blocks by index
- Displaying hashes in decimal and HEX formats
- Blockchain integrity verification
- Console UI

### ChebySignature Tester

- RSA-like key pair generation
- Message hash signing
- Digital signature verification
- Comparison of original and recovered hash
- PASS/FAIL result output

## Building

1. Clone the repository:

```bash
git clone git@github.com:Chebypelke/ChebyCoin.git
cd ChebyCoin
```

2. Build the project using CMake:

```bash
cmake -S . -B build
cmake --build build
```

## Project Status

Current version: v0.0.6

### Implemented

- [x] ChebyHash32
- [x] ChebyHash64
- [x] Hash128 arithmetic
- [x] ChebyHash128
- [x] Block structure
- [x] Blockchain
- [x] Blockchain integrity verification
- [x] ChebyChain
- [x] RSA-like key generation
- [x] Digital signature creation
- [x] Digital signature verification
- [x] ChebySignature
- [x] Wallets
- [x] Transactions

### Planned

- [ ] Mining
- [ ] Proof-of-Work
- [ ] Networking layer
- [ ] Transaction signing
- [ ] Secure key storage
- [ ] Persistent blockchain storage

## License

Distributed under the MIT License.

See `LICENSE` for more information.

## Disclaimer

ChebyCoin is an experimental educational project.

ChebyHash, ChebyChain, and ChebySignature are **not** intended for use in real financial, cryptographic, authentication, or security systems.

This project was created purely for educational purposes to study:

- C++
- Algorithms
- Data structures
- Hash functions
- 128-bit arithmetic
- Digital signatures
- Blockchain architecture
- Cryptographic concepts
- Safe programming