#include <iostream>

#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/cpu.h>

#include <cstdint>
#include <tuple>

int main() {

  std::tuple<double, char> tup(1.618, 0xAB);

  char t2 = std::get<1>(tup);

  tanukigb::Cpu cpu = tanukigb::Cpu::GameboyCpu();

  cpu.DumpRegisters(std::cout);  

  return 0; 

}
