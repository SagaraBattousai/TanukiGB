#ifndef __TANUKIGB_CPU_REGISTER_REGISTER_OPS_H__
#define __TANUKIGB_CPU_REGISTER_REGISTER_OPS_H__

#include <tanukigb/cpu/register/internal/register_arithmetic_operators.h>
#include <tanukigb/cpu/register/internal/register_bitwise_operators.h>
#include <tanukigb/cpu/register/internal/register_comparison_operators.h>
#include <tanukigb/cpu/register/internal/register_flag_operations.h>


#include <tanukigb/cpu/register/register_type_traits.h>
#include <tanukigb/utility/concepts.h>
#include <tanukigb/utility/integral.h>

#include <bit>
#include <concepts>
#include <format>
#include <ostream>
#include <type_traits>
#include <utility>

namespace tanukigb {

namespace register_ops_internal {
constexpr auto kHexCharsPerByte = 2;
}  // namespace register_ops_internal

template <RegisterType Register>
constexpr inline auto ClearRegister(Register& reg) {
  return reg &= ~reg;
}

template <RegisterType Register>
constexpr inline auto FillRegister(Register& reg) {
  return reg |= ~reg;
}

// Important Non-Friend Non-Member that enables unsigned registers to treat
// their value as a signed integer.
template <RegisterType Register>
constexpr inline auto AsSigned(Register& lhs) {
  return signed_cast(lhs.operator typename std::remove_reference_t<Register>::value_type());
}

// Less important Non-Friend Non-Member that enables signed registers (which is
// a weird choice but not my place to judge) to treat their value as an unsigned
// integer.
template <RegisterType Register>
constexpr inline auto AsUnsigned(Register& lhs) {
  return unsigned_cast(lhs.operator typename std::remove_reference_t<Register>::value_type());
}

template <RegisterType Register>
std::ostream& operator<<(std::ostream& os, const Register& obj) {
  using T = typename std::remove_reference_t<Register>::value_type;
  os << std::format("{:#0{}x}", obj.operator T(),
                    (1 + sizeof(T)) * register_ops_internal::kHexCharsPerByte);
  return os;
}

}  // namespace tanukigb
#endif