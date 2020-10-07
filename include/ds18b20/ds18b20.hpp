#pragma once

#include "ds18b20/resolution.hpp"
#include "ds18b20/rom.hpp"
#include "ds18b20/detail/resolution.hpp"
#include "ds18b20/detail/match_rom.hpp"
#include "ds18b20/detail/read.hpp"
#include "ds18b20/detail/reset.hpp"
#include "ds18b20/detail/write.hpp"

#include <att85/type_traits.hpp>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "ds18b20/detail/bus/define.hpp"

namespace ds18b20 {

template<typename Decimal>
struct temperature {
    uint8_t whole;
    Decimal decimal;
};

template<>
struct temperature<void> {
    uint8_t whole;
};

struct WithDecimal {};
struct SkipRom {};

template<uint8_t Pin,
         typename Rom = SkipRom,
         typename WithDecimal_ = void,
         typename Resolution_ = resolution::_9bits_t,
         bool SetResolution = true>
struct thermo {
    static constexpr uint8_t pin = Pin;
    static constexpr bool with_decimal = att85::is_same<WithDecimal_, WithDecimal>::value;
    static constexpr bool has_rom = !att85::is_same<Rom, SkipRom>::value;
    using resolution_t = Resolution_;
    
    using value_type = att85::conditional_t<
        with_decimal,
        temperature<
            att85::conditional_t<
                resolution_t::value >= 11,
                uint16_t,
                uint8_t
            >
        >,
        uint8_t
    >;

    thermo()
    { if constexpr(SetResolution) resolution::set(*this, resolution_t{}); }
    
    ::ds18b20::rom rom() const noexcept {
        if constexpr(has_rom)
            return {Rom::data};
        else {
            detail::reset(Pin);
            detail::write(Pin, 0x33); //Read ROM command
            ::ds18b20::rom ret;
            for(uint8_t i{}; i < 8; ++i)
                ret[i] = detail::read(Pin);
            return ret;
        }
    }

    //TODO: negative temperatures
    value_type read() noexcept {
        if constexpr(has_rom)
            detail::match_rom(Pin, Rom::data);
        else {
            detail::reset(Pin);
            detail::write(Pin, 0xCC /*Skip Rom*/);
        }
        detail::write(Pin, 0x44 /*Conversion*/);
        
        if constexpr(has_rom)
            detail::match_rom(Pin, Rom::data);
        else {
            detail::reset(Pin);
            detail::write(Pin, 0xCC /*Skip Rom*/);
        }
        detail::write(Pin, 0xBE /*Read from scratchpad*/);
        
        uint8_t lo = detail::read(Pin);
        uint8_t hi = detail::read(Pin);
        uint8_t whole_lo = (lo & 0xF0) >> 4;
        uint8_t whole_up = (hi & 0x07) << 4;

        value_type ret = {static_cast<uint8_t>(whole_up | whole_lo)};
        if constexpr (with_decimal) {
            if constexpr (resolution_t::value == 9)
                ret.decimal = (lo & 0x08) ? 5 : 0;
            else if constexpr (resolution_t::value == 10) {
                ret.decimal = (lo & 0x08) ? 50 : 0;
                ret.decimal = ret.decimal + ((lo & 0x04) ? 25 : 0);
            } else if constexpr (resolution_t::value == 11) {
                ret.decimal = (lo & 0x08) ? 500 : 0;
                ret.decimal = ret.decimal + ((lo & 0x04) ? 250 : 0);
                ret.decimal = ret.decimal + ((lo & 0x02) ? 125 : 0);
            } else if constexpr (resolution_t::value == 12) {
                ret.decimal = (lo & 0x08) ? 5000 : 0;
                ret.decimal = ret.decimal + ((lo & 0x04) ? 2500 : 0);
                ret.decimal = ret.decimal + ((lo & 0x02) ? 1250 : 0);
                ret.decimal = ret.decimal + ((lo & 0x01) ? 625 : 0);
            }
        }
        return ret;
    }
};

}

#include "ds18b20/detail/bus/undef.hpp"
