#pragma once

#include <ds18b20/type_traits/integral_constant.hpp>
#include <ds18b20/type_traits/is_destructible.hpp>

namespace ds18b20 {

//Only for avr-gcc
template<typename T>
struct is_trivially_destructible
    : integral_constant<bool, is_destructible<T>::value
                        && __has_trivial_destructor(T)>
{};

}
