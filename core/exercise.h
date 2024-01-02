#pragma once

#include <istream>

namespace aoc {
    class Exercise {
    public:
        virtual long long star1(std::istream& input) = 0;
        virtual long long star2(std::istream& input) = 0;

    protected:
        long long star2_result = 0;
    };
}
