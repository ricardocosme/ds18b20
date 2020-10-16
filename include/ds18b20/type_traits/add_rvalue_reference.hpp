#pragma once

#include <ds18b20/type_traits/integral_constant.hpp>
#include <ds18b20/type_traits/is_reference.hpp>
#include <ds18b20/type_traits/is_void.hpp>

namespace ds18b20 {

template<typename T, bool = !is_void<T>::value && !is_reference<T>::value>
struct add_rvalue_reference;

template<typename T>
struct add_rvalue_reference<T, true> { using type = T&&; };

template<typename T>
struct add_rvalue_reference<T, false> { using type = T; };

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

}
