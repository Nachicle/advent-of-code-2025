#include "aoc/utils/inputs.hpp"
#include "aoc/utils/strings.hpp"

#include <algorithm>
#include <cassert>
#include <print>

namespace aoc {
    using battery = std::uint64_t;
    using bank = std::vector<battery>;
} // namespace aoc

auto parse_banks(std::string_view input_string) {
    std::vector<std::string> bank_strings = aoc::utils::strings::split_lines(input_string);
    std::vector<aoc::bank> banks;
    for (const auto& bank_str : bank_strings) {
        assert(!bank_str.empty());
        aoc::bank bank;
        for (const auto& battery_char : bank_str) {
            bank.push_back(static_cast<aoc::battery>(battery_char - '0'));
        }
        banks.push_back(bank);
    }
    return banks;
}

auto get_puzzle_inputs(int argc, char const* argv[]) {
    const auto input_path = aoc::utils::inputs::get_input_path(argc, argv);
    const auto input_string = aoc::utils::inputs::read_input(input_path);
    return parse_banks(input_string);
}

auto find_largest_joltage(const aoc::bank& bank) {
    auto largest_left_battery = std::max_element(bank.begin(), bank.end());
    if (largest_left_battery == bank.end() - 1) {
        const auto largest_right_battery = largest_left_battery;
        largest_left_battery = std::max_element(bank.begin(), largest_right_battery);
        return *largest_left_battery * 10 + *largest_right_battery;
    } else {
        const auto largest_right_battery = std::max_element(largest_left_battery + 1, bank.end());
        return *largest_left_battery * 10 + *largest_right_battery;
    }
}

int main(int argc, char const* argv[]) {
    const auto banks = get_puzzle_inputs(argc, argv);
    aoc::battery total_joltage = 0;
    for (const auto& bank : banks) {
        total_joltage += find_largest_joltage(bank);
    }
    std::print("Total joltage: {}\n", total_joltage);
    return 0;
}
