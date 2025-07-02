#ifndef __TANUKIGB_CPU_REGISTER_SET_H__
#define __TANUKIGB_CPU_REGISTER_SET_H__

#include <_TanukiGB_config.h>

#include <cstdint>
#include <array>
#include <ostream>

#include <tanukigb/types/types.h>

namespace tanukigb {

// NOTE: Turns out the endianness is not an issue (at least I think, maybe there is some issue when reading as a smaller type
//   that said the interface is still crappy so..... Lets go back to each register being its own class??
// tbf a tuple could do nicely ...


// Before I start I should mention that I don't fully understand std::align from memory and I cant
// get it working in tests so we're just going to be smart and use the fact that: 
//    A) Theres an even number of bytes
//    B) We'll insist upon a buffer type of alignment greater than or equal to the largest register type
// In order to avoid writing a check (partially because I can't work out a nice way to do it)
// we will say that it's undefined behaviour :)
//  Actually we could take a parameter pack and use alignof etc but......
//
// Darn I am overcomplicating things, it doesn't need to be a base class, I mean I am overdesigning again
//   We can make it a base class if we need different versions and/or it becomes part of a generalised
//   emulator library
//

//template <typename T>
class TANUKIGB_EXPORT RegisterSet {
 public:
   // Offsets as value would be better but would reveal underlying ... stuff
   // Although now I think about it it is indeed the offsets so :D
   //
   // Note: Unscoped enums have the implementation define the integral type which is really
   // nice, probably smarter than myself as each implementation can pick the best and
   // avoids a cast :D
   // Although is std::int_fast8_t a smart alternative for a scoped enum. Actually thats
   //   what well do as we dont want anyone to pass in an integral type and get an implicit cast
   //
  enum class Register8Bit : std::int_fast8_t {A = 0, F = 1, B = 2, C = 3, D = 4, E = 5, H = 6, L = 7 };
  enum class Register16Bit : std::int_fast8_t {AF = 0, BC = 1, DE = 2, HL = 3, SP = 4, PC = 5};

 private:
   using buffer_type = std::uint_fast32_t;
  // I'm not sure that this is acceptable but hopefully it won't instansiate the template
   using array_size_type = std::array<buffer_type, 0>::size_type;
   static constexpr array_size_type kRawRegisterByteSize = 12;
   // Thing is it's ceil(kRawRegisterByteSize / sizeof(uint_fast32_t)) which is iffy for constexpr
   static constexpr array_size_type kRawRegisterBufferSize = 3;
 public:

  RegisterSet();

  // I'd love to write something clever like tuple/array's get<int>() but ....
  // Const versions returning scalar type should return by value (apparently though it makes sence
  // That said I will therefore have to write two different versions doing the same thing although
  //   actually it is quite different with the reinterpet casting, very cool!
  byte_t Get(Register8Bit register_name) const;

  //The reference versions are a bit dangerous as if this class dies then .....
  // Maybe I'm trying to be far too "cleaver" and should just have "loose" variables.
  // However, this way I can leave out a tonne of repetitive code / switch statements.

  byte_t& Get(Register8Bit register_name);
  word_t Get(Register16Bit register_name) const;
  word_t& Get(Register16Bit register_name);

  std::ostream& PrettyDumpRegisters(std::ostream& os) const;
  std::ostream& DumpRegisters(std::ostream& os) const;

  private:
  std::array<buffer_type, kRawRegisterBufferSize> raw_register_buffer_;
};

}



#endif