#ifndef __TANUKIGB_UTILITY_ENUM_FLAG_UTILS_H__
#define __TANUKIGB_UTILITY_ENUM_FLAG_UTILS_H__

#include <tanukigb/utility/enum_utils.h>

#include <type_traits>

namespace tanukigb {

/************************************************
 *************** OR Bitwise *********************
 ***********************************************/

template <enum_type E>
inline constexpr E& operator|=(E& lhs, E rhs) {
  return static_cast<E&>(to_underlying(lhs) |= to_underlying(rhs));
}

template <enum_type E>
inline constexpr E& operator|=(E& lhs, std::underlying_type_t<E> rhs) {
  return lhs |= static_cast<E>(rhs);
}

template <enum_type E>
inline constexpr std::underlying_type_t<E> operator|=(
    std::underlying_type_t<E>& lhs, E rhs) {
  return lhs |= to_underlying(rhs);
}

template <enum_type E>
inline constexpr E operator|(E lhs, E rhs) {
  return static_cast<E>(to_underlying(lhs) | to_underlying(rhs));
}

template <enum_type E>
inline constexpr E operator|(E lhs, std::underlying_type_t<E> rhs) {
  return static_cast<E>(to_underlying(lhs) | rhs);
}

template <enum_type E>
inline constexpr std::underlying_type_t<E> operator|(
    std::underlying_type_t<E> lhs, E rhs) {
  return lhs | to_underlying(rhs);
}

/************************************************
 *************** AND Bitwise *********************
 ***********************************************/

template <enum_type E>
inline constexpr E& operator&=(E& lhs, E rhs) {
  return static_cast<E&>(to_underlying(lhs) &= to_underlying(rhs));
}

template <enum_type E>
inline constexpr E& operator&=(E& lhs, std::underlying_type_t<E> rhs) {
  return lhs &= static_cast<E>(rhs);
}

template <enum_type E>
inline constexpr std::underlying_type_t<E> operator&=(
    std::underlying_type_t<E>& lhs, E rhs) {
  return lhs &= to_underlying(rhs);
}

template <enum_type E>
inline constexpr E operator&(E lhs, E rhs) {
  return static_cast<E>(to_underlying(lhs) & to_underlying(rhs));
}

template <enum_type E>
inline constexpr E operator&(E lhs, std::underlying_type_t<E> rhs) {
  return static_cast<E>(to_underlying(lhs) & rhs);
}

template <enum_type E>
inline constexpr std::underlying_type_t<E> operator&(
    std::underlying_type_t<E> lhs, E rhs) {
  return lhs & to_underlying(rhs);
}

/************************************************
 *************** XOR Bitwise *********************
 ***********************************************/

template <enum_type E>
inline constexpr E& operator^=(E& lhs, E rhs) {
  return static_cast<E&>(to_underlying(lhs) ^= to_underlying(rhs));
}

template <enum_type E>
inline constexpr E& operator^=(E& lhs, std::underlying_type_t<E> rhs) {
  return lhs ^= static_cast<E>(rhs);
}

template <enum_type E>
inline constexpr std::underlying_type_t<E> operator^=(
    std::underlying_type_t<E>& lhs, E rhs) {
  return lhs ^= to_underlying(rhs);
}

template <enum_type E>
inline constexpr E operator^(E lhs, E rhs) {
  return static_cast<E>(to_underlying(lhs) ^ to_underlying(rhs));
}

template <enum_type E>
inline constexpr E operator^(E lhs, std::underlying_type_t<E> rhs) {
  return static_cast<E>(to_underlying(lhs) ^ rhs);
}

template <enum_type E>
inline constexpr std::underlying_type_t<E> operator^(
    std::underlying_type_t<E> lhs, E rhs) {
  return lhs ^ to_underlying(rhs);
}

/************************************************
 *************** NOT Bitwise *********************
 ***********************************************/

template <enum_type E>
inline constexpr E operator~(E value) {
  return static_cast<E>(~to_underlying(value));
}

}  // namespace tanukigb

#endif
