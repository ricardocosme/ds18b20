#pragma once

namespace ds18b20 { namespace detail {

template<bool, typename T1, typename>
struct conditional
{ using type = T1; };

template<typename T1, typename T2>
struct conditional<false, T1, T2>
{ using type = T2; };

template<bool B, typename T1, typename T2>
using conditional_t = typename conditional<B, T1, T2>::type;

}}
