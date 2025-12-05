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
    for(const auto& line : lines) {
        aoc::row row;
        for(const auto& character : line) {
            switch(character) {
            case static_cast<char>(aoc::location::empty):
                row.emplace_back(aoc::location::empty);
                break;
            case static_cast<char>(aoc::location::roll):
                row.emplace_back(aoc::location::roll);
                break;
            }
        }
        grid.emplace_back(row);
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
    for(const auto& row : grid) {
        for(const auto& column : row) {
            if(column == aoc::location::roll) {
                rolls_count++;
            }
        }
    }
    return rolls_count;
}

auto get_subgrid(const aoc::grid& grid, std::int64_t start_row, std::int64_t start_column, std::int64_t end_row,
                 std::int64_t end_column) {
    aoc::grid result;
    const aoc::grid subgrid_rows(grid.begin() + start_row, grid.begin() + end_row + 1);
    for(const auto& row : subgrid_rows) {
        result.emplace_back(aoc::row(row.begin() + start_column, row.begin() + end_column + 1));
    }
    return result;
}

auto pick_available_rolls(const aoc::grid& grid) {
    std::uint64_t picked_rolls = 0;
    aoc::grid after_grid = grid;
    for(std::int64_t row_idx = 0; row_idx < grid.size(); ++row_idx) {
        for(std::int64_t col_idx = 0; col_idx < grid[row_idx].size(); ++col_idx) {
            if(grid[row_idx][col_idx] == aoc::location::roll) {
                const auto start_x = std::max(row_idx - 1, static_cast<std::int64_t>(0));
                const auto start_y = std::max(col_idx - 1, static_cast<std::int64_t>(0));
                const auto end_x = std::min(row_idx + 1, static_cast<std::int64_t>(grid.size() - 1));
                const auto end_y = std::min(col_idx + 1, static_cast<std::int64_t>(grid[row_idx].size() - 1));
                const auto subgrid = get_subgrid(grid, start_x, start_y, end_x, end_y);
                const auto adjacent_roll_locations = count_rolls(subgrid);
                if(adjacent_roll_locations <= 4) {
                    picked_rolls++;
                    after_grid[row_idx][col_idx] = aoc::location::empty;
                }
            }
        }
    }
    return std::make_pair(picked_rolls, after_grid);
}

int main(int argc, char const* argv[]) {
    auto grid = get_puzzle_input(argc, argv);
    std::uint64_t picked_rolls;
    std::uint64_t total_picked_rolls = 0;
    do {
        std::tie(picked_rolls, grid) = pick_available_rolls(grid);
        total_picked_rolls += picked_rolls;
    } while(picked_rolls > 0);
    std::print("Total picked rolls: {}", total_picked_rolls);
    return 0;
}
