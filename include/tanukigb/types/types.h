#ifndef __TANUKIGB_TYPES_TYPES_H__
#define __TANUKIGB_TYPES_TYPES_H__

#include <cstdint>

namespace tanukigb {

// #define FAST_UNSIGNED_INTEGRAL(BITS) std::uint_fast##BITS##_t

// For now we will stick to these types as 8-bit computer's almost all suport
//  this and as much as I adore portability there are limits.
// If, in the future, we need to work on all machines we can make a wrapper
//  type, using the above macro, that will ensure the sizes (will be brutal
//  with the array/buffer implementation of the registers, unless I use an
//  array of std::byte :( )

using byte_t = std::uint8_t;

using word_t = std::uint16_t;

}  // namespace tanukigb

#endif