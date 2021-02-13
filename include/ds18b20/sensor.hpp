#pragma once

#include "ds18b20/commands/conversion.hpp"
#include "ds18b20/commands/read_rom.hpp"
#include "ds18b20/commands/read_scratchpad.hpp"
#include "ds18b20/detail/addr_device.hpp"
#include "ds18b20/detail/policies.hpp"
#include "ds18b20/detail/read_scratchpad.hpp"
#include "ds18b20/detail/read.hpp"
#include "ds18b20/lazy_temperature.hpp"
#include "ds18b20/onewire/init.hpp"
#include "ds18b20/onewire/write.hpp"
#include "ds18b20/rom.hpp"
#include <avr/io.hpp>
#include <type_traits>
#include <stdint.h>

namespace ds18b20 {

/**
   Represents the sensor DS18B20

   pin: port pin that has the bus line. It should be a model of the
        concept avr::io::Pin.
   rom_: Rom address of the sensor or SkipRom. Default is
         SkipRom. Take a look at 'rom.hpp' to know more.
   Policies: policies to optimize or enable some features. Take a look
             at 'policies.hpp' to know more.

   Examples:

     1. Sensor with the bus line(data Input/Output [DQ]) connected to
        the pin avr::io::pb3 using SkipRom:

       using thermo = sensor<avr::io::pb3>;

     2. Sensor that has the Rom code {40, 251, 43, 31, 5, 0, 0, 139}:

       using thermo = sensor<avr::io::pb3, Rom<40, 251, 43, 31, 5, 0, 0, 139> >;

     3. Sensor configured with 9bits of resolution:

       using thermo = sensor<
         avr::io::pb3, 
         Rom<40, 251, 43, 31, 5, 0, 0, 139>,
         resolution::_9bits_t>;

     4. Sensor configured with 10bits of resolution and decimal values enabled:

       using thermo = sensor<
         avr::io::pb3, 
         Rom<40, 251, 43, 31, 5, 0, 0, 139>,
         resolution::_10bits_t,
         WithDecimal>;

     5. Sensor using the internal pullup resistors from the MCU:

       using thermo = sensor<
         avr::io::pb3, 
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

template<typename Pin,
         typename rom_ = SkipRom,
         typename... Policies>
class sensor {
    using policies = decltype(detail::policies(std::declval<Policies>()...));
    static constexpr bool has_rom = !std::is_same<rom_, SkipRom>::value;
    uint8_t _state{0};
public:
    Pin pin;

    using pin_t = Pin;
    
    /** Rom code of the device or SkipRom */
    using Rom = rom_;

    /** If there is support to decimals or fractions */
    static constexpr bool with_decimal = detail::with_decimal<policies>();

    /** Resolution used by the sensor */
    static constexpr uint8_t resolution = detail::resolution<policies>();

    /** If there is support to internal pullup resistors */
    static constexpr bool internal_pullup = detail::internal_pullup<policies>();

    /** The return type of the method read(). It can be a lazy_temperature
        if only the whole number of the temperature is desired or a
        lazy_temperature_with_decimal otherwise. */
    using value_type = 
        std::conditional_t<
            with_decimal,
            lazy_temperature_with_decimal<
                std::conditional_t<
                    resolution >= 11,
                    FP<uint16_t>,
                    FP<uint8_t>
                >
             >,
        lazy_temperature<uint8_t>
        >;

    sensor(Pin ppin) noexcept : pin(ppin) {}
    
    /** Returns the Rom code of the sensor

        If sensor was instantiated with SkipRom, then the Rom code is
        read through a command to be sent to the device, otherwise, if
        it was instantiated with a Rom address, then the address is
        returned. Take a look at 'rom.hpp' to know more about the
        return type.
     */
    ::ds18b20::rom rom() noexcept {
        if constexpr(has_rom) return {Rom::data};
        else return commands::read_rom<internal_pullup>(pin);
    }

    /** Asynchronous function to read the temperature

        This is a stackless coroutine that returns a lazy temperature
        value. 

        The first step is to convert the temperature, the second is to
        check if the temperature value is available, and the third and
        the last one is to read the temperature value from the
        memory(scratchpad) of the sensor.

        The conversion process can take a while and if this function
        is resumed while this processing is happening, the function is
        suspended and am unfinished lazy value is returned to inform
        that the coroutine is yet running, which means that
        'lazy_value.done() == false'. When the function is resumed
        after the conversion is over, a lazy value is resturned with
        the temperature or an error.
        
        An example using this function inside an event loop:

        while(true) //event loop
          if(auto temp = thermo.read()) { //[1]
            if(temp.has_value()) //[2]
              do_something(temp.value()); //[3]
          }
       
        Explanation of the above example:
   
        [1] The first call to 'thermo.read()' starts the conversion
        process. When this function is resumed in the next iteration
        of the event loop, which means another call to
        'thermo.read()', the function can returns a lazy value
        representing an unfinished execution, which means that 'temp
        == false', or, it can rerturns a lazy value with the
        temperature value or an error.
       
        [2] When the coroutine is over, the lazy value that is
        returned may contain a valid temperature value or an error.

        [3] The temperature value is safely obtained from the lazy
        temperature value.
     */
    value_type async_read() noexcept {
        switch(_state) {
        case 0: {
            detail::start_conversion<internal_pullup, Rom>(pin);
            _state = 1;
            return {};
        }
        case 1: {
            while(!onewire::read_bit<internal_pullup>(pin)) {
                _state = 2;
                return {};
            case 2: { }
            }
        }
        default: {
            _state = 0;
            return detail::read_scratchpad<value_type>(*this);
        }
        }
        return {};
    }
    
    optional_temperature read() noexcept {
        detail::start_conversion<internal_pullup, Rom>(pin);
        while(!onewire::read_bit<internal_pullup>(pin));
        return detail::read_scratchpad<optional_temperature>(*this);
    }
};

}

