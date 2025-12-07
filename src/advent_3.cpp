#include "advent_3.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <array>

int main()
{
    const std::string l_l_filePath = "res/input_3.txt";
    std::cout << "Part one: " << Advent3::solvePartOne(l_l_filePath) << std::endl;
    std::cout << "Part two: " << Advent3::solvePartTwo(l_l_filePath) << std::endl;

    return 0;
}

int64_t Advent3::solvePartOne(const std::string &f_filePath)
{
    auto l_banks = readBanks(f_filePath);
    if (!l_banks)
    {
        std::cerr << "Error reading input at '" << f_filePath << "'" << std::endl;
        return -1;
    }

    return sumJoltages(l_banks.value(), 2);
}

int64_t Advent3::solvePartTwo(const std::string &f_filePath)
{
    auto l_banks = readBanks(f_filePath);
    if (!l_banks)
    {
        std::cerr << "Error reading input at '" << f_filePath << "'" << std::endl;
        return -1;
    }

    return sumJoltages(l_banks.value(), 12);
}

std::optional<std::vector<std::string>> Advent3::readBanks(const std::string &f_filePath)
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        return std::nullopt;
    }

    std::vector<std::string> l_banks;
    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        l_banks.push_back(l_line);
    }

    return l_banks;
}

int64_t Advent3::sumJoltages(const std::vector<std::string> &f_banks, const int f_digits)
{
    int64_t l_sum = 0;
    for (const std::string &l_bank : f_banks)
    {
        l_sum += findLargestJoltage(l_bank, f_digits);
    }
    return l_sum;
}

int64_t Advent3::findLargestJoltage(const std::string &f_bank, const int f_digits)
{
    // Monotonic stack
    std::string l_stack;
    l_stack.reserve(f_digits);
    int l_remove = f_bank.size() - f_digits;

    for (char l_char : f_bank)
    {
        while (!l_stack.empty() && (l_remove > 0) && (l_stack.back() < l_char))
        {
            l_stack.pop_back();
            l_remove--;
        }
        l_stack.push_back(l_char);
    }

    if (l_stack.size() > f_digits)
    {
        l_stack.resize(f_digits);
    }

    return std::stoll(l_stack);
}