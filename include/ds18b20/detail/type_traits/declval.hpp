#pragma once

#include "add_rvalue_reference.hpp"

namespace ds18b20 { namespace detail {

template <typename T>
constexpr add_rvalue_reference_t<T> declval() noexcept;

}}
