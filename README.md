### [RU](README_ru.md), EN


# ChebyCoin

Experimental cryptocurrency project written in C++.

## Features

- ChebyHash32
- ChebyHash64
- String hashing API
- Avalanche testing for both variants
- Random string test utilities

## ChebyHash

ChebyHash is a custom experimental hashing algorithm developed for ChebyCoin.

Both 32-bit and 64-bit variants have been tested using an avalanche test. The test changes one bit of the input and measures how many output bits change.

### Test Results

| Algorithm | Hash Size | Average Changed Bits |
|-----------|-----------|----------------------|
| ChebyHash32 | 32-bit | ~16 |
| ChebyHash64 | 64-bit | ~32 |

An ideal avalanche effect changes approximately half of the output bits when a single input bit is changed.

## Building

Clone the repository:
```bash
    git clone git@github.com:Chebypelke/ChebyCoin.git
    cd ChebyCoin
```

Build with CMake:
```bash
    cmake -S . -B build
    cmake --build build
```

## Testers

Linux binaries for testers are available in the releases.

## Project Status

Current version: v0.0.1

### Implemented

- [x] ChebyHash32
- [x] ChebyHash64
- [x] String hashing
- [x] Avalanche testing
- [x] Hash testers
- [x] Initial release

### Planned

- [ ] Block structure
- [ ] Blockchain
- [ ] Transactions
- [ ] Mining
- [ ] Proof-of-Work
- [ ] Wallets
- [ ] Network layer

## License

This project is licensed under the MIT License.

See [LICENSE](LICENSE) for details.

## Disclaimer

ChebyCoin is an experimental educational project.

It is not intended for real-world financial use.