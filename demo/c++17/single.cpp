#include <ds18b20.hpp>

/** 
   This demo shows how to read the temperature of a specific device.

   It's considered that the device has the default resolution of
   12bits and the user is interested in reading only the whole part of
   the temperature value.
*/
void do_something(uint8_t temp){
}

int main() {
    using namespace ds18b20;
    
    sensor thermo{avr::io::pb3, Rom<40, 129, 145, 19, 10, 0, 0, 99>{}};

    while(true)
        if(auto temp = thermo.async_read()) {
            if(temp.has_value())
                do_something(temp.value());
        }
}
