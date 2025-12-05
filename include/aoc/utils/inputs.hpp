#pragma once

#include <cassert>
#include <filesystem>
#include <fstream>
#include <string>

namespace aoc::utils::inputs {

    std::filesystem::path get_input_path(int argc, char const* argv[]) {
        assert(argc == 2);
        return std::filesystem::path(argv[1]);
    }

    std::string read_input(std::filesystem::path file) {
        assert(std::filesystem::exists(file));
        std::ifstream infile(file);
        std::string content((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
        return content;
    }

} // namespace aoc::utils::inputs
