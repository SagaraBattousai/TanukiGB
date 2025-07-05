#ifndef __TANUKIGB_CPU_REGISTER_SET_H__
#define __TANUKIGB_CPU_REGISTER_SET_H__

#include <_TanukiGB_config.h>
#include <tanukigb/types/types.h>

#include <array>
#include <ostream>
#include <cstdint>
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
  
  RegisterSet();

  // Could make template but it would require the underlying type of the enum to be the
  // return type for now.
  // 
  // Return const scalars by value according to C++ ref (makes sence sepecially
  // since all our values are
  //  actually smaller than ptrs :P)
  //
  // Wish I could make these inline as they all call an internal/private function but that would require
  // exposing the 
  //


  byte_t A() const noexcept;
  byte_t& A() noexcept;

  byte_t F() const noexcept;
  byte_t& F() noexcept;

  // TODO: Flags

  byte_t B() const noexcept;
  byte_t& B() noexcept;

  byte_t C() const noexcept;
  byte_t& C() noexcept;

  byte_t D() const noexcept;
  byte_t& D() noexcept;

  byte_t E() const noexcept;
  byte_t& E() noexcept;

  byte_t H() const noexcept;
  byte_t& H() noexcept;

  byte_t L() const noexcept;
  byte_t& L() noexcept;

  word_t SP() const noexcept;
  word_t& SP() noexcept;

  word_t PC() const noexcept;
  word_t& PC() noexcept;

  word_t AF() const noexcept;
  void SetAF(word_t value) noexcept;

  word_t BC() const noexcept;
  void SetBC(word_t value) noexcept;

  word_t DE() const noexcept;
  void SetDE(word_t value) noexcept;

  word_t HL() const noexcept;
  void SetHL(word_t value) noexcept;

  std::ostream& PrettyDumpRegisters(std::ostream& os) const;
  std::ostream& DumpRegisters(std::ostream& os) const;

 private:
  using buffer_type = std::uint_fast32_t;  // greater/equal alignment to largest
                                           // return type of register (word_t)
  static constexpr int kRegistersByteSize = 12;
  static constexpr int kRegistersBufferSize =
      (kRegistersByteSize + (sizeof(buffer_type) - 1)) / sizeof(buffer_type);

  std::array<buffer_type, kRegistersBufferSize> raw_register_buffer_;

  // Forward declare private enums. I should probably leave it as int but ....
  enum class R8Bit : int_fast8_t;
  enum class R16Bit : std::underlying_type_t<R8Bit>;
  enum class RComposite : std::underlying_type_t<R8Bit>;

  byte_t Get8Bit(R8Bit offset) const noexcept;
  byte_t& Get8Bit(R8Bit offset) noexcept;

  word_t Get16Bit(R16Bit offset) const noexcept;
  word_t& Get16Bit(R16Bit offset) noexcept;

  word_t GetComposite(RComposite offset) const noexcept;
  void SetComposite(RComposite offset, word_t value) noexcept;

};

}  // namespace tanukigb

#endif