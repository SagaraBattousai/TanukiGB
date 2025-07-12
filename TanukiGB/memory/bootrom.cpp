
#include <memory>


#include <tanukigb/memory/bootrom.h>
#include "gameboy_rom.h"
#include "gameboy_colour_rom.h"

namespace tanukigb {

// These cannot be inline as we dont want the raw bytes in the header file!

Bootrom Bootrom::GBRom() { 
  return Bootrom(std::vector<byte_t>(GAMEBOY_BOOTROM_BYTES),
                 GAMEBOY_BOOTROM_SIZE);
}

Bootrom Bootrom::CGBRom() {
  return Bootrom(std::vector<byte_t>{GAMEBOY_COLOUR_BOOTROM_BYTES}, GAMEBOY_COLOUR_BOOTROM_SIZE);
}

}  // namespace tanukigb