#pragma once

#include "ds18b20/detail/write.hpp"

namespace ds18b20::detail {

inline void set_resolution(uint8_t pin, resolution::_9bits_t) noexcept
{ detail::write(pin, 0); }
    
inline void set_resolution(uint8_t pin, resolution::_10bits_t) noexcept
{ detail::write(pin, 1); }
    
inline void set_resolution(uint8_t pin, resolution::_11bits_t) noexcept
{ detail::write(pin, 2); }
    
inline void set_resolution(uint8_t pin, resolution::_12bits_t) noexcept
{ detail::write(pin, 3); }

}
