#pragma once

#include "ds18b20/commands/copy_scratchpad.hpp"
#include "ds18b20/commands/write_scratchpad.hpp"
#include "ds18b20/detail/addr_device.hpp"

namespace ds18b20::resolution {

/**
  Defines the resolution of the sensoor

  This function defines the resolution of the themometer at the
  hardware level. By default the sensor has a 12 bits resolution. The
  resolution can be of 9, 10, 11 or 12 bits. The best approach is to
  choose one and define it using this function only one time saving
  the configuration in the EEPROM.

  | Resolution | Max. conversion time | Decimal increment |
  | 9 bits     | 93.75ms              |               0.5 |
  | 10 bits    | 187.5ms              |             0.250 |
  | 11 bits    | 375ms                |             0.125 |
  | 12 bits    | 750ms                |            0.0625 |
*/
template<typename Thermo>
inline void set(Thermo& thermo, bool save_to_eeprom = true) {
    detail::addr_device<Thermo::internal_pullup, typename Thermo::Rom>(thermo.pin);
    uint8_t resolution;
    if constexpr(Thermo::resolution == 9)
        resolution = 0x1F;
    else if(Thermo::resolution == 10)
        resolution = 0x3F;
    else if(Thermo::resolution == 11)
        resolution = 0x5F;
    else if(Thermo::resolution == 12)
        resolution = 0x7F;
    else static_assert("Resolution is out of the range [9, 12]bits");
    commands::write_scratchpad<Thermo::internal_pullup>(thermo.pin, resolution);
    
    if(save_to_eeprom) {
        detail::addr_device<Thermo::internal_pullup, typename Thermo::Rom>(thermo.pin);
        commands::copy_scratchpad<Thermo::internal_pullup>(thermo.pin);
    }
}

}
