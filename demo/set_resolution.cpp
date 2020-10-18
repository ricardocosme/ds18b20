#include <ds18b20.hpp>

/**
  This demo shows how to setup the sensor with an especific
  resolution.
*/

using namespace ds18b20;

int main() {
    sensor<PB3, SkipRom, resolution::_12bits> thermo;

    /** We can pass 'false' if we don't want to save this configuration
        in the EEPROM. Take a look at 'resolution.hpp' to know how to
        use this function.
    */
    resolution::set(thermo);
}
