#ifndef __TANUKIGB_CPU_REGISTER_SET_H__
#define __TANUKIGB_CPU_REGISTER_SET_H__

#include <array>
#include <climits>
#include <concepts>
#include <format>
#include <ostream>

namespace tanukigb {

// I can't work out if reinterpret_Cast is acceptable for this use with type
// accessability
//
// Should I use std::align and should I use std::launder??
// std::align isn't right as alignof has helped with that (I think)
// although I guess it's still dodgy to use reinterpret_cast if one were to put
// an int at the third byte (wouldn't be aligned anymore right??) I guess I
// could place it a byte at a time? Maybe?
//
// Is it poorly/not portable.
//
// For now I shall not, additionally (asper isocpp's guide) I'm probably trying
// to be too cleaver by using an array (for locallity?) but none the less
//
// Because it's so unlikly, we won't bother with mixed endian systems.
// Additionally we're going to assume all integrals are the same endianness as
// it's only on niche machines that we would have to worry about such things, so
// testing will be important.
//
template <int BufferByteSize, decltype(alignof(nullptr_t)) Alignment>
class RegisterSet {
 private:
  // unsigned char used as alignof = 1 always and is used over std::byte as
  // std::byte is not an integral type
  alignas(Alignment) std::array<unsigned char, BufferByteSize> raw_register_buffer_;

 public:
  using index_type = decltype(sizeof(nullptr_t));

  static RegisterSet InitalizedRegisterSet(unsigned char init = 0x00) {
    RegisterSet rs;
    rs.raw_register_buffer_.fill(init);
    return rs;
  }

  RegisterSet() = default;

  template <std::integral T>
  T Get(int byte_offset) const noexcept {
    const unsigned char* const ptr =
        this->raw_register_buffer_.data() + byte_offset;
    return *(reinterpret_cast<const T* const>(ptr));
  }

  template <std::integral T>
  T& Get(int byte_offset) noexcept {
    unsigned char* const ptr = this->raw_register_buffer_.data() + byte_offset;
    return *(reinterpret_cast<T* const>(ptr));
  }

  // Must be a nicer way to do this!

  // GetComposite functions may require pointer to store value (C style)
  // Not the neatest solution (should probably take a shift parameter but....
  // this is bespoke enough for me so..... I mean this isnt a library (I mean..)
  template <std::integral T, std::integral U>
  T GetComposite(int higher_byte_offset, int lower_byte_offset) const noexcept {
    const U higher_value = Get<U>(higher_byte_offset);
    const U lower_value = Get<U>(lower_byte_offset);

    return (static_cast<T>(higher_value) << (sizeof(U) * CHAR_BIT)) |
           lower_value;
  }

  template <std::integral T, std::integral U>
  T GetComposite(int higher_byte_offset) const noexcept {
    if constexpr (std::endian::native == std::endian::big) {
      // Dangerous if higher_byte_offset in range [arr.size() - sizeof(T),
      // arr.size()) <- range syntax
      return GetComposite<T, U>(higher_byte_offset,
                                higher_byte_offset + sizeof(U));
    } else if constexpr (std::endian::native == std::endian::little) {
      // Dangerous if higher_byte_offset in range [ 0, sizeof(T) ) <- range
      // syntax
      return GetComposite<T, U>(higher_byte_offset,
                                higher_byte_offset - sizeof(U));
    } else {
      static_assert(
          false,
          "Mixed endian systems are not (potentially currently) supported.");
    }
  }

  template <std::integral T>
  void SetComposite(int higher_byte_offset, int lower_byte_offset,
                    T value) const noexcept;

  template <std::integral T>
  void SetComposite(int higher_byte_offset, T value) const noexcept;

  friend std::ostream& operator<<(std::ostream& os, const RegisterSet& obj) {
    os << "0x";
    for (const unsigned char& b : obj.raw_register_buffer_) {
      os << std::format("{:02x}", to_underlying(b));
    }
    return os;
  }
};

}  // namespace tanukigb
#endif