#ifndef __TANUKIGB_CPU_CPU_H__
#define __TANUKIGB_CPU_CPU_H__

#include <_TanukiGB_config.h>

#include <memory>
#include <ostream>

#include <tanukigb/types/types.h>
#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/register_set.h>

namespace tanukigb {
class TANUKIGB_EXPORT Cpu {
 public:

  static Cpu GameboyCpu() { return Cpu(Bootrom::GBRom()); }
  static Cpu ColourGameboyCpu() { return Cpu(Bootrom::CGBRom()); }
    
  ~Cpu() = default;

  void Run();

  std::ostream& PrettyDumpRegisters(std::ostream& os) const {
    return register_set_.PrettyDumpRegisters(os);
  }

  std::ostream& DumpRegisters(std::ostream& os) const {
    return register_set_.DumpRegisters(os);
  }

 private:

   Cpu(Bootrom&& bootrom);

  //byte_t Read8BitRegister(int memory_offset) const;
  //void Write8BitRegister(int memory_offset, byte_t value);

  //word_t Read16BitRegister(int memory_offset) const;
  //void Write16BitRegister(int memory_offset, word_t value);

  Bootrom bootrom_;
  RegisterSet register_set_;
};


}  // namespace tanukigb

#endif
