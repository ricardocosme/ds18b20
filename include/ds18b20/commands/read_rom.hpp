#pragma once

#include "ds18b20/onewire/init.hpp"
#include "ds18b20/onewire/read.hpp"
#include "ds18b20/onewire/write.hpp"
#include "ds18b20/rom.hpp"
#include <util/atomic.h>

namespace ds18b20 { namespace commands {

template<typename Sensor>
inline ::ds18b20::rom read_rom(const Sensor& sensor) noexcept {
    ::ds18b20::rom ret;
    using namespace onewire;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        init<Sensor::internal_pullup>(sensor.pin);
        write<Sensor::internal_pullup>(sensor.pin, 0x33); //Read ROM command
        for(uint8_t i{}; i < 8; ++i)
            ret[i] = read<Sensor::internal_pullup>(sensor.pin);
    }
    return ret;
}

}}
