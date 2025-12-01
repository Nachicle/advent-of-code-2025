cmake_minimum_required(VERSION 3.16)

project(advent-of-code-2025 CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(day1 src/day1.cpp)
target_include_directories(day1 PRIVATE include)