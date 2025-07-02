#include <tanukigb/cpu/cpu_register_16bit.h>

namespace tanukigb {

CpuRegister16Bit::CpuRegister16Bit(word_t* data_ptr)
    : CpuRegister(data_ptr, CpuRegister16Bit::k16BitRegisterSize) {}

}  // namespace tanukigb