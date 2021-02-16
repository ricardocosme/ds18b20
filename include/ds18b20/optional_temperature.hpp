#pragma once

namespace ds18b20 {

template<typename T>
class optional_temperature {
    T _value{255}; 
public:
    optional_temperature() = default;
    optional_temperature(T v) : _value(v) {}
    bool has_value() const noexcept { return _value != 255; }
    operator bool() const noexcept { return has_value(); }
    T value() const noexcept { return _value; }
};

template<typename T>
class optional_temperature_with_decimal {
    T _value{255}; 
public:
    optional_temperature_with_decimal() = default;
    optional_temperature_with_decimal(T v) : _value(v) {}
    bool has_value() const noexcept { return _value.whole != 255; }
    operator bool() const noexcept { return has_value(); }
    uint8_t value() const noexcept { return _value.whole; }
    typename T::decimal_t decimal() const noexcept { return _value.decimal; }
};

}
