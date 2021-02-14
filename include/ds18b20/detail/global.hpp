#pragma once

namespace ds18b20 { namespace detail {

// [C++11/14] Workaround to allow global objects using header only
// sources.
template<typename T>
struct global
{ static constexpr T instance{}; };

template<typename T>
constexpr T global<T>::instance;

}}
