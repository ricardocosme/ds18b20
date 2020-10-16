#pragma once

#include <util/atomic.h>
#include <util/delay.h>

#include "ds18b20/avr/bus/define.hpp"

namespace ds18b20::onewire {

template<bool InternalPullup>
inline bool read_bit(uint8_t pin) noexcept {
    out(pin);
    if constexpr(InternalPullup) low(pin);
    _delay_us(1);
    in(pin);
    if constexpr(InternalPullup) high(pin);
    _delay_us(13);
    bool ret = PINB & (1 << pin);
    _delay_us(47); 
    return ret;
}

/**
  Read 1 byte 
  
  InternalPullup: 'true' activates the support to the usage of the
                   internal pullup resistor of the MCU.
  pin: number of the port pin that has the bus line.
*/
template<bool InternalPullup>
inline uint8_t read(uint8_t pin) noexcept {
    uint8_t byte{};
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for(uint8_t mask{1}; mask; mask <<= 1) 
            if(read_bit<InternalPullup>(pin)) byte |= mask;
    }
    return byte;
}

}//namespace ds18b20::onewire

#include "ds18b20/avr/bus/undef.hpp"
