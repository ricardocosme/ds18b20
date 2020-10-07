#pragma once

#include "ds18b20/detail/reset.hpp"
#include "ds18b20/detail/write.hpp"

namespace ds18b20::resolution {

struct _9bits_t { constexpr static uint8_t value = 9; };
constexpr inline _9bits_t _9bits;

struct _10bits_t { constexpr static uint8_t value = 10; };
constexpr inline _10bits_t _10bits;

struct _11bits_t { constexpr static uint8_t value = 11; };
constexpr inline _11bits_t _11bits;

struct _12bits_t { constexpr static uint8_t value = 12; };
constexpr inline _12bits_t _12bits;

}

#include "ds18b20/detail/resolution.hpp"

namespace ds18b20::resolution {

template<typename Thermo, typename Resolution>
inline void set(const Thermo& t, Resolution res) {
    constexpr auto Pin = Thermo::pin;
    detail::reset(Pin);
    //TODO: I need to set the resolution without loose the values
    //related to the alarm.
    detail::write(Pin, 0x4E /*Write Scratchpad*/);
    detail::write(Pin, 0); // Th
    detail::write(Pin, 0); // Tl
    detail::set_resolution(Pin, res);
}
}
