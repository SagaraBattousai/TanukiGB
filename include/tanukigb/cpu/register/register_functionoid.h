#ifndef __TANUKIGB_CPU_REGISTER_FUNCTIONOID_H__
#define __TANUKIGB_CPU_REGISTER_FUNCTIONOID_H__

#include <concepts>

namespace tanukigb {

template <typename Fnoid, typename Integral>
concept RegisterFunctionoid =
    std::is_null_pointer_v<Fnoid> ||
    (std::is_integral_v<Integral> && requires(Fnoid fnoid, Integral value) {
      { fnoid() } noexcept -> std::same_as<Integral>;
      { fnoid(value) } noexcept -> std::same_as<Integral>;
    });
}  // namespace tanukigb

#endif