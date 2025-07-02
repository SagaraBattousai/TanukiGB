#ifndef __TANUKIGB_MEMORY_BOOTROM_H__
#define __TANUKIGB_MEMORY_BOOTROM_H__

#include <_TanukiGB_config.h>
#include <tanukigb/memory/memory.h>
#include <tanukigb/types/types.h>

#include <vector>

namespace tanukigb {

class TANUKIGB_EXPORT Bootrom : public Memory<Bootrom> {
 public:
  static Bootrom GBRom();
  static Bootrom CGBRom();

  byte_t Read(word_t addr) const;

 private:
  Bootrom(std::vector<byte_t>&& rom) : rom_(std::move(rom)) {}

  // May change to shared_ptr array as it's "fixed size" but it seems a
  // bit...more work
  const std::vector<byte_t> rom_;
};

}  // namespace tanukigb

#endif