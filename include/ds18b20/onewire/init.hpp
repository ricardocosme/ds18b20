#pragma once

#include <stdint.h>
#include <util/atomic.h>
#include <util/delay.h>

#include "ds18b20/avr/bus/define.hpp"

namespace ds18b20::onewire {

/** 
  Reset pulse
    
  pin: number of the port pin that has the bus line.

  Pulls the 1-Wire bus low for a minimum of 480μs. The bus master
  then releases the bus and goes into receive mode (RX). When the
  bus is released, the 5kpullup resistor pulls the 1-Wire bus high.
 */
template<bool InternalPullup>
inline void reset(uint8_t pin) noexcept {
    //pull the bus down for 480us
    out(pin);
    low(pin); 
    _delay_us(480);
    
    //release the bus
    in(pin);
    if constexpr(InternalPullup) high(pin);
}

/**
  Presence pulse

  pin: number of the port pin that has the bus line.

  When the DS18B20 detects the rising edge after a reset pulse and it
  waits 15μs to 60μs. After then transmits a presence pulse by
  pulling the 1-Wire bus low for 60μs to 240μs.
*/ 
template<bool InternalPullup>
inline void presence(uint8_t pin) noexcept {
    _delay_us(480);
}

/**
  Initialization: reset pulse followed by a presence pulse

  pin: number of the port pin that has the bus line.
*/
template<bool InternalPullup>
inline void init(uint8_t pin) noexcept {
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        reset<InternalPullup>(pin);
        presence<InternalPullup>(pin);
    }
}

}//namespace ds18b20::onewire

#include "ds18b20/avr/bus/undef.hpp"
