#ifndef __TANUKIGB_CPU_INTERNAL_REGISTER_FLAG_OPERATIONS_H__
#define __TANUKIGB_CPU_INTERNAL_REGISTER_FLAG_OPERATIONS_H__

#include <tanukigb/cpu/register_functionoid.h>
#include <tanukigb/utility/concepts.h>
#include <tanukigb/utility/enum_utils.h>

#include <bit>
#include <concepts>

namespace tanukigb {
namespace rfo_internal {
constexpr auto ClearBit = 0;
}  // namespace rfo_internal

template <std::integral T, RegisterFunctionoid<T> Functionoid>
class Register;

// While Flag Operations dont truly require strict_unsigned_integral (We could
// make a version of std::has_single_bit that casts non strictly unsigned values
// to strictly unsigned ones (or at least the non char_X ones) but since many of
// the "bit" members do require it we may as well too (even though the other
// flag operations do not need it).

template <unsigned int flag, std::integral T, RegisterFunctionoid<T> F>
constexpr inline bool IsFlagSet(const Register<T, F>& reg) noexcept {
  static_assert(std::has_single_bit(flag),
                "A Flag is a single bit in the register and therefore must be "
                "a power of 2");
  return (reg & flag) != rfo_internal::ClearBit;
}

template <unsigned int flag, std::integral T, RegisterFunctionoid<T> F>
constexpr inline bool IsFlagClear(const Register<T, F>& reg) noexcept {
  static_assert(std::has_single_bit(flag),
                "A Flag is a single bit in the register and therefore must be "
                "a power of 2");
  return (reg & flag) == rfo_internal::ClearBit;
}

template <unsigned int... flags, std::integral T, RegisterFunctionoid<T> F>
constexpr inline T SetFlags(Register<T, F>& reg) noexcept {
  return reg |= (flags | ...);
}

template <unsigned int... flags, std::integral T, RegisterFunctionoid<T> F>
constexpr inline T ClearFlags(Register<T, F>& reg) noexcept {
  return reg &= ~(flags | ...);
}

template <unsigned int... flags, std::integral T, RegisterFunctionoid<T> F>
constexpr inline T ToggleFlags(Register<T, F>& reg) noexcept {
  return reg ^= (flags | ...);
}

// Since its common to use enums for flags the following are helpers when using a scoped enum's for flags

template <enum_type enum_flag_t, enum_flag_t enum_flag, std::integral T,
          RegisterFunctionoid<T> F>
constexpr inline bool IsFlagSet(const Register<T, F>& reg) noexcept {
  return IsFlagSet<to_unsigned_underlying(enum_flag)>(reg);
}

template <enum_type enum_flag_t, enum_flag_t enum_flag, std::integral T,
          RegisterFunctionoid<T> F>
constexpr inline bool IsFlagClear(const Register<T, F>& reg) noexcept {
  return IsFlagClear<to_unsigned_underlying(enum_flag)>(reg);
}

template <enum_type enum_flag_t, enum_flag_t ...enum_flags, std::integral T,
          RegisterFunctionoid<T> F>
constexpr inline T SetFlags(Register<T, F>& reg) noexcept {
  return reg |= (to_unsigned_underlying(enum_flags) | ...);
}

template <enum_type enum_flag_t, enum_flag_t ...enum_flags, std::integral T,
          RegisterFunctionoid<T> F>
constexpr inline T ClearFlags(Register<T, F>& reg) noexcept {
  return reg &= ~(to_unsigned_underlying(enum_flags) | ...);
}

template <enum_type enum_flag_t, enum_flag_t ...enum_flags, std::integral T,
          RegisterFunctionoid<T> F>
constexpr inline T ToggleFlags(Register<T, F>& reg) noexcept {
  return reg ^= (to_unsigned_underlying(enum_flags) | ...);
}

}  // namespace tanukigb

#endif