#include <iostream>

#include <tanukigb/memory/bootrom.h>


int main() {

  auto br = tanukigb::Bootrom();

  unsigned x = (unsigned)br.Read(0xFFFF);

  std::cout << "Bootrom.Read() " << x << std::endl;


  return 0; 

}
