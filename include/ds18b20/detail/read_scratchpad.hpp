#pragma once

#include "ds18b20/onewire/read.hpp"

#include <stdint.h>
#include <util/crc16.h>

namespace ds18b20 { namespace detail {

template<bool InternalPullup, typename Pin>
inline uint8_t read_scratchpad(Pin pin) noexcept {
    uint8_t scratchpad[9];
    uint8_t invalid_crc = 0;
    for(uint8_t i = 0; i < 9; ++i) {
        scratchpad[i] = onewire::read<InternalPullup>(pin);
        invalid_crc = _crc_ibutton_update(invalid_crc, scratchpad[i]);
    }
                     
    if(invalid_crc)
        return 254;
    
    uint8_t whole_lo = (scratchpad[0]& 0xF0) >> 4;
    uint8_t whole_up = (scratchpad[1]& 0x07) << 4;
    return static_cast<uint8_t>(whole_up | whole_lo);
}

struct with_decimal_t {
    uint8_t whole;
    uint8_t decimal;
};

template<bool InternalPullup, uint8_t resolution, typename Ret, typename Pin>
inline Ret read_scratchpad_with_decimal(Pin pin) noexcept {
    uint8_t scratchpad[9];
    uint8_t invalid_crc = 0;
    for(uint8_t i = 0; i < 9; ++i) {
        scratchpad[i] = onewire::read<InternalPullup>(pin);
        invalid_crc = _crc_ibutton_update(invalid_crc, scratchpad[i]);
    }
                     
    if(invalid_crc)
        return {254};
    
    uint8_t whole_lo = (scratchpad[0]& 0xF0) >> 4;
    uint8_t whole_up = (scratchpad[1]& 0x07) << 4;

    Ret ret;
    ret.whole = static_cast<uint8_t>(whole_up | whole_lo);
    
    if (resolution == 9) {
        ret.decimal = (scratchpad[0]& 0x08) ? 5 : 0;
    } else if (resolution == 10) {
        ret.decimal = (scratchpad[0]& 0x08) ? 50 : 0;
        ret.decimal = ret.decimal + ((scratchpad[0]& 0x04) ? 25 : 0);
    } else if (resolution == 11) {
        ret.decimal = (scratchpad[0]& 0x08) ? 500 : 0;
        ret.decimal = ret.decimal + ((scratchpad[0]& 0x04) ? 250 : 0);
        ret.decimal = ret.decimal + ((scratchpad[0]& 0x02) ? 125 : 0);
    } else if (resolution == 12) {
        ret.decimal = (scratchpad[0]& 0x08) ? 5000 : 0;
        ret.decimal = ret.decimal + ((scratchpad[0]& 0x04) ? 2500 : 0);
        ret.decimal = ret.decimal + ((scratchpad[0]& 0x02) ? 1250 : 0);
        ret.decimal = ret.decimal + ((scratchpad[0]& 0x01) ? 625 : 0);
    }

    return ret;
}

}}
