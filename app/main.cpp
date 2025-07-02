#include <iostream>

#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/cpu.h>
#include <tanukigb/cpu/register_set.h>

#include <cstdint>

int main() {

  tanukigb::RegisterSet rs;

  rs.DumpRegisters(std::cout);

  rs.PrettyDumpRegisters(std::cout);

  rs.Get(tanukigb::RegisterSet::Register8Bit::A) = 0xFF;

  rs.Get(tanukigb::RegisterSet::Register16Bit::BC) = 0xDEAD;

  rs.Get(tanukigb::RegisterSet::Register16Bit::PC)++;

  rs.DumpRegisters(std::cout);

  rs.PrettyDumpRegisters(std::cout);

  return 0; 

}
