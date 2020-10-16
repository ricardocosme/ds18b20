#pragma once

#include <ds18b20/type_traits/add_rvalue_reference.hpp>

namespace ds18b20 {

template <typename T>
constexpr add_rvalue_reference_t<T> declval() noexcept;

}
