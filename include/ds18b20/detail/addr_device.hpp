#pragma once

#include "ds18b20/commands/match_rom.hpp"
#include "ds18b20/commands/skip_rom.hpp"
#include "ds18b20/rom.hpp"
#include "ds18b20/type_traits.hpp"

namespace ds18b20::detail {

template<bool InternalPullup, typename Rom>
inline void addr_device(uint8_t pin) noexcept {
    if constexpr(!is_same<Rom, SkipRom>::value)
        commands::match_rom<InternalPullup>(pin, Rom::data);
    else
        commands::skip_rom<InternalPullup>(pin);
}

}//namespace ds18b20::detail
