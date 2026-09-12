#include "Utils.hpp"
#include <iostream>
#include <limits>

void CLIUtils::clearScreen() 
{
    std::cout << "\033[2J\033[H" << std::flush;
}

bool CLIUtils::readInt(int& int_data)
{
    if (!(std::cin >> int_data)) 
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}

bool CLIUtils::readSizeT(std::size_t& size_t_data)
{
    if (!(std::cin >> size_t_data))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}

bool CLIUtils::readString(std::string& string_data)
{
    if (!(std::getline(std::cin, string_data)))
    {
        std::cin.clear();
	    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }
    return true;
}

bool CLIUtils::readUInt32(std::uint32_t& uint32_t_data)
{
    if (!(std::cin >> uint32_t_data))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}

bool CLIUtils::readHash128(ChebyHash::ChebyHash128::Hash128& hash)
{
    std::string input;

    if (!(std::cin >> input))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    if (input.length() != 32)
    {
        return false;
    }

    for (char c : input)
    {
        if (!std::isxdigit(static_cast<unsigned char>(c)))
        {
            return false;
        }
    }

    try
    {
        hash.high = std::stoull(input.substr(0, 16), nullptr, 16);
        hash.low = std::stoull(input.substr(16, 16), nullptr, 16);
    }
    catch (...)
    {
        return false;
    }

    return true;
}

bool CLIUtils::readDouble(double &double_data)
{
    if (!(std::cin >> double_data))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return false;
    }

    return true;
}