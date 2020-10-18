#include <ds18b20.hpp>

/** 
   This demo shows how to read the temperature using the asynchronous
   call read()

   It's considered that there is only one device using the bus, it has
   the default resolution of 12bits and the user is interested in
   reading only the whole part of the temperature value.
*/

// display_128x64<> disp;
void do_something(uint8_t temp){
}

int main() {
    ds18b20::sensor<PB3> thermo;

    while(true)
        if(auto temp = thermo.read()) {
            if(temp.has_value())
                do_something(temp.value());
        }
}
