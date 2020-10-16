#pragma once

#include <ds18b20/type_traits/integral_constant.hpp>
#include <ds18b20/type_traits/is_same.hpp>
#include <ds18b20/type_traits/remove_cv.hpp>

namespace ds18b20 {

template<typename T>
struct is_void : is_same<remove_cv_t<T>, void> {};

}
