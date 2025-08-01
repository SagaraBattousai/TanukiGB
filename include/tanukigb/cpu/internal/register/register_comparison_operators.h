#ifndef __TANUKIGB_CPU_INTERNAL_REGISTER_REGISTER_COMPARISON_OPERATORS_H__
#define __TANUKIGB_CPU_INTERNAL_REGISTER_REGISTER_COMPARISON_OPERATORS_H__

#include <tanukigb/cpu/register_functionoid.h>

#include <compare>
#include <concepts>

namespace tanukigb {

template <std::integral T, RegisterFunctionoid<T> Functionoid>
class Register;

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

template <std::integral T, RegisterFunctionoid<T> F>
inline std::strong_ordering operator<=>(const Register<T, F>& lhs,
                                        const Register<T, F>& rhs) {
  return (lhs.operator T() <=> rhs.operator T());
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<U> G>
inline std::weak_ordering operator<=>(const Register<T, F>& lhs,
                                      const Register<U, G>& rhs) {
  return (lhs.operator T() <=> rhs.operator U());
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<U> G>
inline bool operator==(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs <=> rhs) == 0;
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<U> G>
inline bool operator!=(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs <=> rhs) != 0;
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<U> G>
inline bool operator<(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs <=> rhs) < 0;
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<U> G>
inline bool operator>(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs <=> rhs) > 0;
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<U> G>
inline bool operator<=(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs <=> rhs) <= 0;
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<U> G>
inline bool operator>=(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs <=> rhs) >= 0;
}


}  // namespace tanukigb

#endif