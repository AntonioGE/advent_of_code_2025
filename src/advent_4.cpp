#include "advent_4.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <numeric>
#include <algorithm>
#include <array>

int main()
{
    const std::string l_l_filePath = "res/input_4.txt";
    std::cout << "Part one: " << Advent4::solvePartOne(l_l_filePath) << std::endl;
    std::cout << "Part two: " << Advent4::solvePartTwo(l_l_filePath) << std::endl;

    return 0;
}

int64_t Advent4::solvePartOne(const std::string &f_filePath)
{
    auto l_grid = readGrid(f_filePath);
    if (!l_grid)
    {
        std::cerr << "Error reading input at '" << f_filePath << "'" << std::endl;
        return -1;
    }

    return countAccesibleRolls(l_grid.value());
}

int64_t Advent4::solvePartTwo(const std::string &f_filePath)
{
    auto l_grid = readGrid(f_filePath);
    if (!l_grid)
    {
        std::cerr << "Error reading input at '" << f_filePath << "'" << std::endl;
        return -1;
    }

    return countAccesibleRollsRecursive(l_grid.value());
}

std::optional<Advent4::CharGrid> Advent4::readGrid(const std::string &f_filePath)
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        return std::nullopt;
    }

    int l_rows = 0;
    int l_cols = 0;
    std::vector<char> l_data;
    std::string l_line;
    while (std::getline(l_file, l_line))
    {
        if (l_rows == 0)
        {
            l_cols = l_line.size();
        }

        l_data.insert(l_data.begin(), l_line.begin(), l_line.end());
        l_rows++;
    }
    return CharGrid(l_rows, l_cols, l_data);
}

int64_t Advent4::countAccesibleRolls(const CharGrid &f_grid)
{
    int64_t l_sum = 0;
    for (int i = 0; i < f_grid.rows(); i++)
    {
        for (int j = 0; j < f_grid.cols(); j++)
        {
            if ((f_grid.at(i, j) == s_roll) && isRollAccesible(f_grid, i, j))
            {
                l_sum++;
            }
        }
    }
    return l_sum;
}

bool Advent4::isRollAccesible(const CharGrid &f_grid, const int f_row, const int f_col)
{
    int l_count = -1;

    constexpr int l_radius = 1;
    for (int i = -l_radius; i <= l_radius; i++)
    {
        for (int j = -l_radius; j <= l_radius; j++)
        {
            int l_row = f_row + i;
            int l_col = f_col + j;
            if (f_grid.isInside(l_row, l_col) && (f_grid.at(l_row, l_col) != s_empty))
            {
                l_count++;
            }
        }
    }

    return l_count < 4;
}

int64_t Advent4::countAccesibleRollsRecursive(const CharGrid &f_grid)
{
    CharGrid l_grid = f_grid;

    int l_totalCount = 0;
    int l_count;
    while ((l_count = countAndClearAccesibleRolls(l_grid)) != 0)
    {
        l_totalCount += l_count;
    }

    return l_totalCount;
}

int64_t Advent4::countAndClearAccesibleRolls(CharGrid &f_grid)
{
    int64_t l_sum = 0;
    for (int i = 0; i < f_grid.rows(); i++)
    {
        for (int j = 0; j < f_grid.cols(); j++)
        {
            if ((f_grid.at(i, j) == s_roll) && isRollAccesible(f_grid, i, j))
            {
                l_sum++;
                f_grid.at(i, j) = s_used;
            }
        }
    }

    for (int i = 0; i < f_grid.rows(); i++)
    {
        for (int j = 0; j < f_grid.cols(); j++)
        {
            if (f_grid.at(i, j) == s_used)
            {
                f_grid.at(i, j) = s_empty;
            }
        }
    }

    return l_sum;
}
