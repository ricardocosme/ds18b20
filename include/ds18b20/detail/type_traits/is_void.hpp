#pragma once

#include "integral_constant.hpp"
#include "is_same.hpp"
#include "remove_cv.hpp"

namespace ds18b20 { namespace detail {

template<typename T>
struct is_void : is_same<remove_cv_t<T>, void> {};

}}
