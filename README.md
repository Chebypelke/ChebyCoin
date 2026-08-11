### EN, [RU](README_ru.md)

# ChebyCoin

An experimental cryptocurrency project written in C++.

## Features

- ChebyHash32|64|128
- String hashing API
- 128-bit Hash128 type
- Avalanche effect testing
- ChebyChain
- Block structure
- Genesis Block
- Block linking through previous hashes
- Blockchain integrity validation

## ChebyHash

ChebyHash is an experimental hashing algorithm developed for ChebyCoin.

The project supports 32-bit, 64-bit and 128-bit versions.

ChebyHash128 uses a custom Hash128 structure consisting of two 64-bit values: high and low.

128-bit operations are implemented using two 64-bit values.

### Avalanche Effect

The hashes are tested using an avalanche effect test.

The test changes a single bit of the input data and measures how many bits of the output hash have changed.

| Algorithm    | Hash size | Average number of changed bits |
| ------------ | --------- | ------------------------------ |
| ChebyHash32  | 32 bits   | ~16                            |
| ChebyHash64  | 64 bits   | ~32                            |
| ChebyHash128 | 128 bits  | 63.979                         |

With an ideal avalanche effect, changing a single input bit results in approximately half of the output hash bits changing.

ChebyHash128 was tested with 500,000 random inputs.

## ChebyChain

ChebyChain is an experimental blockchain implementation for ChebyCoin.

Each block contains information about the previous block and its own hash.

### Implemented

- Block structure
- Genesis Block
- Blockchain container
- Block linking through previous hashes
- Automatic block hash calculation
- Blockchain integrity validation
- Block access API
- Block count API

## Testers

The testers provide tools for experimenting with the implemented ChebyCoin components.

### ChebyHash Tester

- Random string generation
- Hashing tests
- Avalanche effect testing
- Average changed-bit calculation
- Execution time measurement

### ChebyChain Tester

- Create new blocks
- Display block count
- Inspect blocks by index
- Display hashes in decimal and hexadecimal format
- Validate blockchain integrity
- Console interface

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

Current version: v0.0.3

### Implemented

- [x] ChebyHash32
- [x] ChebyHash64
- [x] ChebyHash128
- [x] String hashing
- [x] Avalanche effect testing
- [x] Hash testers
- [x] Block structure
- [x] Genesis Block
- [x] Blockchain
- [x] Block linking
- [x] Blockchain integrity validation
- [x] Blockchain testers
- [x] ChebyHash initial release
- [x] ChebyChain initial release
- [x] ChebyHash128 initial release

### Planned

- [ ] Transactions
- [ ] Mining
- [ ] Proof-of-Work
- [ ] Wallets
- [ ] Networking layer

## License

The project is distributed under the MIT License.

See the LICENSE file for details.

## Disclaimer

ChebyCoin is an experimental educational project.

ChebyHash and ChebyChain are not intended for use in real financial or cryptographic systems.

The project is developed for educational purposes to study C++, hashing algorithms, data structures and blockchain principles.