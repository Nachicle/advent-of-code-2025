#pragma once

namespace aoc::utils::ranges {

    template <typename T>
    bool is_between(const T& value, const T& lowest, const T& highest) {
        return value >= lowest && value <= highest;
    }

} // namespace aoc::utils::ranges
