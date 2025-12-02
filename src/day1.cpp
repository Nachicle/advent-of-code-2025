#include "aoc/circular_dial.hpp"
#include "aoc/utils/inputs.hpp"
#include "aoc/utils/strings.hpp"

#include <iostream>
#include <map>

enum class turn_direction {
    LEFT,
    RIGHT
};

template <typename amount_type>
using movement = std::pair<turn_direction, amount_type>;

std::vector<movement<int>> parse_movements(const std::vector<std::string>& lines) {
    std::vector<movement<int>> movements;
    for (const auto& line : lines) {
        if (!line.empty()) {
            const auto direction = line.substr(0, 1);
            const auto amount = std::stoi(line.substr(1));
            if (direction == "L") {
                movements.emplace_back(turn_direction::LEFT, amount);
            } else if (direction == "R") {
                movements.emplace_back(turn_direction::RIGHT, amount);
            }
        }
    }
    return movements;
}

std::vector<movement<int>> get_puzzle_input(int argc, char const* argv[]) {
    const auto input_path = aoc::utils::inputs::get_input_path(argc, argv);
    const auto input_string = aoc::utils::inputs::read_input(input_path);
    const auto input_lines = aoc::utils::strings::split_lines(input_string);
    return parse_movements(input_lines);
}

int main(int argc, char const* argv[]) {
    const auto movements = get_puzzle_input(argc, argv);
    aoc::circular_dial<int> dial(50);
    size_t zero_clicks = 0;
    for (const auto& movement : movements) {
        const auto& [direction, amount] = movement;
        int previous_value = dial.value();
        if (direction == turn_direction::LEFT) {
            dial.turn_left(amount);
            if (dial.value() > previous_value) {
                zero_clicks++;
            }
        } else {
            dial.turn_right(amount);
            if (dial.value() < previous_value) {
                zero_clicks++;
            }
        }
        zero_clicks += amount / dial.range();
    }
    std::cout << "Zero clicks: " << zero_clicks << std::endl;
    return 0;
}
