#pragma once

#include "ds18b20/commands/conversion.hpp"
#include "ds18b20/commands/read_scratchpad.hpp"
#include "ds18b20/detail/addr_device.hpp"
#include "ds18b20/detail/read_scratchpad.hpp"
#include "ds18b20/onewire/read.hpp"
#include "ds18b20/optional_temperature.hpp"

namespace ds18b20 { namespace detail {

template<bool internal_pullup, typename Rom, typename Pin>
inline void start_conversion(Pin pin) noexcept {
    detail::addr_device<internal_pullup, Rom>(pin);
    commands::conversion<internal_pullup>(pin);
}

template<typename Ret, typename Sensor>
inline Ret read_scratchpad(Sensor& sensor, std::true_type) noexcept {
    return detail::read_scratchpad_with_decimal<
        Sensor::internal_pullup, Sensor::resolution,
        typename Sensor::value_type::value_type>(sensor.pin);
}

template<typename Ret, typename Sensor>
inline Ret read_scratchpad(Sensor& sensor, std::false_type) noexcept {
    return {detail::read_scratchpad<Sensor::internal_pullup>(sensor.pin)};
}

template<typename Ret, typename Sensor>
inline Ret read_scratchpad(Sensor& sensor) noexcept {
    detail::addr_device<Sensor::internal_pullup, typename Sensor::rom_t>(sensor.pin);
    commands::read_scratchpad<Sensor::internal_pullup>(sensor.pin);
    return read_scratchpad<Ret>(
        sensor, std::integral_constant<bool, Sensor::with_decimal>{});
}

}}
