#ifndef __TANUKIGB_CPU_REGISTER_H__
#define __TANUKIGB_CPU_REGISTER_H__

#include <tanukigb/cpu/register/internal/register_arithmetic_operators.h>
#include <tanukigb/cpu/register/internal/register_bitwise_operators.h>
#include <tanukigb/cpu/register/internal/register_comparison_operators.h>
#include <tanukigb/cpu/register/internal/register_flag_operations.h>
#include <tanukigb/cpu/register/register_functionoid.h>
#include <tanukigb/utility/concepts.h>
#include <tanukigb/utility/integral.h>

#include <bit>
#include <concepts>
#include <format>
#include <ostream>
#include <type_traits>
#include <utility>

namespace tanukigb {

namespace register_internal {
constexpr auto kHexCharsPerByte = 2;
}  // namespace register_internal

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

  Register(const Register&) = delete;  // = default;  // delete;
  Register(Register&&) = delete;       // default;       // delete;

  T operator=(T value) noexcept { return fnoid_(value); }

  // Meh, probably should be explicit, and would remove the need for non
  // assignment binary operators but .... Fine to leave as implicit, now the
  // requirement is on me to ensure I've written all the operators. Can I test
  // for this.
  //
  // Now we have .Value lets try explicit again
  //
  // I still prefer implicit even though it only saves writing .Value() in a
  // relativly specific case (reading from an array). Would be interesting if we
  // could use explicit (...) to work around this.
  //
  operator T() const noexcept { return fnoid_(); }

  // Does not need to be a member but just a nice way to convert without calling
  // .operatorT() in external code and potentially allows for making operator
  // T() explicit and then clients can use Register.Value() as a nice
  // replacement
  T Value() const noexcept { return this->operator T(); }

 private:
  Functionoid fnoid_;
};

template <std::integral T>
class Register<T, std::nullptr_t> {
 public:
  using value_type = T;
  
  Register() = default;
  explicit Register(T value) : value_{value} {}
  ~Register() = default;

  Register(const Register&) = delete;
  Register(Register&&) = delete;

  T operator=(T value) noexcept {
    value_ = value;
   value_;
  }

  operator T() const noexcept { return value_; }

  T Value() const noexcept { return this->operator T(); }

 private:
  T value_;
};

template <std::integral T>
using RegisterWrapper = Register<T, std::nullptr_t>;



template <std::integral T, RegisterFunctionoid<T> Functionoid>
constexpr inline T ClearRegister(Register<T, Functionoid>& reg) {
  return reg &= ~reg;
}

template <std::integral T, RegisterFunctionoid<T> Functionoid>
constexpr inline T FillRegister(Register<T, Functionoid>& reg) {
  return reg |= ~reg;
}

// Important Non-Friend Non-Member that enables unsigned registers to treat
// their value as a signed integer.
template <std::unsigned_integral T, RegisterFunctionoid<T> F>
constexpr inline auto AsSigned(Register<T, F>& lhs) {
  return signed_cast(lhs.operator T());
}

// Less important Non-Friend Non-Member that enables signed registers (which is
// a weird choice but not my place to judge) to treat their value as an unsigned
// integer.
template <std::signed_integral T, RegisterFunctionoid<T> F>
constexpr inline auto AsUnsigned(Register<T, F>& lhs) {
  return unsigned_cast(lhs.operator T());
}

template <std::integral T, RegisterFunctionoid<T> Functionoid>
std::ostream& operator<<(std::ostream& os,
                         const Register<T, Functionoid>& obj) {
  os << std::format("{:#0{}x}", obj.operator T(),
                    (1 + sizeof(T)) * register_internal::kHexCharsPerByte);
  return os;
}

}  // namespace tanukigb
#endif