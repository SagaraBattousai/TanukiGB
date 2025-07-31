#ifndef __TANUKIGB_UTILITY_CONCEPTS_H__
#define __TANUKIGB_UTILITY_CONCEPTS_H__

#include <concepts>

namespace tanukigb {

// Generic concepts. Since google's style guide seems to not like them, we will
// put more bespoke concepts in internal namespaces in the header (or annonomous
// namespaces in cpp file).

template<typename T, typename... U>
concept one_of = (std::same_as<T, U> || ...);

template <typename T, typename... U>
concept none_of = (!std::same_as<T, U> && ...);

template <typename T>
concept strict_unsigned_integral =
    std::unsigned_integral<T> &&
    none_of<T, bool, char, char8_t, char16_t, char32_t, wchar_t>;

}  // namespace tanukigb

#endif