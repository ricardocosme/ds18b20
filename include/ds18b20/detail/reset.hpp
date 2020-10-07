#pragma once

#include <util/delay.h>

#include "ds18b20/detail/bus/define.hpp"

namespace ds18b20::detail {

inline void reset(uint8_t pin) {
    out(pin);
    low(pin); //pull the bus down for 480us
    _delay_us(480);
    in(pin); //release the bus and waits for 480us
    // _delay_us(60);
    // uint8_t ret = PINB & (1<<PB3);
    _delay_us(480);
}

}//namespace ds18b20::detail

#include "ds18b20/detail/bus/undef.hpp"
