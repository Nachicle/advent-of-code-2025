#include "aoc/utils/inputs.hpp"
#include "aoc/utils/ranges.hpp"
#include "aoc/utils/strings.hpp"

#include <cassert>
#include <numeric>
#include <print>
#include <ranges>
#include <set>

namespace aoc {

    using id = std::uint64_t;
    using id_range = aoc::range<id>;

} // namespace aoc

auto parse_ranges(std::string_view input_string) {
    const std::vector<std::string> range_strings = aoc::utils::strings::split(input_string, ",");
    std::vector<aoc::id_range> ranges;
    for(const auto& range : range_strings) {
        assert(!range.empty());
        const auto parts = aoc::utils::strings::split(range, "-");
        if(parts.size() == 2) {
            const auto start = static_cast<aoc::id>(std::stoull(parts[0]));
            const auto end = static_cast<aoc::id>(std::stoull(parts[1]));
            ranges.emplace_back(start, end);
        }
    }
    return ranges;
}

auto get_puzzle_input(int argc, char const* argv[]) {
    const auto input_path = aoc::utils::inputs::get_input_path(argc, argv);
    const auto input_string = aoc::utils::inputs::read_input(input_path);
    return parse_ranges(input_string);
}

auto has_repeated_patterns(aoc::id number) {
    const auto num_str = std::to_string(number);
    const auto len = num_str.length();
    for(auto pattern_len = 1; pattern_len <= len / 2; ++pattern_len) {
        const auto substr = num_str.substr(0, pattern_len);
        const auto occurrences = aoc::utils::strings::count_occurrences(num_str, substr);
        if(occurrences * pattern_len == len) {
            return true;
        }
    }
    return false;
}

int main(int argc, char const* argv[]) {
    const auto ranges = get_puzzle_input(argc, argv);
    std::set<aoc::id> invalid_ids;
    for(const auto& range : ranges) {
        auto invalid_by_pattern = aoc::utils::ranges::generate_range(range) | std::views::filter(has_repeated_patterns);
        invalid_ids.insert(invalid_by_pattern.begin(), invalid_by_pattern.end());
    }
    const auto sum_invalid = std::accumulate(invalid_ids.begin(), invalid_ids.end(), static_cast<aoc::id>(0));
    std::println("Sum of invalid IDs: {}", sum_invalid);
    return 0;
}
