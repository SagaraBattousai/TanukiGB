#ifndef __TANUKIGB_CPU_REGISTER_8BIT_H__
#define __TANUKIGB_CPU_REGISTER_8BIT_H__

#include <_TanukiGB_config.h>

#include <tanukigb/types/types.h>
#include <tanukigb/cpu/cpu_register.h>

namespace tanukigb {

class TANUKIGB_EXPORT CpuRegister8Bit : public CpuRegister<byte_t> {
 public:
  static constexpr int k8BitRegisterSize = 1;

  CpuRegister8Bit(byte_t* data_ptr);
};

}  // namespace tanukigb

#endif