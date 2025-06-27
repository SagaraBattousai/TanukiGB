#ifndef __TANUKIGB_MEMORY_MEMORY_H__
#define __TANUKIGB_MEMORY_MEMORY_H__

#include <cstdint>

namespace tanukigb {

template <typename ConcreteMemory>
class Memory {
 public:
   //Despite the fact that uint8_t almost always exists there are places it does not
   // (apparently some TI chips in calculators only have 16 bits) regardless
   // I dont want to risk they type not existing but for now I wont worry about it
   // by using type alias' we can change them later, even if we have to use a wrraper type....
   using byte_t = std::uint8_t;
   
   // uint_fast16_t is int on windows so faster but larger than "short" is that
   // a problem on modern hardware?
   using word_t = std::uint16_t; //could possibly call address but theyre not always addresses

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