#pragma once

#include "ds18b20/detail/global.hpp"

#include <stdint.h>

namespace ds18b20 {

struct SkipRom {};
#if cplusplus >= 201703L
inline constexpr SkipRom skip_rom;
#else
namespace {
constexpr auto& skip_rom{detail::global<SkipRom>::instance};
}//anonymous namespace
#endif

template<uint8_t B0, uint8_t B1, uint8_t B2, uint8_t B3,
         uint8_t B4, uint8_t B5, uint8_t B6, uint8_t B7>
struct Rom {
    static uint8_t data[];
};

template<uint8_t B0, uint8_t B1, uint8_t B2, uint8_t B3,
         uint8_t B4, uint8_t B5, uint8_t B6, uint8_t B7>
uint8_t Rom<B0,B1,B2,B3,B4,B5,B6,B7>::data[] = {B0,B1,B2,B3,B4,B5,B6,B7};

class rom {
    uint8_t _data[8];
public:    
    using iterator = uint8_t*;
    using const_iterator = const uint8_t*;

    // constexpr
    rom() = default;
    
    // constexpr
    rom(const uint8_t r[8]) {
        for(uint8_t i{}; i < 8; ++i)
            _data[i] = r[i];
    }
    
    iterator begin() noexcept
    { return _data; }
    
    const_iterator begin() const noexcept
    { return _data; }
    
    const_iterator cbegin() const noexcept
    { return begin(); }
    
    iterator end() noexcept
    { return _data + 8; }
    
    const_iterator end() const noexcept
    { return _data + 8; }
    
    const_iterator cend() const noexcept
    { return end(); }

    uint8_t& operator[](uint8_t i) noexcept
    { return _data[i]; }

    const uint8_t& operator[](uint8_t i) const noexcept
    { return _data[i]; }
    
    uint8_t* data() noexcept
    { return _data; }
    
    const uint8_t* data() const noexcept
    { return _data; }
};

}
