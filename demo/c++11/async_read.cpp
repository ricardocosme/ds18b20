#include <ds18b20.hpp>

/** 
   This demo shows how to read the temperature using a
   non-blocking(asynchronous) approach.

   It's considered that there is only one device using the bus, it has
   the default resolution of 12bits and the user is interested in
   reading only the whole part of the temperature value.
*/


int main() {
    auto thermo = ds18b20::make_sensor(avr::io::pb4);

    while(true) 
        if(auto temp = thermo.async_read()) {
            if(temp.has_value())
                auto v = temp.value();
        }
}
