#pragma once

#include "ds18b20/onewire/write.hpp"

namespace ds18b20::commands {

template<bool InternalPullup>
inline void copy_scratchpad(uint8_t pin) noexcept {
    onewire::write<InternalPullup>(pin, 0x48 /*Copy Scratchpad*/);
}

}
