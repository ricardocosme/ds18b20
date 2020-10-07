#pragma once

#include <util/delay.h>

#include "ds18b20/detail/bus/define.hpp"

namespace ds18b20::detail {

inline bool read_bit(uint8_t pin) {
    out(pin);
    _delay_us(1);
    in(pin);
    _delay_us(13);
    bool ret = PINB & (1 << pin);
    _delay_us(47);
    return ret;
}

inline uint8_t read(uint8_t pin) {
    uint8_t byte{};
    for(uint8_t mask{1}; mask; mask <<= 1) 
        if(read_bit(pin)) byte |= mask;
    return byte;
}

}//namespace ds18b20::detail

#include "ds18b20/detail/bus/undef.hpp"
