#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace aoc::utils::strings {

    std::vector<std::string> split(std::string_view str, std::string_view delimiter) {
        std::vector<std::string> tokens;
        size_t start = 0;
        size_t end = str.find(delimiter);
        while(end != std::string_view::npos) {
            tokens.emplace_back(str.substr(start, end - start));
            start = end + delimiter.length();
            end = str.find(delimiter, start);
        }
        tokens.emplace_back(str.substr(start));
        return tokens;
    }

    std::vector<std::string> split_lines(std::string_view str) {
        return split(str, "\n");
    }

    std::vector<std::string> split_blocks(std::string_view str) {
        return split(str, "\n\n");
    }

    size_t count_occurrences(std::string_view str, std::string_view sub) {
        size_t count = 0;
        size_t pos = 0;
        while((pos = str.find(sub, pos)) != std::string_view::npos) {
            ++count;
            pos += sub.length();
        }
        return count;
    }

} // namespace aoc::utils::strings