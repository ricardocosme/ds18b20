#include <ds18b20.hpp>

/**
  This demo shows how to setup the sensor with a specific
  resolution.
*/

using namespace ds18b20;

int main() {
    auto thermo = make_sensor(avr::io::pb3, skip_rom, resolution::_12bits);

    /** We can pass 'false' if we don't want to save this configuration
        in the EEPROM. Take a look at 'resolution.hpp' to know how to
        use this function.
    */
    resolution::set(thermo);
}
