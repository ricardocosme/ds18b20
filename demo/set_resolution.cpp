#include <ds18b20/resolution.hpp>
#include <ds18b20/sensor.hpp>

/**
  This demo shows how to setup the sensor with an especific resolution.
*/

using namespace ds18b20;

int main() {
    using thermo = sensor<PB3, SkipRom, resolution::_9bits>;

    //We can pass 'false' if we don't want to save this configuration
    //in the EEPROM. Take a look at 'resolution.hpp' to know how to
    //use this function.
    resolution::set<thermo>();
}
