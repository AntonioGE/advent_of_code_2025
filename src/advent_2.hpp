#pragma once

#include <string>
#include <vector>
#include <optional>
#include <cstdint>

class Advent2
{
public:
    static int64_t solvePartOne(const std::string &f_filePath);
    static int64_t solvePartTwo(const std::string &f_filePath);

private:
    struct Range
    {
        int64_t start;
        int64_t end;
    };    

private:
    static std::optional<std::vector<Range>> readRanges(const std::string &f_filePath);
    static int64_t sumAllInvalidIDs(const std::vector<Range> &f_ranges);
    static int64_t sumRangeInvalidIDs(const Range &f_range);
    static bool isInvalidID(const int64_t f_id);
    static int numDigitsBase10(const int64_t f_value);
    static bool isEven(const int64_t f_value);
    static int64_t pow10(const unsigned int f_numZeros);
    static int64_t sumAllNewInvalidIDs(const std::vector<Range> &f_ranges);
    static int64_t sumRangeNewInvalidIDs(const Range &f_range);
    static bool isNewInvalidID(const int64_t f_id);
    static bool isSeqRepeated(const int64_t f_id, const int f_numDigitsID, const int f_numDigitsSeq);
    static int64_t getSeq(const int64_t f_id, const int f_seqIdx, const int f_numDigitsSeq);

};