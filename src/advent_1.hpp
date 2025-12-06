#pragma once

#include <string>
#include <vector>
#include <optional>

class Advent1
{
public:
    static int solvePartOne(const std::string &f_filePath);
    static int solvePartTwo(const std::string &f_filePath);

private:
    static std::optional<std::vector<int>> readRotations(const std::string &f_filePath);
    static int countZeroDials(const std::vector<int> &f_rotations);
    static int countZeroTicks(const std::vector<int> &f_rotations);

private:
    static constexpr int s_numTicks = 100;
    static constexpr int s_dialStart = 50;
};