#include <ds18b20.hpp>

/** 
   This demo shows how to read the temperature with support to
   fractions.

   It's considered that there is only one device using the bus and it
   has the default resolution of 12bits.
*/

int main() {
    using namespace ds18b20;    
    sensor thermo{avr::io::pb3, skip_rom, with_decimal};
    
    while(true)
        if(auto temp = thermo.async_read()) {
            if(temp.has_value()) {
                auto whole = temp.value();
                auto decimal = temp.decimal();
            }
        }
}
