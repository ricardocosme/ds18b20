#pragma once

#include <stdint.h>

namespace ds18b20 {

template<typename T>
class lazy_temperature {
    T _value{255};
public:
    using value_type = T;
    lazy_temperature() = default;
    lazy_temperature(T v) : _value(v) {}
    bool has_value() const noexcept { return _value != 254; }
    bool done() const noexcept { return _value != 255; }
    operator bool() const noexcept { return done(); }
    T value() const noexcept { return _value; }
};

template<typename T>
class lazy_temperature_with_decimal {
    T _value{255};
public:
    using value_type = T;
    lazy_temperature_with_decimal() = default;
    lazy_temperature_with_decimal(T v) : _value(v) {}
    bool has_value() const noexcept { return _value.whole != 254; }
    bool done() const noexcept { return _value.whole != 255; }
    operator bool() const noexcept { return done(); }
    uint8_t value() const noexcept { return _value.whole; }
    typename T::decimal_t decimal() const noexcept { return _value.decimal; }
};

template<typename Decimal>
struct FP {
    using decimal_t = Decimal;
    uint8_t whole;
    Decimal decimal;
};

}
