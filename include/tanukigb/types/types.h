#ifndef __TANUKIGB_TYPES_TYPES_H__
#define __TANUKIGB_TYPES_TYPES_H__

#include <cstdint>

namespace tanukigb {

// Despite the fact that uint8_t almost always exists there are places it does
// not
//  (apparently some TI chips in calculators only have 16 bits) regardless
//  I dont want to risk they type not existing but for now I wont worry about it
//  by using type alias' we can change them later, even if we have to use a
//  wrraper type....
using byte_t = std::uint8_t;

// uint_fast16_t is int on windows so faster but larger than "short" is that
// a problem on modern hardware?
using word_t = std::uint16_t;  // could possibly call address but theyre not
                               // always addresses

}  // namespace tanukigb

#endif