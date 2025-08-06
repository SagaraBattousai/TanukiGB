#ifndef __TANUKIGB_CPU_REGISTER_TYPE_H__
#define __TANUKIGB_CPU_REGISTER_TYPE_H__

#include <climits>
#include <concepts>
#include <type_traits>

namespace tanukigb {

// Defined first as Concept (RegisterType) not required here thanks to SFINAE (I
// think)
template <typename R>
struct register_traits {
  using value_type = typename std::remove_reference_t<R>::value_type;

  static constexpr std::size_t bit_width = sizeof(value_type) * CHAR_BIT;

  template <std::size_t N>
  struct has_at_least_bits : std::bool_constant<(bit_width >= N)> {};
};

// Additional helpers (by leaving out of struct it saves typing :)

template <typename R, std::size_t N>
using register_has_at_least_bits =
    typename register_traits<R>::template has_at_least_bits<N>;

template <typename R, std::size_t N>
inline constexpr bool register_has_at_least_bits_v =
    register_has_at_least_bits<R, N>::value;

template <typename R>
inline constexpr bool register_has_at_least_8_bits =
    register_has_at_least_bits_v<R, 8>;

template <typename R>
inline constexpr bool register_has_at_least_16_bits =
    register_has_at_least_bits_v<R, 16>;

template <typename R>
inline constexpr bool register_has_at_least_32_bits =
    register_has_at_least_bits_v<R, 32>;

template <typename R>
inline constexpr bool register_has_at_least_64_bits =
    register_has_at_least_bits_v<R, 64>;

// Had to name it something, originally RegisterLike but thats not like anything
// in the C++ named requirements and I like that naming structure. It was
// between RegisterObject nad RegisterType but I went with type as (although I
// think the requirement on ::vaule_type (nested member name) enforces it to be
// an object) but we dont care whether it is or not.

template <typename R>
concept RegisterType =
    requires(R reg, std::remove_reference_t<R>::value_type vt) {
      std::is_integral_v<typename register_traits<R>::value_type>;
      // requires an implicit (direct) conversion to value_type
      {
        reg.operator register_traits<R>::value_type()
      } noexcept -> std::same_as<typename register_traits<R>::value_type>;

      { reg = vt } noexcept;
    };

}  // namespace tanukigb
#endif