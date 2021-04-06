#pragma once

#include "ds18b20/detail/type_traits/integral_constant.hpp"

#include <avr/io.hpp>
#include <util/delay.h>

namespace ds18b20 { namespace onewire {

template<typename Pin>
inline bool read_bit(Pin pin, detail::true_type) noexcept {
    using namespace avr::io;
    out(pin);
    low(pin);
    _delay_us(1);
    in(pin);
    high(pin);
    _delay_us(13);
    bool ret = is_high(pin);
    _delay_us(47); 
    return ret;
}

template<typename Pin>
inline bool read_bit(Pin pin, detail::false_type) noexcept {
    using namespace avr::io;
    out(pin);
    _delay_us(1);
    in(pin);
    _delay_us(13);
    bool ret = is_high(pin);
    _delay_us(47); 
    return ret;
}

/**
  Read 1 byte (LSB first)
  
  InternalPullup: 'true' activates the support to the usage of the
                   internal pull-up resistor of the MCU.
  pin: port pin that has the bus line.

  precondition: the function should be called in a context that an
  interrupt isn't possible.
*/
template<bool InternalPullup, typename Pin>
inline uint8_t read(Pin pin) noexcept {
    uint8_t byte{};
    for(uint8_t i{8}, mask{0x01}; i > 0; --i, mask <<= 1)
        if(read_bit(pin, detail::integral_constant<bool, InternalPullup>{}))
            byte |= mask;
    return byte;
}

}}//namespace ds18b20::onewire
