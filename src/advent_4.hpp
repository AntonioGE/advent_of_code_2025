#pragma once

#include <string>
#include <vector>
#include <optional>
#include <cstdint>

class Advent4
{
public:
    static int64_t solvePartOne(const std::string &f_filePath);
    static int64_t solvePartTwo(const std::string &f_filePath);

private:
    template <typename T>
    class Grid
    {
    public:
        Grid()
            : m_rows(0), m_cols(0)
        {
        }

        Grid(const int f_rows, const int f_cols)
            : m_rows(f_rows), m_cols(f_cols), m_data(f_rows * f_cols)
        {
        }

        Grid(const int f_rows, const int f_cols, const std::vector<T> &f_data)
            : m_rows(f_rows), m_cols(f_cols), m_data(f_data)
        {
        }

        bool isInside(const int f_row, const int f_col) const
        {
            return (f_row >= 0) && (f_row < m_rows) && (f_col >= 0) && (f_col < m_cols);
        }

        T &at(const int f_row, const int f_col)
        {
            return m_data[f_row * m_cols + f_col];
        }

        const T &at(const int f_row, const int f_col) const
        {
            return m_data[f_row * m_cols + f_col];
        }

        int rows() const
        {
            return m_rows;
        }

        int cols() const
        {
            return m_cols;
        }

    private:
        std::vector<T> m_data;
        int m_rows;
        int m_cols;
    };

    using CharGrid = Grid<char>;

    static constexpr char s_roll = '@';
    static constexpr char s_empty = '.';
    static constexpr char s_used = '#';

private:
    static std::optional<CharGrid> readGrid(const std::string &f_filePath);
    static int64_t countAccesibleRolls(const CharGrid &f_grid);
    static bool isRollAccesible(const CharGrid &f_grid, const int f_row, const int f_col);
    static int64_t countAccesibleRollsRecursive(const CharGrid &f_grid);
    static int64_t countAndClearAccesibleRolls(CharGrid &f_grid);
};