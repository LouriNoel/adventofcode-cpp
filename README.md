# Advent of Code (C++)

Challenging myself to do [adventofcode](https://adventofcode.com) in C++

My goal is to make a little C++ project using CMake, so I can learn it as well as modern C++.

I intend to improve my solutions from time to time.

## Setting up the project

```
mkdir -p build
cd build
cmake ..
cmake --build .
```

Add a `input.txt` file at the root of the project, which is your input for the day.
Then edit the `today.cpp` file, build it and run it.

To run the other days, place your `input.txt` file in the corresponding folder.
Then build and run the *aoc* target with the arguments *year* and *day*:
```
./build/Debug/aoc.exe 2023 1
```
