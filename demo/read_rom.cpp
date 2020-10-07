#include <ds18b20/ds18b20.hpp>
#include <att85/ssd1306/display.hpp>
#include <att85/ssd1306/font/16x32/chars.hpp>
#include <att85/ssd1306/font/8x8/chars.hpp>
using namespace att85::ssd1306;

//This demo shows how to read the Rom value of the chip

int main() {    
    ds18b20::thermo<PB3> termo;
    auto rom = termo.rom();

    display_128x64<> disp;
    disp.clear();
    disp.on();
    disp.out<font::_8x8>(0, 0, rom[0]);
    disp.out<font::_8x8>(0, 26, rom[1]);
    disp.out<font::_8x8>(0, 52, rom[2]);
    disp.out<font::_8x8>(0, 78, rom[3]);
    disp.out<font::_8x8>(2, 0, rom[4]);
    disp.out<font::_8x8>(2, 26, rom[5]);
    disp.out<font::_8x8>(2, 52, rom[6]);
    disp.out<font::_8x8>(2, 78, rom[7]);

    while(true);
}
