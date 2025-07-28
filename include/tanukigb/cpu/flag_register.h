#ifndef __TANUKIGB_CPU_FLAG_REGISTER_H__
#define __TANUKIGB_CPU_FLAG_REGISTER_H__

#include <tanukigb/cpu/register.h>

namespace tanukigb {

template <typename FlagFnoid, typename Integral>
concept FlagRegisterFunctionoid =
    std::is_integral_v<Integral> && RegisterFunctionoid<FlagFnoid, Integral> &&
    requires(FlagFnoid fnoid, Integral value) {
  // We'll make it a nttp as required flag should be known at compile time!
      { fnoid.template GetFlag<7>() } -> std::same_as<Integral>;
    };

template <std::integral T, FlagRegisterFunctionoid<T> Functionoid>
class FlagRegister {
 public:
  explicit FlagRegister(Functionoid fnoid) : fnoid_{fnoid} {}
  ~FlagRegister() = default;

  FlagRegister(const FlagRegister&) = delete;
  FlagRegister(FlagRegister&&) = delete;

  T operator=(T value) { return fnoid_(value); }

  operator T() const { return fnoid_(); }

 private:
  Functionoid fnoid_;
};

template <std::integral T, FlagRegisterFunctionoid<T> Functionoid>
std::ostream& operator<<(std::ostream& os,
                         const FlagRegister<T, Functionoid>& obj) {
  os << std::format("{:#0{}x}", obj.operator T(),
                    (1 + sizeof(T)) * internal::kHexCharsPerByte);
  return os;
}
}  // namespace tanukigb
#endif