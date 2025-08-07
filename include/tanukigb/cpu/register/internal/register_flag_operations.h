#ifndef __TANUKIGB_CPU_REGISTER_INTERNAL_REGISTER_FLAG_OPERATIONS_H__
#define __TANUKIGB_CPU_REGISTER_INTERNAL_REGISTER_FLAG_OPERATIONS_H__

#include <tanukigb/cpu/register/register_type_traits.h>
#include <tanukigb/utility/concepts.h>
#include <tanukigb/utility/enum_utils.h>

#include <bit>
#include <concepts>

namespace tanukigb {
namespace rfo_internal {
constexpr auto ClearBit = 0;
}  // namespace rfo_internal

template <unsigned int flag, RegisterType Register>
constexpr inline bool IsFlagSet(const Register& reg) noexcept {
  static_assert(std::has_single_bit(flag),
                "A Flag is a single bit in the register and therefore must be "
                "a power of 2");
  return (reg & flag) != rfo_internal::ClearBit;
}

template <unsigned int flag, RegisterType Register>
constexpr inline bool IsFlagClear(const Register& reg) noexcept {
  return !IsFlagSet<flag>(reg);
}

template <unsigned int... flags, RegisterType Register>
constexpr inline register_value_type<Register> SetFlags(
    Register& reg) noexcept {
  return reg |= (flags | ...);
}

template <unsigned int... flags, RegisterType Register>
constexpr inline register_value_type<Register> ClearFlags(
    Register& reg) noexcept {
  return reg &= ~(flags | ...);
}

template <unsigned int... flags, RegisterType Register>
constexpr inline register_value_type<Register> ToggleFlags(
    Register& reg) noexcept {
  return reg ^= (flags | ...);
}

// Since its common to use enums for flags the following are helpers when using
// a scoped enum's for flags

template <enum_type enum_flag_t, enum_flag_t enum_flag, RegisterType Register>
constexpr inline bool IsFlagSet(const Register& reg) noexcept {
  return IsFlagSet<to_unsigned_underlying(enum_flag)>(reg);
}

template <enum_type enum_flag_t, enum_flag_t enum_flag, RegisterType Register>
constexpr inline bool IsFlagClear(const Register& reg) noexcept {
  return IsFlagClear<to_unsigned_underlying(enum_flag)>(reg);
}

template <enum_type enum_flag_t, enum_flag_t... enum_flags,
          RegisterType Register>
constexpr inline register_value_type<Register> SetFlags(
    Register& reg) noexcept {
  return reg |= (to_unsigned_underlying(enum_flags) | ...);
}

template <enum_type enum_flag_t, enum_flag_t... enum_flags,
          RegisterType Register>
constexpr inline register_value_type<Register> ClearFlags(
    Register& reg) noexcept {
  return reg &= ~(to_unsigned_underlying(enum_flags) | ...);
}

template <enum_type enum_flag_t, enum_flag_t... enum_flags,
          RegisterType Register>
constexpr inline register_value_type<Register> ToggleFlags(
    Register& reg) noexcept {
  return reg ^= (to_unsigned_underlying(enum_flags) | ...);
}

}  // namespace tanukigb

#endif