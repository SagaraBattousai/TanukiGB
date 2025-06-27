
#include <tanukigb/memory/bootrom.h>

namespace tanukigb {

byte_t Bootrom::Read_Impl(word_t addr) const {
  byte_t x = (addr >> 8) & 0x0F;
  return x;
}

}  // namespace tanukigb