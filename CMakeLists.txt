cmake_minimum_required(VERSION 3.16)

project(advent-of-code-2025 CXX)
set(CMAKE_CXX_STANDARD 23)

add_executable(day1 src/day1.cpp)
target_include_directories(day1 PRIVATE include)

add_executable(day2 src/day2.cpp)
target_include_directories(day2 PRIVATE include)

add_executable(day3 src/day3.cpp)
target_include_directories(day3 PRIVATE include)

add_executable(day4 src/day4.cpp)
target_include_directories(day4 PRIVATE include)