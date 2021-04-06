#pragma once

namespace ds18b20 { namespace detail {

template<typename T, T v>
struct integral_constant {
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

}}
