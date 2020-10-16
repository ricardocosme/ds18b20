#pragma once

#include "ds18b20/commands/conversion.hpp"
#include "ds18b20/detail/policies.hpp"
#include "ds18b20/onewire/init.hpp"
#include "ds18b20/onewire/write.hpp"
#include "ds18b20/rom.hpp"
#include "ds18b20/temperature.hpp"
// #include "ds18b20/commands/read_rom.hpp"

#include <ds18b20/type_traits.hpp>
#include <stdint.h>


namespace ds18b20 {

/**
   Represents the sensor DS18B20

   pin: number of the port pin that has the bus line.
   rom_: Rom address of the sensor or SkipRom. Default is
         SkipRom. Take a look at 'rom.hpp' to know more.
   Policies: policies to optimize or enable some features. Take a look
             at 'policies.hpp' to know more.

   Examples:

     1. Sensor with the bus line(data Input/Output [DQ]) connected to
        the pin PB3 using SkipRom:

       using thermo = sensor<PB3>;

     2. Sensor that has the Rom code {40, 251, 43, 31, 5, 0, 0, 139}:

       using thermo = sensor<PB3, Rom<40, 251, 43, 31, 5, 0, 0, 139> >;

     3. Sensor configured with 9bits of resolution:

       using thermo = sensor<
         PB3, 
         Rom<40, 251, 43, 31, 5, 0, 0, 139>,
         resolution::_9bits_t>;

     4. Sensor configured with 10bits of resolution and decimal values enabled:

       using thermo = sensor<
         PB3, 
         Rom<40, 251, 43, 31, 5, 0, 0, 139>,
         resolution::_10bits_t,
         WithDecimal>;

     5. Sensor using the internal pullup resistors from the MCU:

       using thermo = sensor<
         PB3, 
         Rom<40, 251, 43, 31, 5, 0, 0, 139>,
         resolution::_9bits_t,
         InternalPullup>;

     Some notes about resolution:

       1. The default resolution is 12bits, which is the same default
          resolution used by the hardware.
       2. This configuration doesn't change the resolution of the
          sensor, in other words, the configuration only informs the
          resolution value that is used by the hardware to the sofware
          abstraction, if the programmer wants to change the hardware
          resolution it should call function 'resolution::set()'
          defined at 'resolution.hpp'.

     Features that aren't available:
       1. Negative temperatures
       2. Search Rom
       3. Alarm 
       4. Parasite power mode

       Datasheet:
       https://datasheets.maximintegrated.com/en/ds/DS18B20.pdf
 */
template<uint8_t pin,
         typename rom_ = SkipRom,
         typename... Policies>
class sensor {
    using policies = decltype(detail::policies(declval<Policies>()...));
    static constexpr bool has_rom = !is_same<rom_, SkipRom>::value;
public:
    
    /** number of the port pin that has the bus line */
    static constexpr uint8_t Pin = pin;
    
    /** Rom code of the device or SkipRom */
    using Rom = rom_;

    /** If there is support to decimals or fractions */
    static constexpr bool with_decimal = detail::with_decimal<policies>();

    /** Resolution used by the sensor */
    static constexpr uint8_t resolution = detail::resolution<policies>();

    /** If there is support to internal pullup resistors */
    static constexpr bool internal_pullup = detail::internal_pullup<policies>();

    /** The return type of the method read(). It can be a temperature
        if only the whole number of the temperature is desired or a
        temperature_with_decimal otherwise. */
    using value_type = 
        conditional_t<
            with_decimal,
            temperature_with_decimal<
                conditional_t<
                    resolution >= 11,
                    uint16_t,
                    uint8_t
                >,
                pin, Rom, internal_pullup, resolution
             >,
        temperature<pin, Rom, internal_pullup, resolution>
        >;

    /** Returns the Rom code of the sensor

        If this abstraction was intantiated with SkipRom, then the Rom
        code is read through a command to be sent to the device,
        otherwise, if it was instantiated with a Rom address, then the
        address is returned. Take a look at 'rom.hpp' to see the
        return type.
     */
    static ::ds18b20::rom rom() noexcept {
        if constexpr(has_rom) {
            return {Rom::data};
        } else {
            onewire::init<internal_pullup>(pin);
            onewire::write<internal_pullup>(pin, 0x33); //Read ROM command
            ::ds18b20::rom ret;
            for(uint8_t i{}; i < 8; ++i)
                ret[i] = onewire::read<internal_pullup>(pin);
            return ret;
            // return commands::read_rom<internal_pullup>(pin);
        }
    }

    /** Get the temperature

        This returns a resumable function that initiates a temperature
        conversion and suspends its execution. Take a look at
        'temperature.hpp' to see how to use the returned object.
    */
    static value_type read() noexcept {
        detail::addr_device<internal_pullup, Rom>(pin);
        commands::conversion<internal_pullup>(pin);
        return {};
    }
};

}
