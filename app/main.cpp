#include <iostream>

#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/cpu.h>


int main() {

  auto br = tanukigb::Bootrom::GBRom();

  auto cpu = tanukigb::Cpu();

  unsigned x = (unsigned)br.Read(0xFFFF);

  std::cout << " Bootrom.Read() " << x << std::endl;


  return 0; 

}
