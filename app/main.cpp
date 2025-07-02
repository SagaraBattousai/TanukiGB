#include <iostream>

#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/cpu.h>
#include <tanukigb/cpu/register_set.h>

#include <cstdint>

int main() {

  auto cpu = tanukigb::Cpu::GameboyCpu();

  cpu.DumpRegisters(std::cout);

  cpu.PrettyDumpRegisters(std::cout);

  cpu.Run();

  cpu.DumpRegisters(std::cout);

  cpu.PrettyDumpRegisters(std::cout);

  return 0; 

}
