#include <cassert>
#include <chrono>
#include <fstream>
#include <ranges>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "exercisefactory.h"

#pragma region exercises
#include "2023/day1/ex2023d1.h"
#pragma endregion exercises

namespace {
    /// <summary>
    /// Parse commandline arguments.
    /// --name=value is an option.
    /// --name is a flag, meaning an option with an empty value.
    /// A positional argument cannot begin with '-'.
    /// Everything else is a positional argument.
    /// </summary>
    /// <param name="argc"></param>
    /// <param name="argv"></param>
    /// <param name="positional_arguments"></param>
    /// <param name="options"></param>
    void parseopt(int argc, char* argv[], std::vector<std::string>& positional_arguments, std::unordered_map<std::string, std::string>& options) {
        positional_arguments.clear();
        options.clear();

        for (size_t i = 1; i < argc; ++i) {
            std::string arg{ argv[i] };
            if (arg.starts_with('-')) {
                size_t k = arg.find('=');
                if (k == std::string::npos) {
                    options[arg.substr(2)] = "";
                }
                else {
                    options[arg.substr(2, k-2)] = arg.substr(k+1);
                }
            }
            else {
                positional_arguments.emplace_back(arg);
            }
        }
    }

#pragma region factory
    void setup_factory(aoc::ExerciseFactory& factory) {
        factory.prepare("2023", "day1", [](aoc::ExerciseFactory::PosArgs& args, aoc::ExerciseFactory::OptArgs& options) { return std::make_unique<Ex2023d1>(); });
    }
#pragma endregion factory
}

int main(int argc, char *argv[]) {
    typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> systime_ms;
    auto gettime = []() { return std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()); };

    std::vector<std::string> positional_arguments;
    std::unordered_map<std::string, std::string> options;

    parseopt(argc, argv, positional_arguments, options);
    assert(positional_arguments.size() >= 2);

    std::string year = positional_arguments[0];
    std::string day = "day" + positional_arguments[1];
    std::string filename = year + "/" + day + "/input.txt";

    positional_arguments.erase(positional_arguments.begin(), positional_arguments.begin()+2);
    if (positional_arguments.size() > 0) {
        filename = positional_arguments[0];
        positional_arguments.erase(positional_arguments.begin());
    }

    aoc::ExerciseFactory factory;
    setup_factory(factory);

    std::unique_ptr<aoc::Exercise> exercise = factory.build(year, day, positional_arguments, options);

    std::fstream file(filename, std::ios::in);

    systime_ms startTime, endTime;

    startTime = gettime();
    long long res1 = exercise->star1(file);
    endTime = gettime();

    std::cout << "Star 1: " << res1 << std::endl;
    std::cout << "(" << (endTime - startTime).count() << " ms)" << std::endl;
    std::cout << std::endl;

    file.clear();
    file.seekg(0, file.beg);

    startTime = gettime();
    long long res2 = exercise->star2(file);
    endTime = gettime();

    std::cout << "Star 2: " << res2 << std::endl;
    std::cout << "(" << (endTime - startTime).count() << " ms)" << std::endl;
    std::cout << std::endl;

    file.close();
    return 0;
}
