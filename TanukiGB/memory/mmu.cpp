
#include <tanukigb/memory/mmu.h>

namespace tanukigb {

byte_t MMU::Read(word_t addr) const {
  if (!IsBootromDisabled()) {
    if (addr >= 0 && addr < bootrom_.rom_size_) {
      return bootrom_.Read(addr);
    }
  } else {
    return psudo_ram_[addr]; //TODO
  }
}

void MMU::Write(word_t addr, byte_t value) { psudo_ram_[addr] = value; }
}  // namespace tanukigb