#pragma once

#include <type_traits>

namespace aoc {

template <typename DialType>
    requires std::is_arithmetic_v<DialType>
class circular_dial {

  public:
    circular_dial(DialType initial_value = 0, DialType min_value = 0, DialType max_value = 99)
        : min_value_(min_value), max_value_(max_value), value_(initial_value) {
        normalize();
    }

    void turn_left(DialType amount) {
        value_ -= amount;
        normalize();
    }

    void turn_right(DialType amount) {
        value_ += amount;
        normalize();
    }

    DialType range() const {
        return max_value_ - min_value_ + static_cast<DialType>(1);
    }

    DialType value() const {
        return value_;
    }

  private:
    void normalize() {
        value_ = (value_ - min_value_) % range();
        if (value_ < min_value_) {
            value_ += range();
        }
        value_ += min_value_;
    }
    DialType value_;
    DialType min_value_;
    DialType max_value_;
};

} // namespace aoc