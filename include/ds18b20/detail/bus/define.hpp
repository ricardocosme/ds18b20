#include <avr/io.h>

#define low(pin) PORTB &= ~(1 << pin);
#define high(pin) PORTB |= (1 << pin);
#define out(pin) DDRB |= (1 << pin);
#define in(pin) DDRB &= ~(1 << pin);
