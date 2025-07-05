
#include <tanukigb/cpu/cpu.h>

#include <cstdint>

namespace tanukigb {

Cpu::Cpu(Bootrom&& bootrom) : bootrom_(std::move(bootrom)), registers_() {}

int Cpu::Run() {
  while (true) {
    byte_t opcode = bootrom_[registers_.PC()];
    registers_.PC()++;

    switch (opcode) {
      case 0x31:
        registers_.SP() =
            bootrom_[registers_.PC()] | bootrom_[registers_.PC() + 1] << 8; //todo: after MMU add helper.
        registers_.PC() += 2;
        break;
      default:
        return opcode;
    }
  }

  return 0;
}

}  // namespace tanukigb