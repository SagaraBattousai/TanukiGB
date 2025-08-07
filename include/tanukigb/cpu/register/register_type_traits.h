#ifndef __TANUKIGB_CPU_REGISTER_REGISTER_TYPE_TRAITS_H__
#define __TANUKIGB_CPU_REGISTER_REGISTER_TYPE_TRAITS_H__

#include <climits>
#include <concepts>
#include <type_traits>

namespace tanukigb {

// Okay so this makes it SFINAE safe (when I've finished my paper I'd like to
// understand this better and the cases around friendly...)
//
// Cant seem to replace the SFINAE with Concepts (maybe this is the corner
// case?) Read up on this later!
//
// I guess the easiest case would be to constrain the register_traits with
// RegisterType?
//
template <typename R, typename = void>
struct register_traits {};

template <typename R>
struct register_traits<
    R, std::void_t<typename std::remove_reference_t<R>::value_type>> {
  using value_type = typename std::remove_reference_t<R>::value_type;

  static constexpr std::size_t bit_width = sizeof(value_type) * CHAR_BIT;

  template <std::size_t N>
  struct has_at_least_bits : std::bool_constant<(bit_width >= N)> {};
};

template <typename R>
using register_value_t = typename register_traits<R>::value_type;

template <typename R, std::size_t N>
using register_has_at_least_bits =
    register_traits<R>::template has_at_least_bits<N>;

template <typename R, std::size_t N>
inline constexpr bool register_has_at_least_bits_v =
    register_has_at_least_bits<std::remove_reference_t<R>, N>::value;

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
concept RegisterType = requires(
    R reg, typename std::remove_reference_t<R>::value_type vt) {
  std::is_integral_v<typename std::remove_reference_t<R>::value_type>;
  // requires an implicit (direct) conversion to value_type
  {
    reg.operator std::remove_reference_t<R>::value_type()
  } noexcept -> std::same_as<typename std::remove_reference_t<R>::value_type>;

  { reg = vt } noexcept;
};

}  // namespace tanukigb
#endif