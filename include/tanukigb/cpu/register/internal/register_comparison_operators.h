#ifndef __TANUKIGB_CPU_REGISTER_INTERNAL_REGISTER_COMPARISON_OPERATORS_H__
#define __TANUKIGB_CPU_REGISTER_INTERNAL_REGISTER_COMPARISON_OPERATORS_H__

#include <tanukigb/cpu/register/register_type_traits.h>

#include <compare>
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
// implicitly cast to T. Should I make the T conversion explicit? Okay thats
// what I've done :)

template <RegisterType Register, RegisterType OtherRegister>
inline std::strong_ordering operator<=>(const Register& lhs,
                                        const OtherRegister& rhs) {
  return (lhs.operator register_value_type<Register>() <=>
          rhs.operator register_value_type<OtherRegister>);
}

//template <RegisterType Register, RegisterType OtherRegister>
//inline std::weak_ordering operator<=>(const Register& lhs,
//                                      const OtherRegister& rhs) {
//  return (lhs.operator T() <=> rhs.operator U());
//}

template <RegisterType Register, RegisterType OtherRegister>
inline bool operator==(const Register& lhs, const OtherRegister& rhs) {
  return (lhs <=> rhs) == 0;
}

template <RegisterType Register, RegisterType OtherRegister>
inline bool operator!=(const Register& lhs, const OtherRegister& rhs) {
  return (lhs <=> rhs) != 0;
}

template <RegisterType Register, RegisterType OtherRegister>
inline bool operator<(const Register& lhs, const OtherRegister& rhs) {
  return (lhs <=> rhs) < 0;
}

template <RegisterType Register, RegisterType OtherRegister>
inline bool operator>(const Register& lhs, const OtherRegister& rhs) {
  return (lhs <=> rhs) > 0;
}

template <RegisterType Register, RegisterType OtherRegister>
inline bool operator<=(const Register& lhs, const OtherRegister& rhs) {
  return (lhs <=> rhs) <= 0;
}

template <RegisterType Register, RegisterType OtherRegister>
inline bool operator>=(const Register& lhs, const OtherRegister& rhs) {
  return (lhs <=> rhs) >= 0;
}

}  // namespace tanukigb

#endif