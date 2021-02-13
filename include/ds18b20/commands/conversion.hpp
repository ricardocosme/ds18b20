#pragma once

#include "ds18b20/onewire/write.hpp"

namespace ds18b20::commands {

template<bool InternalPullup, typename Pin>
inline void conversion(Pin pin) noexcept {
    onewire::write<InternalPullup>(pin, 0x44 /*Conversion*/);
}

}
