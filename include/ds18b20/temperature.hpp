#pragma once

#include "ds18b20/detail/addr_device.hpp"
#include "ds18b20/onewire/read.hpp"
#include "ds18b20/onewire/init.hpp"
#include "ds18b20/onewire/write.hpp"

#include <util/crc16.h>
#include <stdint.h>

namespace ds18b20 {

/** Resumable function that represents a lazy temperature value

   An object 'temperature' is returned by a call to 'thermo::read()'.
   This object is a stackless coroutine that represents the
   temperature value in the future.

   The first step is to convert the temperature and the second and the
   last one is to read the temperature value from the
   memory(scratchpad) of the sensor.

   The conversion process can take a while and if the function is
   resumed while this processing is happening, the function is
   suspended and a value 'false' is returned to inform that the
   coroutine is yet running. When the function is resumed after the
   conversion is over, the temperature or an error is available and
   the value 'true' is returned.
   
   An example using this function inside an event loop:

     auto temp = thermo.read(); //[1]
     while(true) {
       if(temp()) { //[2]
         if(temp.has_value()) //[3]
           do_something(temp.value()); //[4]
       }
       temp = thermo.read(); //[5]
     }
       
     Explanation of the above example:
   
     [1] Each call to 'thermo.read()' returns a coroutine.
       
     [2] The 'temp' object has an operator() that is the same as
     'temp.resume()'. When the coroutine is resumed it can be
     suspended again if the conversion is ongoing, in this case a
     value 'false' is returned to inform that the coroutine is
     running. If the coroutine is finished, the value 'true' is
     returned.

     [3] When the coroutine is finished, the method 'has_value()'
     returns 'true' if there is a valid temperature value or 'false'
     otherwise. The error is achievable when the function reads a
     temperature that can't be validated using CRC.
       
     [4] With a valid temperature in hands the caller calls
     'temp.value()' to obtain the temperature value.

     [5] The steps from 1 to 4 are repeated again calling 'read()' to
     obtain a new coroutine.
 */
template<uint8_t pin,
         typename Rom,
         bool internal_pullup,
         uint8_t resolution>
class temperature {
protected:    
    constexpr static uint8_t unfinished{255}, error{254};
    uint8_t _value{unfinished};
public:
    
    /** Resumes this coroutine 
        precondition: done() == false */
    bool resume() noexcept {
      if(!onewire::read<internal_pullup>(pin)) return false;
      
      detail::addr_device<internal_pullup, Rom>(pin);
      onewire::write<internal_pullup>(pin, 0xBE /*Read from scratchpad*/);

      // check for errors using CRC byte
      uint8_t scratchpad[9];
      uint8_t invalid_crc = 0;
      for(uint8_t i = 0; i < 9; ++i) {
          scratchpad[i] = onewire::read<internal_pullup>(pin);
          invalid_crc = _crc_ibutton_update(invalid_crc, scratchpad[i]);
      }
      
      if(invalid_crc) {
          _value = error;
          return true;
      }
      
      uint8_t whole_lo = (scratchpad[0]& 0xF0) >> 4;
      uint8_t whole_up = (scratchpad[1]& 0x07) << 4;

      _value = static_cast<uint8_t>(whole_up | whole_lo);

      return true;
    }

    /** The same as 'resume()' */
    bool operator()() noexcept
    { return resume(); }

    /** Returns 'true' if this coroutine has finished and 'false'
        otherwise. */
    bool done() const noexcept
    { return _value != unfinished; }

    /** The same as 'done()' */
    operator bool() const noexcept
    { return done(); }

    /** Returns 'true' if this coroutine has finished AND if there is a
        valid temperature value, otherwise 'false' is returned. */
    bool has_value() const noexcept
    { return done() && _value != error; }

    /** Returns the temperature value
        precondition: done() == true */
    uint8_t value() const noexcept
    { return _value; }
};

template<typename Decimal,
         uint8_t pin,
         typename Rom,
         bool internal_pullup,
         uint8_t resolution>
class temperature_with_decimal
    // : public temperature<pin, Rom, internal_pullup, resolution>
{
    constexpr static uint8_t unfinished{255}, error{254};
    uint8_t _value{unfinished};
    Decimal _decimal;
public:
    // using base = temperature<pin, Rom, internal_pullup, resolution>;
    
    /** Resumes this coroutine 
        precondition: done() == false */
    bool resume() noexcept {
      if(!onewire::read<internal_pullup>(pin)) return false;
      
      detail::addr_device<internal_pullup, Rom>(pin);
      onewire::write<internal_pullup>(pin, 0xBE /*Read from scratchpad*/);

      // check for errors using CRC byte
      uint8_t scratchpad[9];
      uint8_t invalid_crc = 0;
      for(uint8_t i = 0; i < 9; ++i) {
          scratchpad[i] = onewire::read<internal_pullup>(pin);
          invalid_crc = _crc_ibutton_update(invalid_crc, scratchpad[i]);
      }
      
      if(invalid_crc) {
          _value = error;
          return true;
      }
      
      uint8_t whole_lo = (scratchpad[0]& 0xF0) >> 4;
      uint8_t whole_up = (scratchpad[1]& 0x07) << 4;

      _value = static_cast<uint8_t>(whole_up | whole_lo);

        if constexpr (resolution == 9) {
            _decimal = (scratchpad[0]& 0x08) ? 5 : 0;
        } else if constexpr (resolution == 10) {
            _decimal = (scratchpad[0]& 0x08) ? 50 : 0;
            _decimal = _decimal + ((scratchpad[0]& 0x04) ? 25 : 0);
        } else if constexpr (resolution == 11) {
            _decimal = (scratchpad[0]& 0x08) ? 500 : 0;
            _decimal = _decimal + ((scratchpad[0]& 0x04) ? 250 : 0);
            _decimal = _decimal + ((scratchpad[0]& 0x02) ? 125 : 0);
        } else if constexpr (resolution == 12) {
            _decimal = (scratchpad[0]& 0x08) ? 5000 : 0;
            _decimal = _decimal + ((scratchpad[0]& 0x04) ? 2500 : 0);
            _decimal = _decimal + ((scratchpad[0]& 0x02) ? 1250 : 0);
            _decimal = _decimal + ((scratchpad[0]& 0x01) ? 625 : 0);
        }
        
      return true;
    }
    
    /** The same as 'resume()' */
    bool operator()() noexcept
    { return resume(); }
    
    Decimal decimal() const noexcept
    { return _decimal; }
    
    /** Returns 'true' if this coroutine has finished and 'false'
        otherwise. */
    bool done() const noexcept
    { return _value != unfinished; }

    /** The same as 'done()' */
    operator bool() const noexcept
    { return done(); }

    /** Returns 'true' if this coroutine has finished AND if there is a
        valid temperature value, otherwise 'false' is returned. */
    bool has_value() const noexcept
    { return done() && _value != error; }

    /** Returns the temperature value
        precondition: done() == true */
    uint8_t value() const noexcept
    { return _value; }
};
    
}
