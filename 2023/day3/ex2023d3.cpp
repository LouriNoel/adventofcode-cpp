#include "ex2023d3.h"

#include <regex>
#include <vector>

#include "input.h"

using namespace std;
using namespace aoc;

namespace {
    struct Symbol;

    struct Number {
        int value;
        int start;
        int last; // excluded
        std::vector<Symbol*> linkedSymbols;
    };

    struct Symbol {
        char value;
        int pos;
        std::vector<Number*> linkedNumbers;
    };

    void parseLineForNumbers(std::string line, std::vector<Number>& vec) {
        static const std::regex re(R"(\d+)");

        auto begin = std::sregex_iterator(line.begin(), line.end(), re);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            vec.emplace_back(
                stoi(it->str()),
                it->position(),
                it->position() + it->length()
            );
        }
    }

    void parseLineForSymbols(std::string line, std::vector<Symbol>& vec) {
        static const std::regex re(R"([^\d.])");

        auto begin = std::sregex_iterator(line.begin(), line.end(), re);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            vec.emplace_back(it->str()[0], it->position());
        }
    }
}

long long Ex2023d3::star1(std::istream& input) {
    std::vector<std::vector<Number>> numbers;
    std::vector<std::vector<Symbol>> symbols;

    std::vector<std::string> lines;
    aoc::getgrid(input, '.', lines);

    for (const std::string& line : lines) {
        parseLineForNumbers(line, numbers.emplace_back());
        parseLineForSymbols(line, symbols.emplace_back());
    }
    int n = numbers.size();

    for (int i = 0; i < n; ++i) { // for each line
        for (auto& sb : symbols[i]) { // for each symbol of the line
            for (int j = i - 1; j < i + 2; ++j) { // for each neighbouring line
                for (auto& nb : numbers[j]) { // for each number of one of these lines (sorted left to right)
                    // f >= nb.start-1 && f <= nb.last
                    if (nb.start - 1 > sb.pos) {
                        break; // following numbers are too far on the right
                    }
                    else if (nb.last >= sb.pos) { // number and symbol are in contact, so link them together
                        nb.linkedSymbols.push_back(&sb);
                        sb.linkedNumbers.push_back(&nb);
                    }
                }
            }
        }
    }

    // star 1
    int sum = 0;
    for (auto& row : numbers)
        for (auto& nb : row)
            if (!nb.linkedSymbols.empty())
                sum += nb.value;

    // star 2
    star2_result = 0;
    for (auto& row : symbols)
        for (auto& sb : row)
            if (sb.value == '*' && sb.linkedNumbers.size() == 2)
                star2_result += (long long) sb.linkedNumbers[0]->value * sb.linkedNumbers[1]->value;

    return sum;
}

long long Ex2023d3::star2(std::istream& input) {
    return star2_result;
}
