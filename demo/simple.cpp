#include <ds18b20.hpp>

/** 
   This demo shows how to read the temperature using the asynchronous
   call async_read()

   It's considered that there is only one device using the bus, it has
   the default resolution of 12bits and the user is interested in
   reading only the whole part of the temperature value.
*/


void do_something(uint8_t temp){}

int main() {
    ds18b20::sensor thermo{avr::io::pb4};

    while(true) 
        if(auto temp = thermo.async_read()) {
            if(temp.has_value())
                do_something(temp.value());
        }
}
