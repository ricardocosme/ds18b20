#pragma once

#include <ds18b20/type_traits/integral_constant.hpp>

namespace ds18b20 {

template<typename T>
struct is_rvalue_reference : false_type {};

template<typename T>
struct is_rvalue_reference<T&&> : true_type {};

}
