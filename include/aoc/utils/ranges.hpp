#pragma once

#include <vector>

namespace aoc {

    template <typename range_type>
    using range = std::pair<range_type, range_type>;

    namespace utils::ranges {

        template <typename range_type>
        bool is_between(const range_type& value, const range_type& lowest, const range_type& highest) {
            return value >= lowest && value <= highest;
        }

        template <typename range_type>
        bool overlaps(const range<range_type>& range1, const range<range_type>& range2) {
            return range1.first <= range2.second && range2.first <= range1.second;
        }

        template <typename range_type>
        range<range_type> merge_ranges(const range<range_type>& range1, const range<range_type>& range2) {
            return {std::min(range1.first, range2.first), std::max(range1.second, range2.second)};
        }

        template <typename range_type>
        std::vector<range_type> generate_range(const range<range_type>& range) {
            std::vector<range_type> result;
            for(range_type i = range.first; i <= range.second; ++i) {
                result.push_back(i);
            }
            return result;
        }

    } // namespace utils::ranges

} // namespace aoc
