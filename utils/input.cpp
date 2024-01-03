#include "input.h"

#include <cassert>
#include <sstream>
#include <ranges>
#include <regex>

namespace aoc {
    void getlines(std::istream& src, std::vector<std::string>& dest) {
        for (std::string line; std::getline(src, line); dest.emplace_back(line));
    }
    
    void getgrid(std::istream& src, char border, std::vector<std::string>& dest) {
        std::string line;
        std::getline(src, line);

        // top border
        std::string::size_type n{ line.size() + 2 };
        dest.emplace_back(n, border);
        
        // first line
        dest.emplace_back(border + line + border);
        
        // other lines
        for (std::string line; std::getline(src, line); dest.emplace_back(border + line + border));
        
        // bottom border
        dest.emplace_back(n, border);
    }

	void digits(const std::string& src, std::vector<int>& dest) {
        for (const char& c : src) {
            if (c >= '0' && c <= '9') {
                dest.emplace_back(c - '0');
            }
        }
	}

    std::tuple<std::string::size_type, std::string> find_first_substr_of(const std::string_view& src, const std::unordered_set<std::string>& candidates) {
        // Keep track of indexes where a substring can start
        std::vector<std::pair<std::string, std::string::size_type>> track;

        // Only iterate once over the string
        for (std::string::size_type i = 0; i < src.size(); ++i) {
            const char& c = src[i];

            // Each time a candidate can start at this index, remember it
            for (const std::string& candidate : candidates) {
                if (candidate.front() == c) {
                    track.emplace_back(candidate, i);
                }
            }

            // For each tracked index-for-candidate, check if it still stands, and if the substring is now complete
            auto it = track.begin();
            while (it != track.end()) {
                const auto& p = *it;

                // If a character differs in the candidate: it is not a substring at this tracked index, forget it
                if (p.first[i - p.second] != c) {
                    it = track.erase(it);
                    continue;
                }
                // Otherwise it is still a possible substring

                // If the last character was just checked, then a substring has been found
                if (i - p.second == p.first.size() - 1) {
                    return { p.second, p.first };
                }

                ++it;
            }
        }

        return { std::string::npos, "" }; // no substring found
    }

    std::tuple<std::string::size_type, std::string> find_last_substr_of(const std::string_view& src, const std::unordered_set<std::string>& candidates) {
        // Keep track of indexes where a substring can start
        std::vector<std::pair<std::string, std::string::size_type>> track;

        // Only iterate once (backwards) over the string
        std::string::size_type i{ src.size() - 1 };
        for (auto rit = src.rbegin(); rit != src.rend(); ++rit) {
            const char& c = *rit;

            // Each time a candidate can end at this index, remember it
            for (const std::string& candidate : candidates) {
                if (candidate.back() == c) {
                    track.emplace_back(candidate, i);
                }
            }

            // For each tracked index-for-candidate, check if it still stands, and if the substring is now complete
            auto it = track.begin();
            while (it != track.end()) {
                const auto& p = *it;

                // If a character differs in the candidate: it is not a substring at this tracked index, forget it
                if (p.first[p.first.size() - 1 - (p.second - i)] != c) {
                    it = track.erase(it);
                    continue;
                }
                // Otherwise it is still a possible substring

                // If the "last" character was just checked, then a substring has been found
                if (p.second - i == p.first.size() - 1) {
                    return { i, p.first };
                }

                ++it;
            }

            --i;
        }

        return { std::string::npos, "" }; // no substring found
    }
}
