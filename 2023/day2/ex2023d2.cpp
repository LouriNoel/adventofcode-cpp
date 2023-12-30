#include "ex2023d2.h"

#include <regex>
#include <unordered_map>

using namespace std;
using namespace aoc;

namespace {
    void parseLine(const string& line, int& id, int& r, int& g, int& b) {
        static const regex intPattern(R"(\d+)");

        smatch m;
        regex_search(line, m, intPattern);
        id = stoi(m[0]); // the first int is the game's id

        static const regex colorPattern(R"((\d+) (red|green|blue))");
        unordered_map<string, int*> max_cubes{ {"red", &r}, {"green", &g}, {"blue", &b} };
        r = 0; g = 0; b = 0;

        auto begin = sregex_iterator(line.begin(), line.end(), colorPattern);
        auto end = sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            int* cubes = max_cubes[(*it)[2]];
            *cubes = max(*cubes, stoi((*it)[1]));
        }
    }
}

long long Ex2023d2::star1(std::istream& input) {
    static constexpr int redTarget = 12;
    static constexpr int greenTarget = 13;
    static constexpr int blueTarget = 14;

    int sum = 0;
    star2_result = 0;

    string line;
    int id, red, green, blue;
    while (getline(input, line)) {
        parseLine(line, id, red, green, blue);

        if (blue <= blueTarget && green <= greenTarget && red <= redTarget) {
            sum += id;
        }

        star2_result += blue * green * red;
    }

    return sum;
}

long long Ex2023d2::star2(std::istream& input) {
    return star2_result;
}
