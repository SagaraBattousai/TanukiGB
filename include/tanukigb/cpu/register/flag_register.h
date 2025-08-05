#ifndef __TANUKIGB_CPU_FLAG_REGISTER_H__
#define __TANUKIGB_CPU_FLAG_REGISTER_H__

#include <tanukigb/cpu/register.h>

namespace tanukigb {

template <typename FlagFnoid, typename Integral>
concept FlagRegisterFunctionoid =
    std::is_integral_v<Integral> && RegisterFunctionoid<FlagFnoid, Integral> &&
    requires(FlagFnoid fnoid, Integral value) {
      // We'll make it a nttp as required flag should be known at compile time!
      // 0 is just a placeholder. Can we force it to be an integral of a
      // specific type?
      { fnoid.template GetFlag<0>() } -> std::same_as<Integral>;
      { fnoid.template SetFlag<0>() } -> std::same_as<Integral>;
    };

template <std::integral T, FlagRegisterFunctionoid<T> Functionoid>
class FlagRegister : Register<T, Functionoid> {
 public:
  FlagRegister(Functionoid fnoid) : Register(fnoid) {}
  ~FlagRegister() = default;

  FlagRegister(const FlagRegister&) = delete;
  FlagRegister(FlagRegister&&) = delete;

  // I think its fine just to use the same T ->template<std::integral U, U flag>
  template <T flag>
  constexpr T GetFlag() const {
    fnoid_.get<
  
  }
};

}  // namespace tanukigb
#endif