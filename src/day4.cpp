#include "aoc/utils/inputs.hpp"
#include "aoc/utils/strings.hpp"

#include <print>

namespace aoc {
    enum class location : char {
        empty = '.',
        roll = '@'
    };
    using row = std::vector<location>;
    using grid = std::vector<row>;
} // namespace aoc

auto parse_grid(const std::vector<std::string>& lines) {
    aoc::grid grid;
    for (const auto& line : lines) {
        aoc::row row;
        for (const auto& ch : line) {
            if (ch == static_cast<char>(aoc::location::empty)) {
                row.push_back(aoc::location::empty);
            } else if (ch == static_cast<char>(aoc::location::roll)) {
                row.push_back(aoc::location::roll);
            }
        }
        grid.push_back(row);
    }
    return grid;
}

auto get_puzzle_input(int argc, char const* argv[]) {
    const auto input_path = aoc::utils::inputs::get_input_path(argc, argv);
    const auto input_string = aoc::utils::inputs::read_input(input_path);
    const auto input_lines = aoc::utils::strings::split_lines(input_string);
    return parse_grid(input_lines);
}

auto count_rolls(const aoc::grid& grid) {
    std::uint64_t rolls_count = 0;
    for (const auto& row : grid) {
        for (const auto& loc : row) {
            if (loc == aoc::location::roll) {
                rolls_count++;
            }
        }
    }
    return rolls_count;
}

auto get_subgrid(const aoc::grid& grid, std::int64_t start_row, std::int64_t start_col, std::int64_t end_row,
                 std::int64_t end_col) {
    aoc::grid result;
    const aoc::grid subgrid(grid.begin() + start_row, grid.begin() + end_row + 1);
    for (const auto& row : subgrid) {
        result.push_back(aoc::row(row.begin() + start_col, row.begin() + end_col + 1));
    }
    return result;
}

auto get_accessible_locations(const aoc::grid& grid) {
    std::uint64_t accessible_locations_count = 0;
    for (std::int64_t row_idx = 0; row_idx < grid.size(); ++row_idx) {
        for (std::int64_t col_idx = 0; col_idx < grid[row_idx].size(); ++col_idx) {
            if (grid[row_idx][col_idx] == aoc::location::roll) {
                const auto start_x = std::max(row_idx - 1, static_cast<std::int64_t>(0));
                const auto start_y = std::max(col_idx - 1, static_cast<std::int64_t>(0));
                const auto end_x = std::min(row_idx + 1, static_cast<std::int64_t>(grid.size() - 1));
                const auto end_y = std::min(col_idx + 1, static_cast<std::int64_t>(grid[row_idx].size() - 1));
                const auto subgrid = get_subgrid(grid, start_x, start_y, end_x, end_y);
                std::uint64_t adjacent_roll_locations = count_rolls(subgrid);
                if (adjacent_roll_locations <= 4) {
                    accessible_locations_count++;
                }
            }
        }
    }
    return accessible_locations_count;
}

int main(int argc, char const* argv[]) {
    const auto grid = get_puzzle_input(argc, argv);
    std::print("Accessible locations: {}\n", get_accessible_locations(grid));
    return 0;
}
