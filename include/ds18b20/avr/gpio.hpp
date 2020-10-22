#pragma once

#include <avr/io.h>

[[gnu::always_inline]]
inline void low(uint8_t pin)
{ PORTB = PORTB & ~(1 << pin); }

[[gnu::always_inline]]
inline void high(uint8_t pin)
{ PORTB = PORTB | (1 << pin); }

[[gnu::always_inline]]
inline void out(uint8_t pin)
{ DDRB = DDRB | (1 << pin); }

[[gnu::always_inline]]
inline void in(uint8_t pin)
{ DDRB = DDRB & ~(1 << pin); }

