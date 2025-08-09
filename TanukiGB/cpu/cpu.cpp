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

/*
int Cpu::Run() {
  int retcode = 0;
  byte_t opcode;

  auto& PC = GetRegister<register_tags::PC>();
  while (retcode == 0) {
    opcode = mmu_.Read(PC);
    PC++;
    retcode = jump_table[opcode](*this);
  }
  return retcode;
}
*/
}  // namespace tanukigb
