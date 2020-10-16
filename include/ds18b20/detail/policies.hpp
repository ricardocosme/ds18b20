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

template<typename Policies>
constexpr auto internal_pullup() requires (Policies::internal_pullup)
{ return true; }

template<typename Policies>
constexpr auto internal_pullup() { return false; }

template<typename Policies>
constexpr auto resolution() requires (!!Policies::resolution)
{ return Policies::resolution; }

template<typename Policies>
constexpr auto resolution() { return resolution::_12bits::resolution; }

template<typename Policies>
constexpr auto with_decimal() requires (Policies::with_decimal)
{ return true; }

template<typename Policies>
constexpr auto with_decimal() { return false; }

}
