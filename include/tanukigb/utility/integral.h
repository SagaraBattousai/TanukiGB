#ifndef __TANUKIGB_UTILITY_INTEGRAL_H__
#define __TANUKIGB_UTILITY_INTEGRAL_H__

#include <bit>
#include <concepts>
#include <type_traits>

namespace tanukigb {

template <std::unsigned_integral T>
constexpr std::make_signed_t<T> signed_cast(T value) {
  return std::bit_cast<std::make_signed_t<T>>(value);
}

template <std::signed_integral T>
constexpr std::make_unsigned_t<T> unsigned_cast(T value) {
  return std::bit_cast<std::make_unsigned_t<T>>(value);
}

}  // namespace tanukigb

#endif