#ifndef __TANUKIGB_CPU_REGISTER_H__
#define __TANUKIGB_CPU_REGISTER_H__

#include <tanukigb/utility/integral.h>

#include <concepts>
#include <format>
#include <ostream>
#include <type_traits>
#include <utility>
#include <compare>

namespace tanukigb {

namespace internal {
constexpr auto kHexCharsPerByte = 2;
}  // namespace internal

template <typename Fnoid, typename Integral>
concept RegisterFunctionoid =
    std::is_integral_v<Integral> && requires(Fnoid fnoid, Integral value) {
      { fnoid() } noexcept -> std::same_as<Integral>;
      { fnoid(value) } noexcept -> std::same_as<Integral>;
    };

/*******************************************************************************
 * Be careful with signed types to avoid overflow (Register could be restricted
 * to unsigned integrals only as techncally registers are just raw bits and it's
 * the operations that determine whether a type is signed or unsigned) however,
 * as this is a psudo library it is left to the developer to decide if a signed
 * integral makes sence and therefore the responsibilty to avoid Undefined
 * behavoir (and implemnetationd defined behavoir regarding signed integer
 * conversion) is their responsibility.
 ******************************************************************************/
template <std::integral T, RegisterFunctionoid<T> Functionoid>
class Register {
 public:
  using value_type = T;
  // No longer explicit, it makes sence to implicitly change as Functionoid is
  // useless alone
  Register(Functionoid fnoid) : fnoid_{fnoid} {}
  ~Register() = default;
  Register(T) = delete;  // To avoid posibility of being

  Register(const Register&) = delete;
  Register(Register&&) = delete;

  T operator=(T value) noexcept { return fnoid_(value); }

  // Meh, probably should be explicit, and would remove the need for non assignment binary operators but ....
  // Fine to leave as implicit, now the requirement is on me to ensure I've written all the operators. Can I test for this.
  operator T() const noexcept { return fnoid_(); }

  // Almost all operators can be non friend :D

 private:
  Functionoid fnoid_;
};

// Important Non-Friend Non-Member that enables unsigned registers to treat
// their value as a signed integer.
template <std::unsigned_integral T, RegisterFunctionoid<T> F>
constexpr inline auto AsSigned(Register<T, F>& lhs) {
  return signed_cast(lhs.operator T());
}

// All operators are non-friend, non-member as the private functionoid exposes
// all it's own methods as methods of the register class.
//
// Integer promotion / Usual arithmetic conversions take place but overflow (if
// the register has a signed integral underlying type) may still occur,
// responsibility lies with the caller.
//

// I dont know if I needed to write the non assignment versions as Register is
// implicitly cast to T. Should I make the T conversion explicit? Okay thats what I've done :)

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

template <std::integral T, RegisterFunctionoid<T> Functionoid>
std::ostream& operator<<(std::ostream& os,
                         const Register<T, Functionoid>& obj) {
  os << std::format("{:#0{}x}", obj.operator T(),
                    (1 + sizeof(T)) * internal::kHexCharsPerByte);
  return os;
}

}  // namespace tanukigb
#endif