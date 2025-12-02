#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace aoc::utils::inputs {

std::filesystem::path get_input_path(int argc, char const* argv[]) {
    if (argc != 2) {
        throw std::runtime_error("Input path not provided");
    }
    return std::filesystem::path(argv[1]);
}

std::string read_input(std::filesystem::path file) {
    std::ifstream infile(file);
    std::string content((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    return content;
}

} // namespace aoc::utils::inputs
