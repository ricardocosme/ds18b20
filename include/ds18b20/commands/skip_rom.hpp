#pragma once

#include "ds18b20/onewire/init.hpp"
#include "ds18b20/onewire/write.hpp"

namespace ds18b20::commands {

template<bool InternalPullup>
inline void skip_rom(uint8_t pin) noexcept {
    onewire::init<InternalPullup>(pin);
    onewire::write<InternalPullup>(pin, 0xCC /*Skip Rom*/);
}

}
