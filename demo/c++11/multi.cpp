#include <ds18b20.hpp>
/** 
   This demo shows how to read the temperature of two devices
   connected to the same bus.

   It's considered that the device has the default resolution of
   12bits and the user is interested in reading only the whole part of
   the temperature value.
*/
void do_something_inside(uint8_t temp){
}
void do_something_outside(uint8_t temp){
}
int main() {
    using namespace ds18b20;
    auto inside = make_sensor(avr::io::pb3, Rom<40, 251, 43, 31, 5, 0, 0, 139>{});
    auto outside = make_sensor(avr::io::pb3, Rom<40, 198, 8, 141, 5, 0, 0, 124>{});

    while(true) {
        if(auto temp = inside.async_read())
            if(temp.has_value())
                do_something_inside(temp.value());
        if(auto temp = outside.async_read())
            if(temp.has_value())
                do_something_outside(temp.value());
    }
}
