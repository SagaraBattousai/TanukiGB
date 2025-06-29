
#include <fstream>
#include <iostream>
#include <tanukigb/memory/bootrom.h>

namespace tanukigb {

Bootrom::Bootrom(const char* bootrom_filename) {
  auto bootrom_file = std::fstream(bootrom_filename, std::ios::binary);
  if (!bootrom_file.is_open()) {
    std::cout << "failed to open " << bootrom_filename << '\n';
    return;
  }


  char buff[256];
  bootrom_file.read(buff, 256);

  std::cout << std::hex << (unsigned char)buff[0] << std::endl;

}

byte_t Bootrom::Read(word_t addr) const {
  byte_t x = (addr >> 8) & 0x0F;
  return x;
}

}  // namespace tanukigb