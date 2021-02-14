#pragma once

#include "ds18b20/detail/global.hpp"

#include <stdint.h>

/** 
  This file has policies to the instantiation of a 'thermo'

  These policies can be used to optimize or free some features which
  have costs to the code size and/or to the runtime of the driver.
*/

namespace ds18b20 {

/**
  It enables temperature values with decimals or fractions
  
  Take a look at temperature.hpp to see the 'temperature' abstraction
  with support to decimals. For example, if the 'thermo' is
  instantiated with 9 or 10 bits of resolution, then there is a
  temperature::decimal() with type unit8_t to represent the decimal
  part of the value. It's possible to save some instructions if this
  policy isn't enabled.
*/
struct WithDecimal
{ constexpr static bool with_decimal{true}; };

#if __cplusplus >= 201703L
inline constexpr WithDecimal with_decimal;
#else
namespace {
constexpr auto& with_decimal{detail::global<WithDecimal>::instance};
}//anonymous namespace
#endif

/**
  It allows the usage of the internal pullup resistor from the MCU I/O
  Port
  
  This policy can be enabled with a circuit which uses an external
  pullup resistor. When enabled this policy add some instructions to
  allow the usage of the internal pullup resistor of the bus pin.
*/
struct InternalPullup { constexpr static bool internal_pullup{true}; };

#if __cplusplus >= 201703L
inline constexpr InternalPullup internal_pullup;
#else
namespace {
constexpr auto& internal_pullup{detail::global<InternalPullup>::instance};
}//anonymous namespace
#endif

/**
  Resolution
  
  This policy defines the resolution used to convert the
  temperature. The default value is 12bits, which is the default value
  of the sensor. Low resolutions are faster than high resolution in
  the conversion time. This policy doesn't setup the sensor to operate
  with an especific resolution, it only define to the driver what is
  the resolution used by the hardware(sensor). Take a look at
  resolution.hpp to see how to setup the sensor to operate with a
  specific resolution.
*/
namespace resolution {

struct _9bits_t { constexpr static uint8_t resolution = 9; };
struct _10bits_t { constexpr static uint8_t resolution = 10; };
struct _11bits_t { constexpr static uint8_t resolution = 11; };
struct _12bits_t { constexpr static uint8_t resolution = 12; };

#if __cplusplus >= 201703L
inline constexpr _9bits_t _9bits;
inline constexpr _10bits_t _10bits;
inline constexpr _11bits_t _11bits;
inline constexpr _12bits_t _12bits;
#else
namespace {
constexpr auto& _9bits{detail::global<_9bits_t>::instance};
constexpr auto& _10bits{detail::global<_10bits_t>::instance};
constexpr auto& _11bits{detail::global<_11bits_t>::instance};
constexpr auto& _12bits{detail::global<_12bits_t>::instance};
}//anonymous namespace
#endif

} //namespace resolution

}
