#pragma once

namespace ds18b20 {
/** We don't use the c++17 std::void_t because we need it when c++11
 * is used. */
template<typename...> using void_t = void;
}
