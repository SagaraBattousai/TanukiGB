#ifndef __TANUKIGB_MEMORY_BOOTROM_H__
#define __TANUKIGB_MEMORY_BOOTROM_H__

#include <_TanukiGB_config.h>

#include <vector>

#include <tanukigb/types/types.h>
#include <tanukigb/memory/memory.h>

namespace tanukigb {

class TANUKIGB_EXPORT Bootrom : public Memory<Bootrom> {

  public:
   static Bootrom GBRom();
   static Bootrom CGBRom();

  byte_t Read(word_t addr) const;

  private:
   //Bootrom(const char* bootrom_filename);
   Bootrom(std::vector<byte_t> rom);

   // May change to shared_ptr array as it's "fixed size" but it seems a bit...more work
    const std::vector<byte_t> rom_;

};


}



#endif