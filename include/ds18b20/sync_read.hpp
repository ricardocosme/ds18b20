#pragma once

#include "ds18b20/sensor.hpp"

#include <stdint.h>

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

template<typename Sensor>
inline optional_temperature sync_read(Sensor& sensor) noexcept {
    while(true)
        if(auto t = sensor.read()) {
            if(t.has_value()) return {t.value()};
            else return {};
        }
}

}
