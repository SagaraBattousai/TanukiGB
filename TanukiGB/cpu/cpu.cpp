
#include <tanukigb/cpu/cpu.h>

#include <cstdint>

namespace tanukigb {

Cpu::Cpu(Bootrom&& bootrom) : bootrom_(std::move(bootrom)), registers_() {}

int Cpu::Run() {
  while (true) {
    byte_t opcode = bootrom_[registers_[RegisterSet::R16Bit::PC]];
    registers_[RegisterSet::R16Bit::PC]++;

    switch (opcode) {
      case 0x31:
        registers_[RegisterSet::R16Bit::SP] =
            bootrom_[registers_[RegisterSet::R16Bit::PC]] |
            bootrom_[registers_[RegisterSet::R16Bit::PC] + 1] << 8;
        registers_[RegisterSet::R16Bit::PC] += 2;
        break;
      default:
        return opcode;
    }
  }

  return 0;
}

}  // namespace tanukigb