#ifndef __TANUKIGB_CPU_REGISTER_SET_H__
#define __TANUKIGB_CPU_REGISTER_SET_H__

#include <_TanukiGB_config.h>
#include <tanukigb/cpu/register.h>
#include <tanukigb/cpu/register_set_functionoid.h>
#include <tanukigb/types/types.h>

#include <array>
#include <bit>
#include <format>
#include <ostream>

namespace tanukigb {

using rset_offset_type = std::array<int, 0>::size_type;

template <rset_offset_type BigEndianOffset, rset_offset_type LittleEndianOffset>
consteval rset_offset_type EndianOffset() {
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

// Using explicit template initilisation declaration (and definition in the
// .cpp) reduces code bloat and removes msvc's warning about dll-interface
// issues (C4251). However it does mean it's deadly if a client (and I know this
// is supposed to be an application and we could separate the library parts from
// the application parts) also has an explicit initilisation definition and I
// don't know of a way to warn clients outside of documentation (and the fact
// that they're declared here)

// Do not use explicitly template initalisation definite the following (byte_t
// defined in tanukigb/types/types.h as std::uint8_t)
extern template class RegisterSetFnoid<byte_t, true>;
extern template class Register<byte_t, RegisterSetFnoid<byte_t, true>>;

// Do not use explicitly template initalisation definite the following (word_t
// defined in tanukigb/types/types.h as std::uint16_t)
extern template class RegisterSetFnoid<word_t, true>;
extern template class Register<word_t, RegisterSetFnoid<word_t, true>>;

class TANUKIGB_EXPORT RegisterSet {
 private:
  // explicit template initilisation declaration above (definition in
  // corresponding .cpp file)
  using ByteRegisterFnoid = RegisterSetFnoid<byte_t, true>;
  using ByteRegister = Register<byte_t, ByteRegisterFnoid>;

  // explicit template initilisation declaration above (definition in
  // corresponding .cpp file)
  using WordRegisterFnoid = RegisterSetFnoid<word_t, true>;
  using WordRegister = Register<word_t, WordRegisterFnoid>;

 public:
  RegisterSet();

  static RegisterSet InitalizedRegisterSet(unsigned char init = 0x00) {
    return RegisterSet(init);
  }

  // 8 Bit Registers!
  ByteRegister A;
  // TODO Make Flag Register
  ByteRegister F;
  ByteRegister B;
  ByteRegister C;
  ByteRegister D;
  ByteRegister E;
  ByteRegister H;
  ByteRegister L;

  // 16 Bit Registers
  WordRegister SP;
  WordRegister PC;

  // 16 Bit Composite Registers (AF isn't one apparently)
  WordRegister BC;
  WordRegister DE;
  WordRegister HL;

  // No such "definitive" way to print so should use named functions but it's
  // easier to just have the simple print (RegisterDump) be operator<<
  friend std::ostream& operator<<(std::ostream& os, const RegisterSet& obj) {
    os << "0x";
    for (const unsigned char& b : obj.register_buffer_) {
      os << std::format("{:02x}", b);
    }
    return os;
  }

 private:
  constexpr static int kRegisterSetBufferBytes = 12;
  using buffer_type = std::array<unsigned char, kRegisterSetBufferBytes>;

  alignas(word_t) buffer_type register_buffer_;

  // nrvo isnt enforced by C++20 and wont work in some builds so using private
  // constructor. This one is to only be called named constructor:
  // InitalizedRegisterSet
  explicit RegisterSet(unsigned char init) : RegisterSet() {
    register_buffer_.fill(init);
  }
};

TANUKIGB_EXPORT std::ostream& PrettyPrintRegisters(std::ostream& os,
                                                   const RegisterSet& rs);

}  // namespace tanukigb
#endif