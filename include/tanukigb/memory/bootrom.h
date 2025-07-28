#ifndef __TANUKIGB_MEMORY_BOOTROM_H__
#define __TANUKIGB_MEMORY_BOOTROM_H__

#include <_TanukiGB_config.h>
#include <tanukigb/memory/memory.h>
#include <tanukigb/types/types.h>

#include <vector>

namespace tanukigb {

// NOTE: For now We will only consider the OG Gameboy, We will implement the
// Colour one after not simultaniously, I don't yet possess the skill or
// understanding.

class Bootrom {  // Fulfils ROM
 public:
  const int rom_size_;  // explicitly set but should be same as rom_.size()

  static TANUKIGB_EXPORT Bootrom GBRom();
  static TANUKIGB_EXPORT Bootrom CGBRom();

  // Do inline functions need exporting? Maybe if addr needed/to make ABI
  // stable?
  byte_t Read(word_t addr) const { return rom_[addr]; }

 private:
  Bootrom(std::vector<byte_t>&& rom, int rom_size)
      : rom_{std::move(rom)}, rom_size_{rom_size} {}

  // May change to shared_ptr array as it's "fixed size" but it seems a
  // bit...more work
  const std::vector<byte_t> rom_;

  // No need to store value of the enable location since the boot rom need not
  // know this info.
};

}  // namespace tanukigb

#endif