cmake_minimum_required(VERSION 3.10)

project(adventofcode)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(year2023
	2023/day1/ex2023d1.cpp 2023/day1/ex2023d1.h
)

add_subdirectory(core)
add_subdirectory(utils)

add_executable(aoc aoc.cpp ${year2023})
target_link_libraries(aoc PUBLIC core)
target_link_libraries(aoc PUBLIC utils)

source_group("2023" FILES ${year2023})

add_executable(today today.cpp today.h)
target_link_libraries(today PUBLIC core)
target_link_libraries(today PUBLIC utils)

set_property(TARGET aoc PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
set_property(TARGET today PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

target_include_directories(aoc PUBLIC "${CMAKE_SOURCE_DIR}")
target_include_directories(today PUBLIC "${CMAKE_SOURCE_DIR}")
