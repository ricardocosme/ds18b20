#include <ds18b20.hpp>

/** 
   This demo shows how to read the temperature using a synchronous
   approach calling the method read().

   It's considered that there is only one device using the bus, it has
   the default resolution of 12bits and the user is interested in
   reading only the whole part of the temperature value.
*/

inline void do_something(uint8_t temp){}

int main() {
    ds18b20::sensor<avr::io::Pb3> thermo{avr::io::pb3};

    while(true)
        if(auto temp = thermo.read())
            do_something(temp.value());
}

