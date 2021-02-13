#pragma once

#include "ds18b20/onewire/write.hpp"

namespace ds18b20::commands {

template<bool InternalPullup, typename Pin>
inline void read_scratchpad(Pin pin) noexcept
{
    onewire::write<InternalPullup>(pin, 0xBE /*Read from scratchpad*/);
}

}
