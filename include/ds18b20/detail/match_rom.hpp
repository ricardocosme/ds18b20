#pragma once

#include "ds18b20/detail/reset.hpp"
#include "ds18b20/detail/write.hpp"
#include "ds18b20/rom.hpp"

#include "ds18b20/detail/bus/define.hpp"

namespace ds18b20::detail {

inline void match_rom(uint8_t pin, const rom& r) {
    reset(pin);
    write(pin, 0x55 /*Match ROM*/);
    for(auto b : r)
        write(pin, b);
}
inline void match_rom(uint8_t pin, const uint8_t r[]) {
    reset(pin);
    write(pin, 0x55 /*Match ROM*/);
    for(uint8_t i{}; i < 8; ++i)
        write(pin, r[i]);
}

}//namespace ds18b20::detail

#include "ds18b20/detail/bus/undef.hpp"
