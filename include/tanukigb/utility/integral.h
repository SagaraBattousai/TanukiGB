#ifndef __TANUKIGB_UTILITY_INTEGRAL_H__
#define __TANUKIGB_UTILITY_INTEGRAL_H__

#include <bit>
#include <concepts>
#include <type_traits>

namespace tanukigb {

template <std::unsigned_integral T>
constexpr auto signed_cast(T value) {
  return std::bit_cast<std::make_signed_t<T>>(value);
}

}  // namespace tanukigb

#endif