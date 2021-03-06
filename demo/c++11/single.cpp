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
    
    auto thermo = make_sensor(avr::io::pb3, Rom<40, 251, 43, 31, 5, 0, 0, 139>{});

    while(true)
        if(auto temp = thermo.async_read()) {
            if(temp.has_value())
                do_something(temp.value());
        }
}
