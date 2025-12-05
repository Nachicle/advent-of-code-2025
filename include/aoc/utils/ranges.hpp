#pragma once

#include <vector>

namespace aoc {

    template <typename T>
    using range = std::pair<T, T>;

    namespace utils::ranges {

        template <typename T>
        bool is_between(const T& value, const T& lowest, const T& highest) {
            return value >= lowest && value <= highest;
        }

        template <typename T>
        bool overlaps(const range<T>& range1, const range<T>& range2) {
            return range1.first <= range2.second && range2.first <= range1.second;
        }

        template <typename T>
        range<T> merge_ranges(const range<T>& range1, const range<T>& range2) {
            return {std::min(range1.first, range2.first), std::max(range1.second, range2.second)};
        }

    } // namespace utils::ranges

} // namespace aoc
