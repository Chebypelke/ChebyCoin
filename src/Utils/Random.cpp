#include <Utils/Random.hpp>
#include <string>
#include <random>

std::string Random::RandomStringGenerator(size_t length) 
{
    const std::string characters = 
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";
        
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string result;
    result.reserve(length);
    
    for (size_t i = 0; i < length; ++i) {
        result.push_back(characters[distribution(generator)]);
    }
    
    return result;
}

std::string Random::RandomNumberGenerator(size_t length) 
{
    const std::string characters = "0123456789";
        
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, characters.size() - 1);

    std::string result;
    result.reserve(length);
    
    for (size_t i = 0; i < length; ++i) {
        result.push_back(characters[distribution(generator)]);
    }
    
    return result;
}