#pragma once

#include "ds18b20/onewire/write.hpp"

namespace ds18b20::commands {

template<bool InternalPullup>
inline void conversion(uint8_t pin) noexcept {
    onewire::write<InternalPullup>(pin, 0x44 /*Conversion*/);
}

}
