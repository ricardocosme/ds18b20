#pragma once

#include "ds18b20/onewire/init.hpp"
#include "ds18b20/onewire/write.hpp"

namespace ds18b20 { namespace commands {

template<bool InternalPullup, typename Pin>
inline void skip_rom(Pin pin) noexcept {
    onewire::init<InternalPullup>(pin);
    onewire::write<InternalPullup>(pin, 0xCC /*Skip Rom*/);
}

}}
