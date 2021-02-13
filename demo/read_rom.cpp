#include <ds18b20/sensor.hpp>

/** This demo shows how to read the Rom value of the chip. 
    
    It's considered that there is only one device connected to the
    bus.
*/

void do_something_with_each_byte(uint8_t b){
}

int main() {
    ds18b20::sensor thermo{avr::io::pb3};
    auto rom = thermo.rom();
    for(auto b : rom)
        do_something_with_each_byte(b);
}
