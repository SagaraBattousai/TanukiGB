#ifndef __TANUKIGB_CPU_REGISTER_SET_H__
#define __TANUKIGB_CPU_REGISTER_SET_H__

//NOTE: We were going to merge register set into cpu, which, despite reducing modularity
// it would have avoided the need for forwarding calls. However modularity is prefered to
// writing boilerplate (but I cant remember why i changed my mind :P )

#include <_TanukiGB_config.h>

#include <array>
#include <cstdint>
#include <ostream>
#include <type_traits>

#include <tanukigb/types/types.h>
// V defines bitmask operations for scoped enums
#include <tanukigb/utility/enum_utils.h>

namespace tanukigb {

// Once again Ive had another idea as I had a nap (two infact, one for a register set 
// and one for a property-esque class and once again ive forgotten :( 
//

class TANUKIGB_EXPORT RegisterSet {
 public:
  // Must be scoped as C and H are also function (register) names. Could call
  // them _Flag but... Must be byte_t so it matches register type Bitmask
  // functions implemented at end of header
  enum class Flag : byte_t {
    Z = (1 << 7),
    N = (1 << 6),
    H = (1 << 5),
    C = (1 << 4)
  };

  // remove fill later as this wont always be the case
  RegisterSet() : raw_register_buffer_() { raw_register_buffer_.fill(0x00); }

  // Could make template but it would require the underlying type of the enum to
  // be the return type for now.
  //
  // Return const scalars by value according to C++ ref (makes sence sepecially
  // since all our values are
  //  actually smaller than ptrs :P)
  //
  // Wish I could make these inline as they all call an internal/private
  // function but that would require exposing the
  //

  byte_t A() const noexcept;
  byte_t& A() noexcept;

  byte_t F() const noexcept;
  byte_t& F() noexcept;

  byte_t GetFlags() const noexcept { return F(); }
  void SetFlags(Flag flags) noexcept { F() |= flags; }
  void ClearFlags(Flag flags) noexcept { F() &= ~flags; }
  // void ToggleFlags(Flag flags) noexcept { F() ^= flags; }

  bool IsZFlagSet() const noexcept { return (F() & Flag::Z) != 0; }
  bool IsNFlagSet() const noexcept { return (F() & Flag::N) != 0; }
  bool IsHFlagSet() const noexcept { return (F() & Flag::H) != 0; }
  bool IsCFlagSet() const noexcept { return (F() & Flag::C) != 0; }

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
  using buffer_type = std::uint_fast8_t;

  // Forward declare private enums. I should probably leave it as int but ....
  enum class R8Bit : int_fast8_t;
  enum class R16Bit : std::underlying_type_t<R8Bit>;
  enum class RComposite : std::underlying_type_t<R8Bit>;

  static constexpr int kRegistersBufferSize = 12;

  byte_t Get8Bit(R8Bit offset) const noexcept;
  byte_t& Get8Bit(R8Bit offset) noexcept;

  word_t Get16Bit(R16Bit offset) const noexcept;
  word_t& Get16Bit(R16Bit offset) noexcept;

  word_t GetComposite(RComposite offset) const noexcept;
  void SetComposite(RComposite offset, word_t value) noexcept;

  // Alignment assures we can cast to pointers of byte_t and word_t
  alignas(byte_t) alignas(word_t) alignas(buffer_type)
      std::array<buffer_type, kRegistersBufferSize> raw_register_buffer_;
};

enum class Flags : byte_t {
  Z = (1 << 7),
  N = (1 << 6),
  H = (1 << 5),
  C = (1 << 4)
};

}  // namespace tanukigb

#endif