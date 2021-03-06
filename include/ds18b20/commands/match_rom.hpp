#pragma once

#include "ds18b20/onewire/init.hpp"
#include "ds18b20/onewire/write.hpp"

namespace ds18b20 { namespace commands {

template<bool InternalPullup, typename Pin>
inline void match_rom(Pin pin, const uint8_t rom[]) noexcept {
    onewire::init<InternalPullup>(pin);
    onewire::write<InternalPullup>(pin, 0x55 /*Match ROM*/);
    for(uint8_t i{}; i < 8; ++i)
        onewire::write<InternalPullup>(pin, rom[i]);
}

}}
