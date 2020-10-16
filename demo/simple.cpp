#include <ds18b20.hpp>

/** 
   This demo shows how to read the temperature with a simple setup of
   ds18b20 sensor.

   It's considered that there is only one device using the bus and the
   device has the default resolution of 12bits and the user is
   interested in reading only the whole part of the temperature
   value.
*/

void do_something(uint8_t){}

int main() {
    using thermo = ds18b20::sensor<PB3>;

    auto co_temp = thermo::read();
    while(true) {
        if(co_temp()) {
            if(co_temp.has_value())
                do_something(co_temp.value());
            co_temp = thermo::read();
        }
    }
}
