#ifndef __TANUKIGB_UTILITY_TYPE_TRAITS_H__
#define __TANUKIGB_UTILITY_TYPE_TRAITS_H__

#include <type_traits>

namespace tanukigb {

template <typename FP>
struct is_function_pointer
    : std::bool_constant<std::is_pointer_v<FP> &&
                         std::is_function_v<std::remove_pointer_t<FP>>> {};

template <typename FP>
constexpr inline bool is_function_pointer_v = is_function_pointer<FP>::value;

// Cant use concept version here as this is the type_traits header and dont want
// to import eachother in CMAKE INTERFACE libraries

}  // namespace tanukigb

#endif