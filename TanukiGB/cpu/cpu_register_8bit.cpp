#include <tanukigb/cpu/cpu_register_8bit.h>

namespace tanukigb {

CpuRegister8Bit::CpuRegister8Bit(byte_t* data_ptr)
    : CpuRegister(data_ptr, CpuRegister8Bit::k8BitRegisterSize) {}

}