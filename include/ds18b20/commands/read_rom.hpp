#pragma once

#include "ds18b20/onewire/init.hpp"
#include "ds18b20/onewire/read.hpp"
#include "ds18b20/onewire/write.hpp"
#include "ds18b20/rom.hpp"

namespace ds18b20::commands {

template<bool InternalPullup, typename Pin>
inline auto read_rom(Pin pin) noexcept {
    onewire::init<InternalPullup>(pin);
    onewire::write<InternalPullup>(pin, 0x33); //Read ROM command
    ::ds18b20::rom ret;
    for(uint8_t i{}; i < 8; ++i)
        ret[i] = onewire::read<InternalPullup>(pin);
    return ret;
}

}
