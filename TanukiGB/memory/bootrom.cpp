
#include <memory>


#include <tanukigb/memory/bootrom.h>
#include "gameboy_rom.h"
#include "gameboy_colour_rom.h"

namespace tanukigb {

Bootrom Bootrom::GBRom() { 
  return Bootrom(std::vector<byte_t>(GAMEBOY_BOOTROM_BYTES));
}

Bootrom Bootrom::CGBRom() {
  return Bootrom(std::vector<byte_t>{GAMEBOY_COLOUR_BOOTROM_BYTES});
}

byte_t Bootrom::Read(word_t addr) const {
  return rom_[addr];
}

}  // namespace tanukigb