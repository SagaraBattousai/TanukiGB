#include <tanukigb/cpu/cpu.h>
#include <tanukigb/cpu/opcode_handler.h>
#include <tanukigb/cpu/register/register_set.h>
#include <tanukigb/memory/mmu.h>
#include <tanukigb/types/types.h>
#include <tanukigb/utility/enum_utils.h>

#include <array>
#include <ostream>
#include <utility>

namespace tanukigb {

Cpu Cpu::GameboyCpu() { return Cpu(MMU::GameboyMMU()); }
Cpu Cpu::ColourGameboyCpu() { return Cpu(MMU::ColourGameboyMMU());
}

// TODO:
int Cpu::Run() {
  int retcode = 0;
  auto& PC = GetRegister<register_tags::PC>();
  while (true) {
    byte_t opcode = mmu_.Read(PC);
    PC++;
    retcode = jump_table[opcode](*this);
    if (retcode != 0) {
      break;
    }
  }
  return retcode;
}

// switch (opcode) {
//   case 0x31:
//     // Todo: after MMU add helper as the postfix++ is mucky.
//     registers_.SP = mmu_.Read(registers_.PC++) |
//     mmu_.Read(registers_.PC++)
//                                                      << 8;
//     // registers_.PC() += 2;
//     break;

//  case 0xAF:
//    // Same as ClearRegister(registers_.A) but VV is technically what the
//    // Opcode calls for:
//    // TODO: make nicer
//    registers_.A ^= registers_.A;

//    SetFlags<RegisterFlags, RegisterFlags::Z>(registers_.F);

//    // While clearing all flags before setting the one above achieves a
//    // similar result, it is technically wrong as it would destroy the
//    lower
//    // (unused) bits.
//    ClearFlags<RegisterFlags, RegisterFlags::N, RegisterFlags::H,
//               RegisterFlags::C>(registers_.F);
//    break;
//  default:
//    return opcode;
//}

}  // namespace tanukigb
