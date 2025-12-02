#include "aoc/utils/inputs.hpp"
#include "aoc/utils/strings.hpp"

#include <iostream>
#include <numeric>
#include <set>

using id = std::size_t;
using range = std::pair<id, id>;

std::vector<range> parse_ranges(std::string_view input_string) {
    std::vector<std::string> ranges_string = aoc::utils::strings::split(input_string, ",");
    std::vector<range> ranges;
    for (const auto& range : ranges_string) {
        if (!range.empty()) {
            const auto parts = aoc::utils::strings::split(range, "-");
            if (parts.size() == 2) {
                const id start = static_cast<id>(std::stoull(parts[0]));
                const id end = static_cast<id>(std::stoull(parts[1]));
                ranges.emplace_back(start, end);
            }
        }
    }
    return ranges;
}

std::vector<range> get_puzzle_input(int argc, char const* argv[]) {
    const auto input_path = aoc::utils::inputs::get_input_path(argc, argv);
    const auto input_string = aoc::utils::inputs::read_input(input_path);
    return parse_ranges(input_string);
}

template <typename FilterFunc>
std::vector<id> filter_ids(const range& ran, FilterFunc filter) {
    std::vector<id> ids;
    for (id i = ran.first; i <= ran.second; ++i) {
        if (filter(i)) {
            ids.push_back(i);
        }
    }
    return ids;
}

bool has_repeated_patterns(id number) {
    std::string num_str = std::to_string(number);
    const size_t len = num_str.length();
    if (num_str.substr(0, len / 2) == num_str.substr(len / 2, len - len / 2)) {
        return true;
    }
    return false;
}

int main(int argc, char const* argv[]) {
    const auto ranges = get_puzzle_input(argc, argv);
    std::set<id> invalid_ids;
    for (const auto& range : ranges) {
        const auto invalid_by_pattern = filter_ids(range, has_repeated_patterns);
        invalid_ids.insert(invalid_by_pattern.begin(), invalid_by_pattern.end());
    }
    const auto sum_invalid = std::accumulate(invalid_ids.begin(), invalid_ids.end(), static_cast<id>(0));
    std::cout << "Sum of invalid IDs: " << sum_invalid << std::endl;
    return 0;
}
