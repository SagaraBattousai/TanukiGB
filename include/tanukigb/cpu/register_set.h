#ifndef __TANUKIGB_CPU_REGISTER_SET_H__
#define __TANUKIGB_CPU_REGISTER_SET_H__

#include <_TanukiGB_config.h>
#include <tanukigb/cpu/register.h>
#include <tanukigb/cpu/register_set_functionoid.h>
#include <tanukigb/types/types.h>

#include <array>
#include <format>
#include <ostream>

namespace tanukigb {

// Using explicit template initilisation declaration (and definition in the
// .cpp) reduces code bloat and removes msvc's warning about dll-interface
// issues (C4251). However it does mean it's deadly if a client (and I know this
// is supposed to be an application and we could separate the library parts from
// the application parts) also has an explicit initilisation definition and I
// don't know of a way to warn clients outside of documentation (and the fact
// that they're declared here)

// Do not use explicitly template initalisation definite the following (byte_t
// defined in tanukigb/types/types.h as std::uint8_t)
extern template class RegisterSetFnoid<byte_t>;
extern template class Register<byte_t, RegisterSetFnoid<byte_t>>;

// Do not use explicitly template initalisation definite the following (word_t
// defined in tanukigb/types/types.h as std::uint16_t)
extern template class RegisterSetFnoid<word_t>;
extern template class Register<word_t, RegisterSetFnoid<word_t>>;

class RegisterSet {
 private:
  // explicit template initilisation declaration above (definition in
  // corresponding .cpp file)
  using ByteRegisterFnoid = RegisterSetFnoid<byte_t>;
  using ByteRegister = Register<byte_t, ByteRegisterFnoid>;

  // explicit template initilisation declaration above (definition in
  // corresponding .cpp file)
  using WordRegisterFnoid = RegisterSetFnoid<word_t>;
  using WordRegister = Register<word_t, WordRegisterFnoid>;

 public:
  TANUKIGB_EXPORT RegisterSet();

  static TANUKIGB_EXPORT RegisterSet
  InitalizedRegisterSet(unsigned char init = 0x00) {
    return RegisterSet(init);
  }

  // 8 Bit Registers
  ByteRegister A;
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

  WordRegister AF;
  WordRegister BC;
  WordRegister DE;
  WordRegister HL;

  // No such "definitive" way to print so should use named functions but it's
  // easier to just have the simple print (RegisterDump) be operator<<
  friend TANUKIGB_EXPORT std::ostream& operator<<(std::ostream& os,
                                                  const RegisterSet& obj) {
    os << "0x";
    for (const unsigned char& b : obj.register_buffer_) {
      os << std::format("{:02x}", b);
    }
    return os;
  }

 private:
  constexpr static int kRegisterSetBufferBytes = 12;
  using buffer_type = std::array<unsigned char, kRegisterSetBufferBytes>;
  // No longer needs to be aligned as we're now using memcpy
  buffer_type register_buffer_;

  explicit RegisterSet(unsigned char init) : RegisterSet() {
    register_buffer_.fill(init);
  }
};

TANUKIGB_EXPORT std::ostream& PrettyPrintRegisters(std::ostream& os,
                                                   const RegisterSet& rs);

}  // namespace tanukigb
#endif