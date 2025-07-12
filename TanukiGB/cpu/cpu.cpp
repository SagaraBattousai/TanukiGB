
#include <tanukigb/cpu/cpu.h>

#include <cstdint>

namespace tanukigb {

int Cpu::Run() {
  while (true) {
    byte_t opcode = mmu_.Read(registers_.PC());
    registers_.PC()++;

    switch (opcode) {
      case 0x31:
        registers_.SP() =
            mmu_.Read(registers_.PC()) | mmu_.Read(registers_.PC() + 1) << 8; //todo: after MMU add helper.
        registers_.PC() += 2;
        break;
      default:
        return opcode;
    }
  }

  return 0;
}

}  // namespace tanukigb