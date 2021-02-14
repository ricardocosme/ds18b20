#pragma once

#include <type_traits>

namespace ds18b20 { namespace detail {

template<typename Sensor>
typename std::enable_if<
    !std::is_same<typename Sensor::rom_t, SkipRom>::value,
    ::ds18b20::rom
>::type rom(Sensor&) noexcept
{ return {Sensor::rom_t::data}; }

template<typename Sensor>
typename std::enable_if<
    std::is_same<typename Sensor::rom_t, SkipRom>::value,
    ::ds18b20::rom
>::type rom(Sensor& sensor) noexcept
{ return commands::read_rom(sensor); }

}}
