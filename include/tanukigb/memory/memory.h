#ifndef __TANUKIGB_MEMORY_MEMORY_H__
#define __TANUKIGB_MEMORY_MEMORY_H__

#include <tanukigb/types/types.h>

namespace tanukigb {

template <typename ConcreteMemory>
class Memory {  // Cant be an internal header but msvc complaining about no export but....

 public:
   Memory() = default;

   /*const byte_t& operator[](word_t addr) const {
     return this->underlying().Read(addr);
   }*/

   byte_t operator[](word_t addr) const {
     return this->underlying().Read(addr);
   }

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