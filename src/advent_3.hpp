#pragma once

#include <string>
#include <vector>
#include <optional>
#include <cstdint>

class Advent3
{
public:
    static int64_t solvePartOne(const std::string &f_filePath);
    static int64_t solvePartTwo(const std::string &f_filePath);

private:
    static std::optional<std::vector<std::string>> readBanks(const std::string &f_filePath);
    static int64_t sumJoltages(const std::vector<std::string> &f_banks, const int f_digits);
    static int64_t findLargestJoltage(const std::string &f_bank, const int f_digits);
};