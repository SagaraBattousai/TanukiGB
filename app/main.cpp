#include <iostream>

#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/cpu.h>


int main() {

  auto br = tanukigb::Bootrom::GBRom();
  auto cbr = tanukigb::Bootrom::CGBRom();

  //auto cpu = tanukigb::Cpu();

  unsigned gb_r = (unsigned)br[0x05];
  unsigned cgb_r = (unsigned)cbr[0x05];

  std::cout << " Bootrom.Read() " << std::hex << gb_r << std::endl;
  std::cout << " CBootrom.Read() " << std::hex << cgb_r << std::endl;


  return 0; 

}
