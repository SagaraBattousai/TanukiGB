#ifndef __TANUKIGB_CPU_INTERNAL_REGISTER_ARITHMETIC_OPERATORS_H__
#define __TANUKIGB_CPU_INTERNAL_REGISTER_ARITHMETIC_OPERATORS_H__

#include <tanukigb/cpu/register_functionoid.h>
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

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator+(const Register<T, F>& lhs, U rhs) {
  return ((lhs.operator T()) + rhs);
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator+=(Register<T, F>& lhs, U rhs) {
  return (lhs = operator+(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator-(const Register<T, F>& lhs, U rhs) {
  return (lhs.operator T() - rhs);
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator-=(Register<T, F>& lhs, U rhs) {
  return (lhs = operator-(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator*(const Register<T, F>& lhs, U rhs) {
  return (lhs.operator T() * rhs);
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator*=(Register<T, F>& lhs, U rhs) {
  return (lhs = operator*(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator/(const Register<T, F>& lhs, U rhs) {
  return (lhs.operator T() / rhs);
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator/=(Register<T, F>& lhs, U rhs) {
  return (lhs = operator/(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator%(const Register<T, F>& lhs, U rhs) {
  return (lhs.operator T() % rhs);
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator%=(Register<T, F>& lhs, U rhs) {
  return (lhs = operator%(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F>
inline T operator~(const Register<T, F>& reg) {
  return ~(reg.operator T());
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator&(const Register<T, F>& lhs, U rhs) {
  return (lhs.operator T() & rhs);
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator&=(Register<T, F>& lhs, U rhs) {
  return (lhs = operator&(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator|(const Register<T, F>& lhs, U rhs) {
  return (lhs.operator T() | rhs);
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator|=(Register<T, F>& lhs, U rhs) {
  return (lhs = operator|(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator^(const Register<T, F>& lhs, U rhs) {
  return (lhs.operator T() ^ rhs);
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator^=(Register<T, F>& lhs, U rhs) {
  return (lhs = operator^(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator<<(const Register<T, F>& lhs, U rhs) {
  return (lhs.operator T() << rhs);
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator<<=(Register<T, F>& lhs, U rhs) {
  return (lhs = operator<<(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator>>(const Register<T, F>& lhs, U rhs) {
  return (lhs.operator T() >> rhs);
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U>
inline T operator>>=(Register<T, F>& lhs, U rhs) {
  return (lhs = operator>>(lhs, rhs));
}

// Although it makes sence and is possible to return Register& here, for
// symetry it returns T just as postfix does since postfix cannot return
// Register&

template <std::integral T, RegisterFunctionoid<T> F>
inline T operator++(Register<T, F>& reg) {
  return operator+=(reg, 1);
}

template <std::integral T, RegisterFunctionoid<T> F>
inline T operator++(Register<T, F>& reg, int) {
  T old = reg.operator T();
  operator++(reg);
  return old;
}
template <std::integral T, RegisterFunctionoid<T> F>
inline T operator--(Register<T, F>& reg) {
  return operator-=(reg, 1);
}

template <std::integral T, RegisterFunctionoid<T> F>
inline T operator--(Register<T, F>& reg, int) {
  T old = reg.operator T();
  operator--(reg);
  return old;
}


}  // namespace tanukigb

#endif