#ifndef __TANUKIGB_CPU_REGISTER_SET_H__
#define __TANUKIGB_CPU_REGISTER_SET_H__

#include <_TanukiGB_config.h>
#include <tanukigb/types/types.h>

#include <array>
#include <cstdint>
#include <ostream>
#include <type_traits>

namespace tanukigb {

// I continuously forget my new solutions, this time was more disapointing than
// usual, however here's
//    where we stand.
// 1) Registers are, as far as I can tell at the moment, variables and therefore
// should just return a
//    reference or copy to their underlying value.
// 2) Whilst there is a comminality between individual registers and registers
// as a concept, at the moment
//    (especially as this isnt really a library (yet)) it makes more sence to
//    make a bespoke model so far (and potentially see if we can once again
//    generalise this, although the issue of alignment is rough).
//
// Technically it is possible with a parameter pack but I cant quite workout how
// without revealing the underlying implementation.
//

class TANUKIGB_EXPORT RegisterSet {
 public:
  enum class R8Bit : int_fast8_t {
    A = 0,
    F = 1,
    B = 2,
    C = 3,
    D = 4,
    E = 5,
    H = 6,
    L = 7
  };
  enum class R16Bit : std::underlying_type_t<R8Bit> { SP = 4, PC = 5 }; // Offset in short... bit iffy
  enum class RComposite : std::underlying_type_t<R8Bit> {
    AF = R8Bit::A,
    BC = R8Bit::B,
    DE = R8Bit::D,
    HL = R8Bit::H
  };

  RegisterSet();

  // Could make template but it would require the underlying type of the enum to be the
  // return type for now.
  // 
  // Return const scalars by value according to C++ ref (makes sence sepecially
  // since all our values are
  //  actually smaller than ptrs :P)
  byte_t operator[](R8Bit register_name) const;
  byte_t& operator[](R8Bit register_name);

  word_t operator[](R16Bit register_name) const;
  word_t& operator[](R16Bit register_name);

  word_t operator[](RComposite register_name) const;
  void SetComposite(RComposite register_name, word_t value);

  std::ostream& PrettyDumpRegisters(std::ostream& os) const;
  std::ostream& DumpRegisters(std::ostream& os) const;

 private:
  using buffer_type = std::uint_fast32_t;  // greater/equal alignment to largest
                                           // return type of register (word_t)
  static constexpr int kRegistersByteSize = 12;
  static constexpr int kRegistersBufferSize =
      (kRegistersByteSize + (sizeof(buffer_type) - 1)) / sizeof(buffer_type);

  std::array<buffer_type, kRegistersBufferSize> raw_register_buffer_;
};

}  // namespace tanukigb

#endif