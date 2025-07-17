#ifndef __TANUKIGB_CPU_CPU_H__
#define __TANUKIGB_CPU_CPU_H__

#include <_TanukiGB_config.h>

#include <tanukigb/utility/pimpl.h>



namespace tanukigb {
class TANUKIGB_EXPORT Cpu {
 public:
  static Cpu GameboyCpu();
  static Cpu ColourGameboyCpu();

  // Must be defined (=default) in the impl file as we're using Pimpl 
  ~Cpu();

  // Deleted For now
  Cpu(const Cpu&) = delete;

  // Must be defined (=default) in the impl file as we're using Pimpl
  Cpu(Cpu&&);

  // Deleted For now
  Cpu& operator=(const Cpu&) = delete;

  // Must be defined (=default) in the impl file as we're using Pimpl
  Cpu& operator=(Cpu&&);

  int Run();

  std::ostream& DumpRegisters(std::ostream& os) const;
  std::ostream& PrettyDumpRegisters(std::ostream& os) const;

 private:
  class CpuImpl;
  Cpu(Pimpl<CpuImpl>&&);

  //Do Not Call Directly
  Pimpl<CpuImpl> impl_;
};

}  // namespace tanukigb

#endif
