#include <iostream>
#include <format>

#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/cpu.h>
#include <tanukigb/cpu/cpu_register.h>

#include <cstdint>

int main() {
  tanukigb::Cpu cpu = tanukigb::Cpu::GameboyCpu();

  int ret = cpu.Run();

  if (ret != 0) {
    std::cout << std::format("Unknown Opcode: {:#02x}\n", ret);
    cpu.DumpRegisters(std::cout);
  }

  return 0; 

}
