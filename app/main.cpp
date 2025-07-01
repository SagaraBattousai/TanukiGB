#include <iostream>

#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/cpu.h>

#include <cstdint>


int main() {

  auto cpu = tanukigb::Cpu();

  cpu.DumpRegisters(std::cout);

  cpu.A(0xFF);

  cpu.BC(0x1234);

  cpu.DumpRegisters(std::cout);

  return 0; 

}
