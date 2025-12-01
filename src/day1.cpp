#include "aoc/circular_dial.hpp"
#include "aoc/utils/inputs.hpp"

#include <iostream>
#include <map>

enum class turn_direction { LEFT, RIGHT };
std::map<std::string, turn_direction> string_to_turn_direction = {
    {"L", turn_direction::LEFT}, {"R", turn_direction::RIGHT}};

template <typename amount_type>
using movement = std::pair<turn_direction, amount_type>;

std::vector<movement<int>>
parse_movements(const std::vector<std::string> &lines) {
    std::vector<movement<int>> movements;
    for (const auto &line : lines) {
        if (!line.empty()) {
            const auto direction = line.substr(0, 1);
            const auto amount = std::stoi(line.substr(1));
            movements.emplace_back(string_to_turn_direction[direction], amount);
        }
    }
    return movements;
}

int main(int argc, char const *argv[]) {
    const auto input =
        aoc::utils::read_input(aoc::utils::get_input_path(argc, argv));
    const auto movements = parse_movements(input);
    aoc::circular_dial<int> dial(50);
    size_t zero_clicks = 0;
    for (const auto &movement : movements) {
        const auto &[direction, amount] = movement;
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
