#ifndef __TANUKIGB_MEMORY_BOOTROM_H__
#define __TANUKIGB_MEMORY_BOOTROM_H__

#include <_TanukiGB_config.h>

#include <tanukigb/types/types.h>
#include <tanukigb/memory/memory.h>

namespace tanukigb {

class TANUKIGB_EXPORT Bootrom : public Memory<Bootrom> {

  public:

  Bootrom() = default;

  byte_t Read_Impl(word_t addr) const;
};


}



#endif