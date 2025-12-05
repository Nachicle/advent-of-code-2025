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
    const std::vector<std::string> bank_strings = aoc::utils::strings::split_lines(input_string);
    std::vector<aoc::bank> banks;
    for(const auto& bank_str : bank_strings) {
        assert(!bank_str.empty());
        aoc::bank bank;
        for(const auto& battery_char : bank_str) {
            bank.emplace_back(static_cast<aoc::battery>(battery_char - '0'));
        }
        banks.emplace_back(bank);
    }
    return banks;
}

auto get_puzzle_inputs(int argc, char const* argv[]) {
    const auto input_path = aoc::utils::inputs::get_input_path(argc, argv);
    const auto input_string = aoc::utils::inputs::read_input(input_path);
    return parse_banks(input_string);
}

std::uint64_t find_largest_joltage(const auto bank_begin, const auto bank_end, std::uint64_t number_of_batteries = 2) {
    auto largest_left_battery = std::max_element(bank_begin, bank_end - (number_of_batteries - 1));
    if(number_of_batteries == 1) {
        return *largest_left_battery;
    }
    auto right_sum = find_largest_joltage(largest_left_battery + 1, bank_end, number_of_batteries - 1);
    return *largest_left_battery * std::pow(10, number_of_batteries - 1) + right_sum;
}

int main(int argc, char const* argv[]) {
    const auto banks = get_puzzle_inputs(argc, argv);
    aoc::battery total_joltage = 0;
    for(const auto& bank : banks) {
        total_joltage += find_largest_joltage(bank.begin(), bank.end(), 12);
    }
    std::print("Total joltage: {}\n", total_joltage);
    return 0;
}
