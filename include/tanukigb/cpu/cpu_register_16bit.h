#ifndef __TANUKIGB_CPU_REGISTER_16BIT_H__
#define __TANUKIGB_CPU_REGISTER_16BIT_H__

#include <_TanukiGB_config.h>

#include <tanukigb/types/types.h>
#include <tanukigb/cpu/cpu_register.h>

// NOTE: The requirement on std::uint8_t is almost always fine but...
// technically it is possible for that not to be supported so ...

namespace tanukigb {

class TANUKIGB_EXPORT CpuRegister16Bit : public CpuRegister<word_t> {
 public:
  static constexpr int k16BitRegisterSize = 2;

  CpuRegister16Bit(word_t* data_ptr);
};

}  // namespace tanukigb

#endif