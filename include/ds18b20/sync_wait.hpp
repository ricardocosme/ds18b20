#pragma once

#include <stdint.h>

namespace ds18b20 {

class optional_temperature {
    uint8_t _value;
public:
    explicit optional_temperature(uint8_t v) : _value(v) {}
    auto value() const noexcept
    { return _value; }
    auto has_value() const noexcept
    { return _value != 254; }
};

/**
  Read the temperature using a blocking call
*/
template<typename Temperature>
inline optional_temperature sync_wait(Temperature co_temp) {
    while(true) {
        if(co_temp()) {
            if(co_temp.has_value())
                return optional_temperature{co_temp.value()};
            break;
        }
    }
    return optional_temperature{254};
}

}
