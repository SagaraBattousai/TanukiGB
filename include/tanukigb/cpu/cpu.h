#ifndef __TANUKIGB_CPU_CPU_H__
#define __TANUKIGB_CPU_CPU_H__

#include <_TanukiGB_config.h>
#include <tanukigb/cpu/register_set.h>
#include <tanukigb/memory/bootrom.h>
#include <tanukigb/types/types.h>

#include <memory>
#include <ostream>

namespace tanukigb {
class TANUKIGB_EXPORT Cpu {
 public:
  static Cpu GameboyCpu() { return Cpu(Bootrom::GBRom()); }
  static Cpu ColourGameboyCpu() { return Cpu(Bootrom::CGBRom()); }

  ~Cpu() = default;

  int Run();

  std::ostream& DumpRegisters(std::ostream& os) const {
    return registers_.DumpRegisters(os);
  }

  std::ostream& PrettyDumpRegisters(std::ostream& os) const {
    return registers_.PrettyDumpRegisters(os);
  }

 private:
  Cpu(Bootrom&& bootrom);

  Bootrom bootrom_;
  RegisterSet registers_;
};

}  // namespace tanukigb

#endif
