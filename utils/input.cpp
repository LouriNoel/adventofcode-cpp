#include "input.h"

#include <sstream>
#include <regex>

namespace aoc {
    void getlines(std::istream& src, std::vector<std::string>& dest) {
        for (std::string line; std::getline(src, line); dest.emplace_back(line));
    }

	void digits(const std::string& src, std::vector<int>& dest) {
        for (const char& c : src) {
            if (c >= '0' && c <= '9') {
                dest.emplace_back(c - '0');
            }
        }
	}
}
