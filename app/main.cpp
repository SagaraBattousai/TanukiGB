#include <iostream>

#include <tanukigb/memory/bootrom.h>
#include <tanukigb/cpu/cpu.h>
#include <tanukigb/cpu/register_set.h>
#include <tanukigb/cpu/cpu_register.h>

#include <cstdint>

int main() {

  tanukigb::CpuRegister<std::uint8_t> reg;

  reg = 0xAB;

  reg -= 0x01;

  std::cout << "Sum reg and 0xBE:\n";   

  std::uint8_t a = reg + 0xBE;

  std::cout << "\n\nSum 0xEF and reg:\n";   

  std::uint8_t b = 0xEF + reg;

  std::cout << std::hex << "\n\na = 0x" << +a << "\tb = 0x" << +b << std::endl;   



  return 0; 

}
