#pragma once

#include <avr/io.hpp>
#include <util/delay.h>

namespace ds18b20 { namespace onewire {

template<typename Pin>
inline void write_bit(Pin pin, bool one, bool InternalPullup) noexcept {
    using namespace avr::io;
    out(pin);
    if(InternalPullup) low(pin);
    _delay_us(1);
    if(one) {
        if(InternalPullup) high(pin);
        else in(pin);
    }
    _delay_us(60); //hold the signal for 59us + 1us(recovery time)

    //release the bus
    in(pin); 
    if(InternalPullup) high(pin);
}

/**
  Write 1 byte (LSB first)
  
  InternalPullup: 'true' activates the support to the usage of the
                   internal pull-up resistor of the MCU.
  pin: port pin that has the bus line.
  byte: byte to be written.

  precondition: the function should be called in a context that an
  interrupt isn't possible.
*/
template<bool InternalPullup, typename Pin>
inline void write(Pin pin, uint8_t byte) noexcept {
    for(uint8_t i{}; i < 8; ++i, byte >>= 1)
        write_bit(pin, byte & 0x01, InternalPullup);
}

}}//namespace ds18b20::onewire

