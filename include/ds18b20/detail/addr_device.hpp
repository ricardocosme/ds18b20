#pragma once

#include "ds18b20/commands/match_rom.hpp"
#include "ds18b20/commands/skip_rom.hpp"
#include "ds18b20/detail/type_traits/is_same.hpp"
#include "ds18b20/rom.hpp"

namespace ds18b20 { namespace detail {

template<bool InternalPullup, typename Rom, typename Pin>
inline void addr_device(Pin pin, true_type) noexcept {
    commands::skip_rom<InternalPullup>(pin);
}

template<bool InternalPullup, typename Rom, typename Pin>
inline void addr_device(Pin pin, false_type) noexcept {
    commands::match_rom<InternalPullup>(pin, Rom::data);
}

template<bool InternalPullup, typename Rom, typename Pin>
inline void addr_device(Pin pin) noexcept {
    addr_device<InternalPullup, Rom>(pin, is_same<Rom, SkipRom>{});
}

}}//namespace ds18b20::detail
