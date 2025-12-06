#include "advent_2.hpp"

#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    const std::string l_l_filePath = "res/input_2.txt";
    std::cout << "Part one: " << Advent2::solvePartOne(l_l_filePath) << std::endl;
    std::cout << "Part two: " << Advent2::solvePartTwo(l_l_filePath) << std::endl;

    return 0;
}

int64_t Advent2::solvePartOne(const std::string &f_filePath)
{
    auto l_ranges = readRanges(f_filePath);
    if (!l_ranges)
    {
        std::cerr << "Error reading input at '" << f_filePath << "'" << std::endl;
        return -1;
    }

    return sumAllInvalidIDs(l_ranges.value());
}

int64_t Advent2::solvePartTwo(const std::string &f_filePath)
{
    auto l_ranges = readRanges(f_filePath);
    if (!l_ranges)
    {
        std::cerr << "Error reading input at '" << f_filePath << "'" << std::endl;
        return -1;
    }

    return sumAllNewInvalidIDs(l_ranges.value());
}

std::optional<std::vector<Advent2::Range>> Advent2::readRanges(const std::string &f_filePath)
{
    std::ifstream l_file(f_filePath);
    if (!l_file.is_open())
    {
        return std::nullopt;
    }

    std::string l_line;
    if (!std::getline(l_file, l_line))
    {
        return std::nullopt;
    }

    std::vector<Range> l_ranges;
    std::stringstream l_ss(l_line);
    std::string l_token;
    while (std::getline(l_ss, l_token, ','))
    {
        std::size_t l_dashPos = l_token.find('-');
        if (l_dashPos == std::string::npos)
        {
            break;
        }

        std::string l_strStart = l_token.substr(0, l_dashPos);
        std::string l_strEnd = l_token.substr(l_dashPos + 1);

        Range l_range;
        l_range.start = std::stoll(l_strStart);
        l_range.end = std::stoll(l_strEnd);
        l_ranges.push_back(l_range);
    }

    return l_ranges;
}

int64_t Advent2::sumAllInvalidIDs(const std::vector<Range> &f_ranges)
{
    int64_t l_sum = 0;
    for (const Range &l_range : f_ranges)
    {
        l_sum += sumRangeInvalidIDs(l_range);
    }

    return l_sum;
}

int64_t Advent2::sumRangeInvalidIDs(const Range &f_range)
{
    int64_t l_sum = 0;
    for (int64_t l_id = f_range.start; l_id <= f_range.end; l_id++)
    {
        if (isInvalidID(l_id))
        {
            l_sum += l_id;
        }
    }

    return l_sum;
}

bool Advent2::isInvalidID(const int64_t f_id)
{
    const int l_digits = numDigitsBase10(f_id);
    if (!l_digits || !isEven(l_digits))
    {
        return false;
    }

    const int64_t l_factor = pow10(l_digits / 2);
    const int64_t l_top = f_id / l_factor;
    const int64_t l_bot = f_id - l_top * l_factor;

    return l_bot == l_top;
}

int Advent2::numDigitsBase10(const int64_t f_value)
{
    int l_count = 0;
    int64_t l_value = f_value;
    while (l_value > 0)
    {
        l_value /= 10;
        l_count++;
    }

    return l_count;
}

bool Advent2::isEven(const int64_t f_value)
{
    return (f_value % 2) == 0;
}

int64_t Advent2::pow10(const unsigned int f_numZeros)
{
    unsigned int l_zeros = f_numZeros;
    int64_t l_value = 1;
    while (l_zeros--)
    {
        l_value *= 10;
    }
    return l_value;
}

int64_t Advent2::sumAllNewInvalidIDs(const std::vector<Range> &f_ranges)
{
    int64_t l_sum = 0;
    for (const Range &l_range : f_ranges)
    {
        l_sum += sumRangeNewInvalidIDs(l_range);
    }

    return l_sum;
}

int64_t Advent2::sumRangeNewInvalidIDs(const Range &f_range)
{
    int64_t l_sum = 0;
    for (int64_t l_id = f_range.start; l_id <= f_range.end; l_id++)
    {
        if (isNewInvalidID(l_id))
        {
            l_sum += l_id;
        }
    }

    return l_sum;
}

bool Advent2::isNewInvalidID(const int64_t f_id)
{
    const int l_numDigitsID = numDigitsBase10(f_id);
    for (int l_numDigitsSeq = 1; l_numDigitsSeq <= (l_numDigitsID / 2); l_numDigitsSeq++)
    {
        if (isSeqRepeated(f_id, l_numDigitsID, l_numDigitsSeq))
        {
            return true;
        }
    }

    return false;
}

bool Advent2::isSeqRepeated(const int64_t f_id, const int f_numDigitsID, const int f_numDigitsSeq)
{
    if ((f_numDigitsID % f_numDigitsSeq) != 0)
    {
        return false;
    }

    const int l_numSeqs = f_numDigitsID / f_numDigitsSeq;
    const int64_t l_firstSeq = getSeq(f_id, 0, f_numDigitsSeq);
    for (int l_seqIdx = 1; l_seqIdx < l_numSeqs; l_seqIdx++)
    {
        int64_t l_seq = getSeq(f_id, l_seqIdx, f_numDigitsSeq);
        if (l_firstSeq != l_seq)
        {
            return false;
        }
    }

    return true;
}

int64_t Advent2::getSeq(const int64_t f_id, const int f_seqIdx, const int f_numDigitsSeq)
{
    const int64_t l_factorTop = pow10((f_seqIdx + 1) * f_numDigitsSeq);
    const int64_t l_top = (f_id / l_factorTop) * l_factorTop;
    const int64_t l_factorBot = pow10(f_seqIdx * f_numDigitsSeq);
    const int64_t l_seq = (f_id - l_top) / l_factorBot;

    return l_seq;
}
