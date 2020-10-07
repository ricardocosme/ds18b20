#include <ds18b20/ds18b20.hpp>
#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/16x32/chars.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85::ssd1306;
using namespace ds18b20;

/* This demo shows how to read the temperature with a simple setup of
   ds18b20 sensor.

   It's considered that there is only one device using the bus and the
   device has the default resolution of 12bits and the user is
   interested in reading only the whole part of the temperature
   value.
*/

int main() {
    display_128x64<> disp;
    disp.clear();
    disp.on();
    
    thermo<PB3> termo;
    
    while(true) {
        _delay_ms(1000);
        disp.out<font::_16x32>(0, 0, termo.read());
    }
}
