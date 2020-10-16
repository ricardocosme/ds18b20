#pragma once

#include "ds18b20/onewire/write.hpp"

namespace ds18b20::commands {

template<bool InternalPullup>
inline void write_scratchpad(
    uint8_t pin,
    uint8_t resolution,
    uint8_t th = 125,
    uint8_t tl = 0) noexcept
{
    onewire::write<InternalPullup>(pin, 0x4E /*Write Scratchpad*/);
    onewire::write<InternalPullup>(pin, th); // Th
    onewire::write<InternalPullup>(pin, tl); // Tl
    onewire::write<InternalPullup>(pin, resolution);
}

}
