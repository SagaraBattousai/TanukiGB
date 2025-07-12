#ifndef __TANUKIGB_CPU_CPU_H__
#define __TANUKIGB_CPU_CPU_H__

#include <_TanukiGB_config.h>
#include <tanukigb/cpu/register_set.h>
#include <tanukigb/memory/mmu.h>
#include <tanukigb/types/types.h>

#include <memory>
#include <ostream>

namespace tanukigb {
class TANUKIGB_EXPORT Cpu {
 public:
  static Cpu GameboyCpu() { return Cpu(MMU::GameboyMMU()); }
  static Cpu ColourGameboyCpu() { return Cpu(MMU::ColourGameboyMMU()); }

  ~Cpu() = default;

  int Run();

  std::ostream& DumpRegisters(std::ostream& os) const {
    return registers_.DumpRegisters(os);
  }

  std::ostream& PrettyDumpRegisters(std::ostream& os) const {
    return registers_.PrettyDumpRegisters(os);
  }

 private:
  Cpu(MMU&& mmu) : mmu_(std::move(mmu)), registers_() {};

  MMU mmu_;
  RegisterSet registers_;
};

}  // namespace tanukigb

#endif
