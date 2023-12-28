#include "today.h"

#include <chrono>
#include <fstream>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <ranges>
#include <regex>
#include <string>
#include <unordered_map>

#include "input.h"

using namespace std;
using namespace aoc;

long long TodayExercise::star1(std::istream& input) {
    int sum = 0;
    for (string line; std::getline(input, line); ++sum); // placeholder
    return sum;
}

long long TodayExercise::star2(std::istream& input) {
    int sum = 0;
    for (string line; std::getline(input, line); ++sum); // placeholder
    return sum;
}

int main() {
    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> systime_ms;
    auto gettime = []() { return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()); };
    systime_ms startTime, endTime;

    std::fstream file("input.txt", std::ios::in);

    TodayExercise exercise;
    
    startTime = gettime();
    long long res1 = exercise.star1(file);
    endTime = gettime();

    std::cout << "Star 1: " << res1 << std::endl;
    std::cout << "(" << (endTime - startTime).count() << " ms)" << std::endl;
    std::cout << std::endl;

    file.clear();
    file.seekg(0, file.beg);

    startTime = gettime();
    long long res2 = exercise.star2(file);
    endTime = gettime();

    std::cout << "Star 2: " << res2 << std::endl;
    std::cout << "(" << (endTime - startTime).count() << " ms)" << std::endl;
    std::cout << std::endl;

    file.close();
    return 0;
}
