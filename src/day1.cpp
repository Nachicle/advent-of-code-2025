#include "aoc/circular_dial.hpp"
#include "aoc/utils/inputs.hpp"
#include "aoc/utils/strings.hpp"

#include <print>

namespace aoc {

    enum class turn_direction : char {
        LEFT = 'L',
        RIGHT = 'R'
    };

    using amount_type = std::int64_t;
    using movement = std::pair<turn_direction, amount_type>;

} // namespace aoc

auto parse_movements(const std::vector<std::string>& lines) {
    std::vector<aoc::movement> movements;
    for(const auto& line : lines) {
        assert(!line.empty());
        const auto direction = line[0];
        const auto amount = std::stoll(line.substr(1));
        switch(direction) {
        case static_cast<char>(aoc::turn_direction::LEFT):
            movements.emplace_back(aoc::turn_direction::LEFT, amount);
            break;
        case static_cast<char>(aoc::turn_direction::RIGHT):
            movements.emplace_back(aoc::turn_direction::RIGHT, amount);
            break;
        }
    }
    return movements;
}

auto get_puzzle_input(int argc, char const* argv[]) {
    const auto input_path = aoc::utils::inputs::get_input_path(argc, argv);
    const auto input_string = aoc::utils::inputs::read_input(input_path);
    const auto input_lines = aoc::utils::strings::split_lines(input_string);
    return parse_movements(input_lines);
}

int main(int argc, char const* argv[]) {
    const auto movements = get_puzzle_input(argc, argv);
    aoc::circular_dial<aoc::amount_type> dial(50);
    std::int64_t zero_clicks = 0;
    for(const auto& movement : movements) {
        const auto& [direction, amount] = movement;
        const aoc::amount_type previous_value = dial.value();
        if(direction == aoc::turn_direction::LEFT) {
            dial.turn_left(amount);
            if(dial.value() > previous_value) {
                zero_clicks++;
            }
        } else {
            dial.turn_right(amount);
            if(dial.value() < previous_value) {
                zero_clicks++;
            }
        }
        zero_clicks += amount / dial.range();
    }
    std::println("Zero clicks: {}", zero_clicks);
    return 0;
}
