#ifndef __TANUKIGB_CPU_REGISTER_SET_H__
#define __TANUKIGB_CPU_REGISTER_SET_H__

#include <_TanukiGB_config.h>

#include <array>
#include <bit>
#include <format>
#include <ostream>

#include <tanukigb/cpu/register.h>
#include <tanukigb/cpu/register_set_functionoid.h>
#include <tanukigb/types/types.h>

namespace tanukigb {

//#if defined(_WIN32) || defined(__CYGWIN__)
//extern template class Register<byte_t, RegisterSetFnoid<byte_t, true>>;
//#endif

class TANUKIGB_EXPORT RegisterSet {
 private:
  // Makes constructor neater
  using ByteRegisterFnoid = RegisterSetFnoid<byte_t, true>;
  //using ByteRegisterFnoid = RegisterSetFnoid<byte_t, false>;
  using ByteRegister = Register<byte_t, ByteRegisterFnoid>;

  using WordRegisterFnoid = RegisterSetFnoid<word_t, true>;
  //using WordRegisterFnoid = RegisterSetFnoid<word_t, false>;
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