#include <ds18b20/ds18b20.hpp>

#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/16x32/chars.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>

using namespace att85::ssd1306;
using namespace ds18b20;

int main() {
    display_128x64<> disp;
    disp.clear();
    disp.on();
    
    thermo<
        PB3,
        Rom<40, 251, 43, 31, 5, 0, 0, 139>,
        WithDecimal> termo;
    
    while(true) {
        _delay_ms(100);
        auto temp = termo.read();
        disp.out<font::_16x32>(0, 0, temp.whole);
        disp.out<font::_8x8>(3, 36, temp.decimal);
    }
}
