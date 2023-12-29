#include "ex2023d2.h"

#include <regex>

using namespace std;
using namespace aoc;

namespace {
    int computeForColor(const std::string& line, const std::regex& pattern) {
        std::vector<int> vec;
        auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
        auto end = std::sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            vec.push_back(stoi((*it)[1]));
        }
        auto it = std::max_element(vec.begin(), vec.end());
        int color = it != vec.end() ? *it : 0;
        return color;
    }

    int compute(const std::string& line, int star) {
        static const int redTarget = 12;
        static const int greenTarget = 13;
        static const int blueTarget = 14;

        static const std::regex intPattern(R"((\d+))");

        static const std::regex redPattern(R"((\d+) red)");
        static const std::regex greenPattern(R"((\d+) green)");
        static const std::regex bluePattern(R"((\d+) blue)");

        std::smatch m;
        std::regex_search(line, m, intPattern);
        int game = stoi(m[1].str());

        int red = computeForColor(line, redPattern);
        int green = computeForColor(line, greenPattern);
        int blue = computeForColor(line, bluePattern);

        if (star == 1) {
            if (blue <= blueTarget && green <= greenTarget && red <= redTarget) {
                //std::cerr << "OK " << game << " : " << red << " red + " << green << " green + " << blue << " blue -> " << line << std::endl;
                return game;
            }
            else {
                //std::cerr << "IGNORE " << game << " : " << red << " red + " << green << " green + " << blue << " blue -> " << line << std::endl;
                return 0;
            }
        }
        else {
            return blue * green * red;
        }
    }
}

long long Ex2023d2::star1(std::istream& input) {
    int sum = 0;
    for (std::string line; std::getline(input, line); sum += compute(line, 1));
    return sum;
}

long long Ex2023d2::star2(std::istream& input) {
    int sum = 0;
    for (std::string line; std::getline(input, line); sum += compute(line, 2));
    return sum;
}
