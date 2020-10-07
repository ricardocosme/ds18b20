#pragma once

#include <util/delay.h>

#include "ds18b20/detail/bus/define.hpp"

namespace ds18b20::detail {

inline void write_bit(uint8_t pin, bool one) {
    _delay_us(1);
    out(pin);
    _delay_us(1);
    if(one) in(pin); //write 0 or 1
    _delay_us(60); //hold the signal for 60us + 1us(recovery time)
    in(pin); //release the bus
    //TODO: Shoul I disable the pullup resistor from pin?
}

inline void write(uint8_t pin, uint8_t byte) {
    for(uint8_t i{}; i < 8; ++i, byte >>= 1)
        write_bit(pin, byte & 0x01);
    //Why not?
    // for(int8_t i{0}; i < 7; ++i)
    //     write_bit(pin, byte & (1 << i));
}

}//namespace ds18b20::detail

#include "ds18b20/detail/bus/undef.hpp"
