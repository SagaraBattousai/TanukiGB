#ifndef __TANUKIGB_CPU_INTERNAL_REGISTER_BITWISE_OPERATORS_H__
#define __TANUKIGB_CPU_INTERNAL_REGISTER_BITWISE_OPERATORS_H__

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
// implicitly cast to T. But I already have and now Ive got to do them all again
// for the case theyre both registers, I could skip it for the non assignment
// versions but ...

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

// Arimetic/Bitwise operators where both are Registers (essentially the same/wrappers to
// the above)

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<T> G>
inline T operator&(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs.operator T() & rhs.operator T());
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<T> G>
inline T operator&=(Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs = operator&(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<T> G>
inline T operator|(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs.operator T() | rhs.operator T());
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<T> G>
inline T operator|=(Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs = operator|(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<T> G>
inline T operator^(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs.operator T() ^ rhs.operator T());
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<T> G>
inline T operator^=(Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs = operator^(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<T> G>
inline T operator<<(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs.operator T() << rhs.operator T());
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<T> G>
inline T operator<<=(Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs = operator<<(lhs, rhs));
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<T> G>
inline T operator>>(const Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs.operator T() >> rhs.operator T());
}

template <std::integral T, RegisterFunctionoid<T> F, std::integral U,
          RegisterFunctionoid<T> G>
inline T operator>>=(Register<T, F>& lhs, const Register<U, G>& rhs) {
  return (lhs = operator>>(lhs, rhs));
}

}  // namespace tanukigb

#endif