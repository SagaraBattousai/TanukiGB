
#include <_TanukiGB_config.h>

#include <tanukigb/memory/memory.h>
#include <tanukigb/memory/bootrom.h>

#include <cstdint>

namespace tanukigb {

Memory<Bootrom>::byte_t Bootrom::Read_Impl(Memory<Bootrom>::word_t addr) const {
  uint8_t x = (uint8_t)(((uint8_t)(addr>>8)) & (uint8_t)0x0F);
  return (Memory<Bootrom>::byte_t)x;
}

}  // namespace tanukigb