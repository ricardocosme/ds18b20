#pragma once

#include <avr/io.hpp>
#include <util/atomic.h>
#include <util/delay.h>

namespace ds18b20::onewire {

template<bool InternalPullup, typename Pin>
inline bool read_bit(Pin pin) noexcept {
    using namespace avr::io;
    out(pin);
    if constexpr(InternalPullup) low(pin);
    _delay_us(1);
    in(pin);
    if constexpr(InternalPullup) high(pin);
    _delay_us(13);
    bool ret = is_high(pin);
    _delay_us(47); 
    return ret;
}

/**
  Read 1 byte (LSB first)
  
  InternalPullup: 'true' activates the support to the usage of the
                   internal pullup resistor of the MCU.
  pin: number of the port pin that has the bus line.
*/
template<bool InternalPullup, typename Pin>
inline uint8_t read(Pin pin) noexcept {
    uint8_t byte{};
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        for(uint8_t i{8}, mask{0x01}; i > 0; --i, mask <<= 1)
            if(read_bit<InternalPullup>(pin)) byte |= mask;
    }
    return byte;
}

}//namespace ds18b20::onewire
