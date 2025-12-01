#pragma once

#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace aoc::utils {

std::filesystem::path get_input_path(int argc, char const *argv[]) {
    if (argc != 2) {
        throw std::runtime_error("Input path not provided");
    }
    return std::filesystem::path(argv[1]);
}

std::vector<std::string> read_input(std::filesystem::path file) {
    std::vector<std::string> lines;
    std::ifstream infile(file);
    std::string line;
    while (std::getline(infile, line)) {
        lines.push_back(line);
    }
    return lines;
}

} // namespace aoc::utils
