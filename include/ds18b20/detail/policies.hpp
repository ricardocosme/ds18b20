#pragma once

#include "ds18b20/policies.hpp"

namespace ds18b20::detail {

struct initial {};

template<typename Result, typename Policy>
struct accumulate : Result, Policy {};

template<typename Result>
constexpr auto policies_impl(Result res)
{ return res; }

template<typename Result, typename Policy>
constexpr auto policies_impl(Result res, const Policy& p)
{ return accumulate<Result, Policy>{}; }

template<typename Result, typename Policy, typename... Rest>
constexpr auto policies_impl(Result res, const Policy& p, Rest... rest)
{ return policies_impl(accumulate<Result, Policy>{}, rest...); }

template<typename... Policies>
constexpr auto policies(Policies... p)
{ return policies_impl(initial{}, p...); }

template<typename T, typename Enable = void>
struct has_internal_pullup : std::false_type {};

template<typename T>
struct has_internal_pullup<T, std::void_t<decltype(T::internal_pullup)>> : std::true_type {};

template<typename T, typename Enable = void>
struct resolution {
    static constexpr uint8_t value{ds18b20::resolution::_12bits::resolution};
};

template<typename T>
struct resolution<T, std::void_t<decltype(T::resolution)>> {
    static constexpr uint8_t value{T::resolution};
};

template<typename T, typename Enable = void>
struct has_with_decimal : std::false_type {};

template<typename T>
struct has_with_decimal<T, std::void_t<decltype(T::with_decimal)>> : std::true_type {};

template<typename Policies>
constexpr auto with_decimal() { return false; }

}
