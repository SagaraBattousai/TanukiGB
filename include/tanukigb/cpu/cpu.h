#ifndef __TANUKIGB_CPU_CPU_H__
#define __TANUKIGB_CPU_CPU_H__

#include <_TanukiGB_config.h>

#include <tanukigb/utility/pimpl.h>

namespace tanukigb {
class TANUKIGB_EXPORT Cpu {
 public:
  static Cpu GameboyCpu();
  static Cpu ColourGameboyCpu();

  // The following Constructors, destructors and operator='s
  // Must be defined (=default) in the impl file as we're using Pimpl 
  ~Cpu();
  Cpu(Cpu&&);
  Cpu& operator=(Cpu&&);


  // The following copy functions (Constructor and operator=) are deleted
  //  for now
  Cpu(const Cpu&) = delete;
  Cpu& operator=(const Cpu&) = delete;


  int Run();
  std::ostream& DumpRegisters(std::ostream& os) const;
  std::ostream& PrettyDumpRegisters(std::ostream& os) const;

 private:
  class CpuImpl;

  Cpu(Pimpl<CpuImpl>&&);

  Pimpl<CpuImpl> impl_;
};

}  // namespace tanukigb

#endif
