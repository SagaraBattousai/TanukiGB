#include <iostream>
#include <format>
#include <array>
#include <tuple>

#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/cpu.h>

#include <cstdint>

void RunGameBoy(tanukigb::Cpu& cpu) {
  int ret = cpu.Run();

  if (ret != 0) {
    std::cout << std::format("Unknown Opcode: {:#02x}\n", ret);
    cpu.DumpRegisters(std::cout);
  }
}

int main() {
  tanukigb::Cpu cpu = tanukigb::Cpu::GameboyCpu();
  RunGameBoy(cpu);

  cpu.PrettyDumpRegisters(std::cout);

  return 0; 

}
