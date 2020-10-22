#pragma once

#include <util/atomic.h>
#include <util/delay.h>

#include "ds18b20/avr/gpio.hpp"

namespace ds18b20::onewire {

template<bool InternalPullup>
inline void write_bit(uint8_t pin, bool one) noexcept {
    out(pin);
    if constexpr(InternalPullup) low(pin);
    _delay_us(1);
    if(one) {
        if constexpr (InternalPullup) {
            high(pin);
        } else {
            in(pin);
        }
    }
    _delay_us(60); //hold the signal for 59us + 1us(recovery time)

    //release the bus
    in(pin); 
    if constexpr(InternalPullup) high(pin);
}

/**
  Write 1 byte (LSB first)
  
  InternalPullup: 'true' activates the support to the usage of the
                   internal pullup resistor of the MCU.
  pin: number of the port pin that has the bus line.
  byte: byte to be written
*/
template<bool InternalPullup>
inline void write(uint8_t pin, uint8_t byte) noexcept {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for(uint8_t i{}; i < 8; ++i, byte >>= 1)
            write_bit<InternalPullup>(pin, byte & 0x01);
    }
}

}//namespace ds18b20::onewire

