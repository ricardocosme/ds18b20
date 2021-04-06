#pragma once

#include "ds18b20/detail/type_traits/enable_if.hpp"
#include "ds18b20/detail/type_traits/is_same.hpp"

namespace ds18b20 { namespace detail {

template<typename Sensor>
typename enable_if<
    !is_same<typename Sensor::rom_t, SkipRom>::value,
    ::ds18b20::rom
>::type rom(Sensor&) noexcept
{ return {Sensor::rom_t::data}; }

template<typename Sensor>
typename enable_if<
    is_same<typename Sensor::rom_t, SkipRom>::value,
    ::ds18b20::rom
>::type rom(Sensor& sensor) noexcept
{ return commands::read_rom(sensor); }

}}
