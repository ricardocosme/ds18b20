#include <ds18b20/sensor.hpp>

/** This demo shows how to read the Rom value of the chip. */

void do_something_with_each_byte(uint8_t){}

int main() {
    using thermo = ds18b20::sensor<PB3>;
    auto rom = thermo::rom();
    for(auto b : rom)
        do_something_with_each_byte(b);
}
