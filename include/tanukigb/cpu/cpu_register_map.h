#ifndef __TANUKIGB_CPU_REGISTER_MAP_H__
#define __TANUKIGB_CPU_REGISTER_MAP_H__

#include <_TanukiGB_config.h>

#include <array>
#include <ostream>

#include <tanukigb/types/types.h>
#include <tanukigb/cpu/cpu_register_16bit.h>
#include <tanukigb/cpu/cpu_register_8bit.h>

namespace tanukigb {

class TANUKIGB_EXPORT CpuRegisterMap {
 public:
  static constexpr int kRawRegisterBufferSize = 12;

  CpuRegisterMap();

  std::ostream& DumpRegisters(std::ostream& os) const;

  // Register access functions, note that byte_t and word_t underlying types may
  // change as 16bit is slower in some cases (such as msvc with uint_fast16_t
  // bing 32bits)
  //
  byte_t A() const { return A_.Get(); }
  byte_t F() const { return F_.Get(); }
  byte_t B() const { return B_.Get(); }
  byte_t C() const { return C_.Get(); }
  byte_t D() const { return D_.Get(); }
  byte_t E() const { return E_.Get(); }
  byte_t H() const { return H_.Get(); }
  byte_t L() const { return L_.Get(); }
  word_t SP() const { return SP_.Get(); }
  word_t PC() const { return PC_.Get(); }

  //TODO:
  word_t AF() { return 0x00; }
  word_t BC() { return 0x00; }
  word_t DE() { return 0x00; }
  word_t HL() { return 0x00; }

  byte_t ZeroFlag() const { return this->F() >> 7; }
  byte_t SubtractFlag() const { return (this->F() >> 6) & 0x01; }
  byte_t HalfCarryFlag() const { return (this->F() >> 5) & 0x01; }
  byte_t CarryFlag() const { return (this->F() >> 4) & 0x01; }

 private:
  CpuRegister8Bit A_, F_, B_, C_, D_, E_, H_, L_;
  CpuRegister16Bit SP_, PC_;

  // NOTE: The requirement on std::uint8_t is almost always fine but...
  // technically it is possible for that not to be supported so ...
  std::array<byte_t, kRawRegisterBufferSize> raw_register_buffer_;

};

}


#endif