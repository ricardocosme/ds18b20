#pragma once

#include "integral_constant.hpp"
#include "is_reference.hpp"
#include "is_void.hpp"

namespace ds18b20 { namespace detail {

template<typename T, bool = !is_void<T>::value && !is_reference<T>::value>
struct add_rvalue_reference;

template<typename T>
struct add_rvalue_reference<T, true> { using type = T&&; };

template<typename T>
struct add_rvalue_reference<T, false> { using type = T; };

template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

}}
