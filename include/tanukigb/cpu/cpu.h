#ifndef __TANUKIGB_CPU_CPU_H__
#define __TANUKIGB_CPU_CPU_H__

#include <_TanukiGB_config.h>

#include <memory>
#include <ostream>

#include <tanukigb/types/types.h>
#include <tanukigb/memory/bootrom.h>

namespace tanukigb {
class TANUKIGB_EXPORT Cpu {
 public:
  //enum class Register { A, F, B, C, D, E, H, L, SP, PC, AF, BC, DE, HL };

  Cpu(Bootrom&& bootrom);
  ~Cpu();  // Required when using unique_ptr pimpl (AKA Modern Pimpl)

  void Run();

  // Register access functions, note that byte_t and word_t underlying types may
  // change as 16bit is slower in some cases (such as msvc with uint_fast16_t
  // bing 32bits)
  //
  // Can't inline them as they may change and we want a stable ABI (though do we really?)
  //
  // I'd rather pass in an enum but... meh im really loosing my skill!
  //
  byte_t A() const;
  void A(byte_t);

  byte_t F() const;
  void F(byte_t);

  byte_t B() const;
  void B(byte_t);

  byte_t C() const;
  void C(byte_t);

  byte_t D() const;
  void D(byte_t);

  byte_t E() const;
  void E(byte_t);

  byte_t H() const;
  void H(byte_t);

  byte_t L() const;
  void L(byte_t);

  word_t SP() const;
  void SP(word_t);

  word_t PC() const;
  void PC(word_t);

  word_t AF() const;
  void AF(word_t);

  word_t BC() const;
  void BC(word_t);

  word_t DE() const;
  void DE(word_t);

  word_t HL() const;
  void HL(word_t);

  byte_t ZeroFlag() const { return this->F() >> 7; }
  byte_t SubtractFlag() const { return (this->F() >> 6) & 0x01; }
  byte_t HalfCarryFlag() const { return (this->F() >> 5) & 0x01; }
  byte_t CarryFlag() const { return (this->F() >> 4) & 0x01; }

  std::ostream& DumpRegisters(std::ostream& os) const;

 private:

  byte_t Read8BitRegister(int memory_offset) const;
  void Write8BitRegister(int memory_offset, byte_t value);

  word_t Read16BitRegister(int memory_offset) const;
  void Write16BitRegister(int memory_offset, word_t value);

  // Forward declare cpu_registers class since:
  //   A) It may change
  //   B) it's only used here and therefore it should be embedded into this
  //   class
  //         (possibly with helper non-member functions)
  struct cpu_registers;
  std::unique_ptr<cpu_registers> registers_;

  Bootrom bootrom_;
};

}  // namespace tanukigb

#endif
