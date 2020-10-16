#pragma once

#include <ds18b20/type_traits/integral_constant.hpp>

namespace ds18b20 {

template<typename, typename>
struct is_same : false_type {};

template<typename T>
struct is_same<T, T> : true_type {};

}
