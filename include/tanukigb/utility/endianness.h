#ifndef __TANUKIGB_UTILITY_ENDIANNESS_H__
#define __TANUKIGB_UTILITY_ENDIANNESS_H__

#include <bit>

namespace tanukigb {

template <std::size_t BigEndianOffset, std::size_t LittleEndianOffset>
consteval std::size_t EndianOffset() {
  if constexpr (std::endian::native == std::endian::big) {
    return BigEndianOffset;
  } else if constexpr (std::endian::native == std::endian::little) {
    return LittleEndianOffset;
  } else {
    static_assert(
        false,
        "Mixed endian is (potentially currently) not supported. A per type "
        "endianness check may soon be implemented if some types have different "
        "endianness but niche byte layouts (e.g. using words instead of bytes "
        "or odd ordering) is unlikely to be supported).");
  }
}

}  // namespace tanukigb

#endif