#ifndef __TANUKIGB_CPU_CPU_H__
#define __TANUKIGB_CPU_CPU_H__

#include <_TanukiGB_config.h>

#include <memory>
#include <ostream>

#include <tanukigb/types/types.h>
#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/cpu_register.h>
//#include <tanukigb/cpu/register_set.h>

namespace tanukigb {
class TANUKIGB_EXPORT Cpu {
 public:

  static Cpu GameboyCpu() { return Cpu(Bootrom::GBRom()); }
  static Cpu ColourGameboyCpu() { return Cpu(Bootrom::CGBRom()); }
    
  ~Cpu() = default;

  int Run();

  std::ostream& DumpRegisters(std::ostream& os) const;

 private:

   Cpu(Bootrom&& bootrom);

  //byte_t Read8BitRegister(int memory_offset) const;
  //void Write8BitRegister(int memory_offset, byte_t value);

  //word_t Read16BitRegister(int memory_offset) const;
  //void Write16BitRegister(int memory_offset, word_t value);

  Bootrom bootrom_;
   CpuRegister<byte_t> A_, F_, B_, C_, D_, E_, H_, L_;
   CpuRegister<word_t> SP_, PC_;
};


}  // namespace tanukigb

#endif
