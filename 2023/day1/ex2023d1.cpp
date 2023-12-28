#include "ex2023d1.h"

#include <ranges>
#include <regex>
#include <string>
#include <unordered_map>

#include "input.h"

using namespace std;
using namespace aoc;

#ifdef EX2023DAY1_PART1_CPP11
long long Ex2023d1::star1(std::istream& input) {
    static const string candidates = "0123456789";

    int sum = 0;

    string line;
    while (getline(input, line)) {
        int first = line[line.find_first_of(candidates)] - '0';
        int last = line[line.find_last_of(candidates)] - '0';

        int calibration = 10 * first + last;
        sum += calibration;
    }

    return sum;
}
#else
long long Ex2023d1::star1(std::istream& input) {
    int sum = 0;

    string line;
    while (getline(input, line)) {
        auto digits = views::filter(line, aoc::isdigit);

        int first = digits.front() - '0';
        int last = digits.back() - '0';

        int calibration = 10 * first + last;
        sum += calibration;
    }

    return sum;
}
#endif

#if defined EX2023DAY1_PART1_REGEX
long long Ex2023d1::star2(std::istream& input) {
    // Positive lookahead that only consumes 1 char, so it can find overlapping substrings when searching iteratively.
    static regex re(R"((?=(\d|zero|one|two|three|four|five|six|seven|eight|nine)).)");

    unordered_map<string, int> mapping = {
        {"0", 0}, {"zero", 0},
        {"1", 1}, {"one", 1},
        {"2", 2}, {"two", 2},
        {"3", 3}, {"three", 3},
        {"4", 4}, {"four", 4},
        {"5", 5}, {"five", 5},
        {"6", 6}, {"six", 6},
        {"7", 7}, {"seven", 7},
        {"8", 8}, {"eight", 8},
        {"9", 9}, {"nine", 9}
    };

    int sum = 0;

    string line;
    while (getline(input, line)) {
        vector<int> digits;

        auto begin = sregex_iterator(line.begin(), line.end(), re);
        auto end = sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            digits.emplace_back(mapping[(*it)[1]]); // select the (first) capturing group, otherwise we would only get the first character, the one which is consumed
        }

        int calibration = 10 * digits.front() + digits.back();
        sum += calibration;
    }

    return sum;
}
#elif defined EX2023DAY1_PART1_REGEX_FIRST_LAST
long long Ex2023d1::star2(std::istream& input) {
    static const regex re_forward(R"(\d|zero|one|two|three|four|five|six|seven|eight|nine)");
    static const regex re_backward(R"(\d|orez|eno|owt|eerht|ruof|evif|xis|neves|thgie|enin)"); // the regex must also be reversed when searching backwards

    unordered_map<string, int> mapping = {
        {"0", 0}, {"zero", 0},  {"orez", 0},
        {"1", 1}, {"one", 1},   {"eno", 1},
        {"2", 2}, {"two", 2},   {"owt", 2},
        {"3", 3}, {"three", 3}, {"eerht", 3},
        {"4", 4}, {"four", 4},  {"ruof", 4},
        {"5", 5}, {"five", 5},  {"evif", 5},
        {"6", 6}, {"six", 6},   {"xis", 6},
        {"7", 7}, {"seven", 7}, {"neves", 7},
        {"8", 8}, {"eight", 8}, {"thgie", 8},
        {"9", 9}, {"nine", 9},  {"enin", 9}
    };

    int sum = 0;

    string line;
    while (getline(input, line)) {
        smatch m;
        regex_search(line.cbegin(), line.cend(), m, re_forward); // regex_search needs const iterators
        int first = mapping[m[0]];

        match_results<string::const_reverse_iterator> rm; // the useful smatch cannot be used when searching backwards, we must define it ourselves
        regex_search(line.crbegin(), line.crend(), rm, re_backward);
        int last = mapping[rm[0]];

        int calibration = 10 * first + last;
        sum += calibration;
    }

    return sum;
}
#else
long long Ex2023d1::star2(std::istream& input) {
    static const unordered_set<string> tokens = {
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };

    unordered_map<string, int> mapping = {
        {"0", 0}, {"zero", 0},
        {"1", 1}, {"one", 1},
        {"2", 2}, {"two", 2},
        {"3", 3}, {"three", 3},
        {"4", 4}, {"four", 4},
        {"5", 5}, {"five", 5},
        {"6", 6}, {"six", 6},
        {"7", 7}, {"seven", 7},
        {"8", 8}, {"eight", 8},
        {"9", 9}, {"nine", 9}
    };

    int sum = 0;

    string line;
    while (getline(input, line)) {
        auto [_, first_token] = aoc::find_first_substr_of(line, tokens);
        auto [__, last_token] = aoc::find_last_substr_of(line, tokens);

        int calibration = 10 * mapping[first_token] + mapping[last_token];
        sum += calibration;
    }

    return sum;
}
#endif
