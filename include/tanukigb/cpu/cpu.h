#ifndef __TANUKIGB_CPU_CPU_H__
#define __TANUKIGB_CPU_CPU_H__

#include <_TanukiGB_config.h>

#include <tanukigb/utility/pimpl.h>

namespace tanukigb {
class Cpu {
 public:
  static TANUKIGB_EXPORT Cpu GameboyCpu();
  static TANUKIGB_EXPORT Cpu ColourGameboyCpu();

  // The following Constructors, destructors and operator='s
  // Must be defined (=default) in the impl file as we're using Pimpl 
  TANUKIGB_EXPORT  ~Cpu();
  TANUKIGB_EXPORT Cpu(Cpu&&);
  TANUKIGB_EXPORT Cpu& operator=(Cpu&&);


  // The following copy functions (Constructor and operator=) are deleted
  //  for now
  Cpu(const Cpu&) = delete;
  Cpu& operator=(const Cpu&) = delete;


  TANUKIGB_EXPORT int Run();
  TANUKIGB_EXPORT std::ostream& PrintRegisters(std::ostream& os) const;
  TANUKIGB_EXPORT std::ostream& PrettyPrintRegisters(std::ostream& os) const;

 private:
  class CpuImpl;

  Cpu(Pimpl<CpuImpl>&&);

  Pimpl<CpuImpl> impl_;
};

}  // namespace tanukigb

#endif
