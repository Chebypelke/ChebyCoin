### EN, [RU](README_ru.md)

# ChebyCoin

An experimental cryptocurrency and blockchain project written in C++.

The project was created for educational purposes to study C++, hashing algorithms, 128-bit arithmetic, digital signatures, blockchain architecture, and safe programming principles.

It utilizes custom components built during development (ChebyHash, ChebySignature, etc.).

## [ChebyHash](docs/EN/ChebyHash_en.md)

## ChebyChain

ChebyChain is an experimental blockchain implementation for ChebyCoin.

Each block contains information about the previous block and its own hash.

## ChebySignature

ChebySignature is an experimental digital signature component built on top of the custom 128-bit `Hash128` arithmetic.

The current version implements an educational RSA-like digital signature scheme.

### Implemented

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

- [x] ChebyHash
- [x] ChebyChain
- [x] ChebySignature
- [x] Wallets
- [x] Transactions

### Planned

- [ ] Mining
- [ ] Proof-of-Work
- [ ] Networking layer
- [ ] Secure key storage
- [ ] Persistent blockchain storage

## License

Distributed under the MIT License.

See `LICENSE` for more information.

## Disclaimer

ChebyCoin is an experimental educational project.

ChebyHash, ChebyChain, and ChebySignature are **not** intended for use in real financial, cryptographic, authentication, or security systems.
