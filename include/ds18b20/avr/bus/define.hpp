#include <avr/io.h>

#define low(pin) PORTB = PORTB & ~(1 << pin);
#define high(pin) PORTB = PORTB | (1 << pin);
#define out(pin) DDRB = DDRB | (1 << pin);
#define in(pin) DDRB = DDRB & ~(1 << pin);
