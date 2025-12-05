#include "aoc/utils/inputs.hpp"
#include "aoc/utils/ranges.hpp"
#include "aoc/utils/strings.hpp"

#include <algorithm>
#include <cassert>
#include <print>
#include <set>

namespace aoc {

    using id = std::uint64_t;
    using id_range = aoc::range<id>;

} // namespace aoc

auto parse_ranges(const std::vector<std::string>& lines) {
    std::vector<aoc::id_range> ranges;
    for(const auto& line : lines) {
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
    for(const auto& line : lines) {
        assert(!line.empty());
        ids.emplace_back(static_cast<aoc::id>(std::stoull(line)));
    }
    return ids;
}

auto get_puzzle_input(int argc, char const* argv[]) {
    const auto input_path = aoc::utils::inputs::get_input_path(argc, argv);
    const auto input_string = aoc::utils::inputs::read_input(input_path);
    const auto input_blocks = aoc::utils::strings::split_blocks(input_string);
    assert(input_blocks.size() == 2);
    const auto range_lines = aoc::utils::strings::split_lines(input_blocks[0]);
    const auto ids_lines = aoc::utils::strings::split_lines(input_blocks[1]);
    return std::make_pair(parse_ranges(range_lines), parse_ids(ids_lines));
}

int main(int argc, char const* argv[]) {
    const auto [ranges, ids] = get_puzzle_input(argc, argv);
    std::uint64_t fresh_ingredients = 0;
    for(const auto id : ids) {
        bool fresh = false;
        for(const auto& [start, end] : ranges) {
            if(aoc::utils::ranges::is_between(id, start, end)) {
                fresh = true;
                break;
            }
        }
        if(fresh) {
            fresh_ingredients++;
        }
    }
    std::println("Fresh ingredients: {}", fresh_ingredients);

    auto sorted_ranges = ranges;
    std::sort(sorted_ranges.begin(), sorted_ranges.end(),
              [](const aoc::id_range& r1, const aoc::id_range& r2) { return r1.first < r2.first; });

    std::vector<aoc::id_range> merged_ranges;
    std::vector<aoc::id_range> already_merged;
    for(const auto& range : sorted_ranges) {
        aoc::id_range merged_range = range;
        if(std::ranges::contains(already_merged, range)) {
            continue;
        }
        for(const auto& other_range : sorted_ranges) {
            if(aoc::utils::ranges::overlaps(merged_range, other_range)) {
                merged_range = aoc::utils::ranges::merge_ranges(merged_range, other_range);
                already_merged.emplace_back(other_range);
            }
        }
        merged_ranges.emplace_back(merged_range);
    }

    std::uint64_t total_fresh_ids = 0;
    for(const auto& [start, end] : merged_ranges) {
        total_fresh_ids += (end - start + 1);
    }
    std::println("Total fresh ids: {}", total_fresh_ids);
    return 0;
}