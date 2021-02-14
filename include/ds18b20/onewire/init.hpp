#pragma once

#include <avr/io.hpp>
#include <stdint.h>
#include <util/delay.h>

namespace ds18b20 { namespace onewire {

/** 
  Reset pulse
    
  pin: number of the port pin that has the bus line.

  Pulls the 1-Wire bus low for a minimum of 480μs. The bus master
  then releases the bus and goes into receive mode (RX). When the
  bus is released, the 5kpullup resistor pulls the 1-Wire bus high.
 */
template<typename Pin>
inline void reset(Pin pin, bool InternalPullup) noexcept {
    using namespace avr::io;
    //pull the bus down for 480us
    out(pin);
    low(pin); 
    _delay_us(480);
    
    //release the bus
    in(pin);
    if(InternalPullup) high(pin);
}

/**
  Presence pulse

  pin: port pin that has the bus line.

  When the DS18B20 detects the rising edge after a reset pulse, it
  waits 15μs to 60μs and then transmits a presence pulse by
  pulling the 1-Wire bus low for 60μs to 240μs.
*/ 
template<bool InternalPullup>
inline void presence() noexcept {
    _delay_us(480);
}

/**
  Initialization sequence: reset pulse transmitted by the master
  followed by a presence pulse(s) transmitted by the slave(s).

  pin: port pin that has the bus line.

  precondition: the function should be called in a context that an
  interrupt isn't possible.
*/
template<bool InternalPullup, typename Pin>
inline void init(Pin pin) noexcept {
    reset(pin, InternalPullup);
    presence<InternalPullup>();
}

}}//namespace ds18b20::onewire

