#ifndef __TANUKIGB_CPU_REGISTER_INTERNAL_REGISTER_BITWISE_OPERATORS_H__
#define __TANUKIGB_CPU_REGISTER_INTERNAL_REGISTER_BITWISE_OPERATORS_H__

#include <tanukigb/cpu/register/register_type_traits.h>

#include <concepts>

namespace tanukigb {

// All operators are non-friend, non-member as the private functionoid exposes
// all it's own methods as methods of the register class.
//
// Integer promotion / Usual arithmetic conversions take place but overflow (if
// the register has a signed integral underlying type) may still occur,
// responsibility lies with the caller.
//

// I dont know if I needed to write the non assignment versions as Register is
// implicitly cast to T. But I already have and now Ive got to do them all again
// for the case theyre both registers, I could skip it for the non assignment
// versions but ...

template <RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator~(const Register& reg) {
  return ~(reg.operator typename std::remove_reference_t<Register>::value_type());
}

template <std::integral T, RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator&(const Register& lhs,
                                                         T rhs) {
  return (lhs.operator typename std::remove_reference_t<Register>::value_type() & rhs);
}

template <std::integral T, RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator&=(Register& lhs,
                                                          T rhs) {
  return (lhs = operator&(lhs, rhs));
}

template <std::integral T, RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator|(const Register& lhs,
                                                         T rhs) {
  return (lhs.operator typename std::remove_reference_t<Register>::value_type() | rhs);
}

template <std::integral T, RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator|=(Register& lhs,
                                                          T rhs) {
  return (lhs = operator|(lhs, rhs));
}

template <std::integral T, RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator^(const Register& lhs,
                                                         T rhs) {
  return (lhs.operator typename std::remove_reference_t<Register>::value_type() ^ rhs);
}

template <std::integral T, RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator^=(Register& lhs,
                                                          T rhs) {
  return (lhs = operator^(lhs, rhs));
}

template <std::integral T, RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator<<(const Register& lhs,
                                                          T rhs) {
  return (lhs.operator typename std::remove_reference_t<Register>::value_type() << rhs);
}

template <std::integral T, RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator<<=(Register& lhs,
                                                           T rhs) {
  return (lhs = operator<<(lhs, rhs));
}

template <std::integral T, RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator>>(const Register& lhs,
                                                          T rhs) {
  return (lhs.operator typename std::remove_reference_t<Register>::value_type() >> rhs);
}

template <std::integral T, RegisterType Register>
constexpr inline typename std::remove_reference_t<Register>::value_type operator>>=(Register& lhs,
                                                           T rhs) {
  return (lhs = operator>>(lhs, rhs));
}

// Arimetic/Bitwise operators where both are Registers (essentially the
// same/wrappers to the above)

template <RegisterType Register, RegisterType OtherRegister>
constexpr inline typename std::remove_reference_t<Register>::value_type operator&(
    const Register& lhs, const OtherRegister& rhs) {
  return (lhs.operator typename std::remove_reference_t<Register>::value_type() &
          rhs.operator typename std::remove_reference_t<Register>::value_type());
}

template <RegisterType Register, RegisterType OtherRegister>
constexpr inline typename std::remove_reference_t<Register>::value_type operator&=(
    Register& lhs, const OtherRegister& rhs) {
  return (lhs = operator&(lhs, rhs));
}

template <RegisterType Register, RegisterType OtherRegister>
constexpr inline typename std::remove_reference_t<Register>::value_type operator|(
    const Register& lhs, const OtherRegister& rhs) {
  return (lhs.operator typename std::remove_reference_t<Register>::value_type() |
          rhs.operator typename std::remove_reference_t<Register>::value_type());
}

template <RegisterType Register, RegisterType OtherRegister>
constexpr inline typename std::remove_reference_t<Register>::value_type operator|=(
    Register& lhs, const OtherRegister& rhs) {
  return (lhs = operator|(lhs, rhs));
}

template <RegisterType Register, RegisterType OtherRegister>
constexpr inline typename std::remove_reference_t<Register>::value_type operator^(
    const Register& lhs, const OtherRegister& rhs) {
  return (lhs.operator typename std::remove_reference_t<Register>::value_type() ^
          rhs.operator typename std::remove_reference_t<Register>::value_type());
}

template <RegisterType Register, RegisterType OtherRegister>
constexpr inline typename std::remove_reference_t<Register>::value_type operator^=(
    Register& lhs, const OtherRegister& rhs) {
  return (lhs = operator^(lhs, rhs));
}

template <RegisterType Register, RegisterType OtherRegister>
constexpr inline typename std::remove_reference_t<Register>::value_type operator<<(
    const Register& lhs, const OtherRegister& rhs) {
  return (lhs.operator typename std::remove_reference_t<Register>::value_type()
          << rhs.operator typename std::remove_reference_t<Register>::value_type());
}

template <RegisterType Register, RegisterType OtherRegister>
constexpr inline typename std::remove_reference_t<Register>::value_type operator<<=(
    Register& lhs, const OtherRegister& rhs) {
  return (lhs = operator<<(lhs, rhs));
}

template <RegisterType Register, RegisterType OtherRegister>
constexpr inline typename std::remove_reference_t<Register>::value_type operator>>(
    const Register& lhs, const OtherRegister& rhs) {
  return (lhs.operator typename std::remove_reference_t<Register>::value_type() >>
          rhs.operator typename std::remove_reference_t<Register>::value_type());
}

template <RegisterType Register, RegisterType OtherRegister>
constexpr inline typename std::remove_reference_t<Register>::value_type operator>>=(
    Register& lhs, const OtherRegister& rhs) {
  return (lhs = operator>>(lhs, rhs));
}

}  // namespace tanukigb

#endif