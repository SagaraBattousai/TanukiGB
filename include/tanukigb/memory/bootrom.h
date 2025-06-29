#ifndef __TANUKIGB_MEMORY_BOOTROM_H__
#define __TANUKIGB_MEMORY_BOOTROM_H__

#include <_TanukiGB_config.h>

#include <vector>

#include <tanukigb/types/types.h>
#include <tanukigb/memory/memory.h>

namespace tanukigb {

class TANUKIGB_EXPORT Bootrom : public Memory<Bootrom> {

  public:

    static Bootrom GBRom() { return Bootrom("dmg.bootrom"); }

  byte_t Read(word_t addr) const;

  private:

    Bootrom(const char* bootrom_filename);

    std::vector<byte_t> rom_;

};


}



#endif