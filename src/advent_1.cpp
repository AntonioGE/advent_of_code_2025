#include <iostream>
#include <fstream>

#include "advent_1.hpp"

int main()
{
    const std::string l_filePath = "res/input_1.txt";
    std::cout << "Part one: " << Advent1::solvePartOne(l_filePath) << std::endl;
    std::cout << "Part two: " << Advent1::solvePartTwo(l_filePath) << std::endl;

    return 0;
}

int Advent1::solvePartOne(const std::string &f_filePath)
{
    auto l_rotations = readRotations(f_filePath);
    if (!l_rotations)
    {
        return -1;
    }

    return countZeroDials(*l_rotations);
}

int Advent1::solvePartTwo(const std::string &f_filePath)
{
    auto l_rotations = readRotations(f_filePath);
    if (!l_rotations)
    {
        return -1;
    }

    return countZeroTicks(*l_rotations);
}

std::optional<std::vector<int>> Advent1::readRotations(const std::string &f_filePath)
{
    std::ifstream l_file(f_filePath);
    if (!l_file)
    {
        return std::nullopt;
    }

    std::vector<int> l_rotations;
    std::string l_line;
    while (std::getline(l_file, l_line) && !l_line.empty())
    {
        char l_dir = l_line[0];
        int l_value = std::stoi(l_line.substr(1));

        if (l_dir == 'L')
        {
            l_value = -l_value;
        }

        l_rotations.push_back(l_value);
    }

    return l_rotations;
}

int Advent1::countZeroDials(const std::vector<int> &f_rotations)
{
    int l_count = 0;
    int l_dial = s_dialStart;
    for (int l_rotation : f_rotations)
    {
        l_dial = (l_dial + l_rotation + s_numTicks) % s_numTicks;
        if (l_dial == 0)
        {
            l_count++;
        }
    }

    return l_count;
}

int Advent1::countZeroTicks(const std::vector<int> &f_rotations)
{
    int l_count = 0;
    int l_dial = s_dialStart;
    for (int l_rotation : f_rotations)
    {
        int l_delta = l_rotation < 0 ? -1 : 1;
        while (l_rotation != 0)
        {
            l_dial += l_delta;
            l_dial = (l_dial + s_numTicks) % s_numTicks;

            if (l_dial == 0)
            {
                l_count++;
            }

            l_rotation -= l_delta;
        }
    }

    return l_count;
}
