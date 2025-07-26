#ifndef __TANUKIGB_CPU_REGISTER_SET_H__
#define __TANUKIGB_CPU_REGISTER_SET_H__

#include <array>
#include <bit>
#include <cstring>
#include <format>
#include <ostream>

#include <tanukigb/cpu/register.h>
#include <tanukigb/cpu/register_set_functionoid.h>
#include <tanukigb/types/types.h>

namespace tanukigb {

namespace {
using array_size_type = std::array<int, 0>::size_type;

// Is this allowed to be in the annonmous namespace
template <array_size_type BigEndianOffset, array_size_type LittleEndianOffset>
consteval array_size_type EndianOffset() {
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
}  // namespace

// So RegisterSet will be a class specific to the game boy (remember you're not
// making a library) however Register will be property-esque
//
// We know (because we're statically ensuring it) that all register access is properly aligned so we'll use the RegisterSetFnoid
//
class RegisterSet {
 private:
   // Makes constructor neater
   using ByteRegisterFnoid = RegisterSetFnoid<byte_t, true>;
   using ByteRegister = Register<byte_t, ByteRegisterFnoid>;

   using WordRegisterFnoid = RegisterSetFnoid<word_t, true>;
   using WordRegister = Register<word_t, WordRegisterFnoid>;
 public:

  RegisterSet();

  static RegisterSet InitalizedRegisterSet(unsigned char init = 0x00) {
    RegisterSet rs{};
    rs.register_buffer_.fill(init);
    return rs;
  }

  // 8 Bit Registers!
  ByteRegister A;
  //TODO Make Flag Register
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

  // No such "definitive" way to print so should use named functions but it's easier to just have the simple print (RegisterDump) be operator<<
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

  //No longer needs to be aligned as we're using memcpy but I think its better to keep it aligned.
  alignas(word_t) buffer_type register_buffer_;

};

std::ostream& PrettyPrintRegisters(std::ostream& os, const RegisterSet& rs);

}  // namespace tanukigb
#endif