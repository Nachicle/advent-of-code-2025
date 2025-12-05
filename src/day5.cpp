#include "aoc/utils/inputs.hpp"
#include "aoc/utils/ranges.hpp"
#include "aoc/utils/strings.hpp"

#include <cassert>
#include <print>

namespace aoc {
    using id = std::uint64_t;
    using range = std::pair<id, id>;
} // namespace aoc

auto parse_ranges(const std::vector<std::string>& lines) {
    std::vector<aoc::range> ranges;
    for (const auto& line : lines) {
        assert(!line.empty());
        const auto parts = aoc::utils::strings::split(line, "-");
        assert(parts.size() == 2);
        const auto start = static_cast<aoc::id>(std::stoull(parts[0]));
        const auto end = static_cast<aoc::id>(std::stoull(parts[1]));
        ranges.emplace_back(start, end);
    }
    return ranges;
}

auto parse_ids(const std::vector<std::string>& lines) {
    std::vector<aoc::id> ids;
    for (const auto& line : lines) {
        assert(!line.empty());
        ids.push_back(static_cast<aoc::id>(std::stoull(line)));
    }
    return ids;
}

auto get_puzzle_input(int argc, char const* argv[]) {
    const auto input_path = aoc::utils::inputs::get_input_path(argc, argv);
    const auto input_string = aoc::utils::inputs::read_input(input_path);
    const auto input_blocks = aoc::utils::strings::split(input_string, "\n\n");
    const auto range_lines = aoc::utils::strings::split_lines(input_blocks[0]);
    const auto ids_lines = aoc::utils::strings::split_lines(input_blocks[1]);
    return std::make_pair(parse_ranges(range_lines), parse_ids(ids_lines));
}

int main(int argc, char const* argv[]) {
    const auto [ranges, ids] = get_puzzle_input(argc, argv);
    std::uint64_t fresh_ingredients = 0;
    for (const auto id : ids) {
        bool fresh = false;
        for (const auto& [start, end] : ranges) {
            if (aoc::utils::ranges::is_between(id, start, end)) {
                fresh = true;
                break;
            }
        }
        if (fresh) {
            fresh_ingredients++;
        }
    }
    std::print("Fresh ingredients: {}", fresh_ingredients);
    return 0;
}