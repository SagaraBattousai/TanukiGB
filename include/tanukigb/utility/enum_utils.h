#ifndef __TANUKIGB_UTILITY_ENUM_UTILS_H__
#define __TANUKIGB_UTILITY_ENUM_UTILS_H__

#include <type_traits>

#include <tanukigb/utility/concepts.h>
#include <tanukigb/utility/integral.h>

namespace tanukigb {

template <typename E>
concept enum_type = std::is_enum_v<E>;

template <enum_type E>
constexpr inline std::underlying_type_t<E> to_underlying(E value) {
  return static_cast<std::underlying_type_t<E>>(value);
}

// If the underlying type is already unsigned (actually in this case strictly
// unsigned) then equivilent to calling to_underlying.
template <enum_type E>
constexpr inline auto to_unsigned_underlying(E value) {
  if constexpr (strict_unsigned_integral<std::underlying_type_t<E>>) {
    return to_underlying(value);
  } else {
    return unsigned_cast(to_underlying(value));
  }
}
}  // namespace tanukigb

#endif