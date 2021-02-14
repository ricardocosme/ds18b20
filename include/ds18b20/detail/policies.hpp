#pragma once

#include "ds18b20/policies.hpp"
#include "ds18b20/detail/macros.hpp"
#include "ds18b20/detail/void_t.hpp"

#include <type_traits>

namespace ds18b20 { namespace detail {

struct initial {};

template<typename Result, typename Policy>
struct accumulate : Result, Policy {};

template<typename Result>
constexpr auto policies_impl(Result res)
DS18B20_DECLTYPE_AUTO_RETURN
( res )

template<typename Result, typename Policy>
constexpr auto policies_impl(Result res, const Policy& p)
DS18B20_DECLTYPE_AUTO_RETURN
( accumulate<Result, Policy>{} )

template<typename Result, typename Policy, typename... Rest>
constexpr auto policies_impl(Result res, const Policy& p, Rest... rest)
DS18B20_DECLTYPE_AUTO_RETURN
( policies_impl(accumulate<Result, Policy>{}, rest...) )

template<typename... Policies>
constexpr auto policies(Policies... p)
DS18B20_DECLTYPE_AUTO_RETURN
( policies_impl(initial{}, p...) )

template<typename T, typename Enable = void>
struct has_internal_pullup : std::false_type {};

template<typename T>
struct has_internal_pullup<T, void_t<decltype(T::internal_pullup)>> : std::true_type {};

template<typename T, typename Enable = void>
struct resolution {
    static constexpr uint8_t value{ds18b20::resolution::_12bits_t::resolution};
};

template<typename T>
struct resolution<T, void_t<decltype(T::resolution)>> {
    static constexpr uint8_t value{T::resolution};
};

template<typename T, typename Enable = void>
struct has_with_decimal : std::false_type {};

template<typename T>
struct has_with_decimal<T, void_t<decltype(T::with_decimal)>> : std::true_type {};

}}
