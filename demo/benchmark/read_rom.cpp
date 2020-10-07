#include <onewire.h>
#include <avr/io.h>

int main() {    
    onewire_init(PB3);
    onewire_reset(); // 1-Wire reset
    onewire_write(ONEWIRE_READ_ROM);
    uint8_t rom[8];
    for(uint8_t i{}; i < 8; ++i)
        rom[i] = onewire_read();
    
    while(true);
}
