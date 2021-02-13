#pragma once

namespace ds18b20 {

class optional_temperature {
    uint8_t _value{255}; 
public:
    optional_temperature() = default;
    optional_temperature(uint8_t v) : _value(v) {}
    bool has_value() const noexcept { return _value != 255; }
    operator bool() const noexcept { return has_value(); }
    uint8_t value() const noexcept { return _value; }
};

}
