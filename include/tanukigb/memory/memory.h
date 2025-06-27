#ifndef __TANUKIGB_MEMORY_MEMORY_H__
#define __TANUKIGB_MEMORY_MEMORY_H__

#include <_TanukiGB_config.h>
#include <tanukigb/types/types.h>

namespace tanukigb {

template <typename ConcreteMemory>
class TANUKIGB_LOCAL Memory {  // unexported but cant be an internal header so

 public:
   Memory() = default;

   byte_t Read(word_t addr) const {
     return 0xF0 | this->underlying().Read_Impl(addr);
   }  // Or ReadImpl

 private:
  ConcreteMemory& underlying() {
    return static_cast<ConcreteMemory&>(*this);
  }

  // remember const T& ==  T const& (east const)
  ConcreteMemory const& underlying() const {
    return static_cast<ConcreteMemory const&>(*this);
  }
};

}  // namespace tanukigb

#endif