#ifndef __TANUKIGB_CPU_REGISTER_H__
#define __TANUKIGB_CPU_REGISTER_H__

#include <concepts>
#include <format>
#include <ostream>
#include <utility>

namespace tanukigb {

namespace {
constexpr auto kHexCharsPerByte = 2;

// Will this work with const functionoid? Ideally we'd have 1 functionoid (if
// its larger than the size of a pointer) and then just store a reference to it
// in each register which will allow us to reduce the size.
// To completly reduce the size I suppose we could do it manually/use a bespoke
// class but that would still take a reference (to the backing array) an offset
// (int etc) Still this could be smaller so lets see if we can make a Register
// functionoid take an args parameter pack for its various functions.
//
// Cant return by ref since memset and bit_cast dont return by ref, however as these are integrals its alright
template <typename Fnoid, typename Integral>
concept RegisterFunctionoid =
    std::is_integral_v<Integral> && requires(Fnoid fnoid, Integral value) {
      { fnoid() } -> std::same_as<Integral>;
      // VV Requires either by value call operator or by lref (and optionally by
      // rref)
      { fnoid(value) } -> std::same_as<Integral>;
    };

}  // namespace

// Ive literally just forgotten how i was planning on passing the args without
// holding them :P
template <std::integral T, RegisterFunctionoid<T> Functionoid>
class Register {
 public:
  explicit Register(Functionoid fnoid) : fnoid_{fnoid} {}
  ~Register() = default;

  Register(const Register&) = delete;
  Register(Register&&) = delete;

  // No need to have const lvalue ref and rvalue ref as T is scalar (integral)
  // Cant return by ref since memset and bit_cast dont return by ref, however as
  // these are integrals its alright
  T operator=(T value) { return fnoid_(value); }

  // Cant return by ref since memset and bit_cast dont return by ref, however as
  // these are integrals its alright
  operator T() const { return fnoid_(); }

 private:
  Functionoid& fnoid_;
};

// Doesn't even need to be a friend :D
template <std::integral T, RegisterFunctionoid<T> Functionoid>
std::ostream& operator<<(std::ostream& os,
                         const Register<T, Functionoid>& obj) {
  os << std::format("{:#0{}x}", obj.fnoid(),
                    (1 + sizeof(T)) * kHexCharsPerByte);
  return os;
}

}  // namespace tanukigb
#endif