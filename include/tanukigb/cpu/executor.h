#ifndef __TANUKIGB_CPU_EXECUTOR_H__
#define __TANUKIGB_CPU_EXECUTOR_H__

// Byond having a JumpTable Executor should not know about, or care about
// opcodes, it just but provide what it needs. That could be via a concept or it
// could mean that opcode needs to know about the Executor (since the CRTP is
// essentially a (compile time) interface (much like a concept))
//
// Unfortunatly opcode is better suited (semantically, certainly not
// syntaxtically) to be decoupled than Executor.
//
// If there is an Executor Concept then we can constrain the opcodes but
// actually Concepts are for symantics not syntax/type checking so I should
// either use SFINAE (even though it says to prefer concepts) as the compiler
// will still catch the type being incorrect but I like specifying the interface
// so....
//
// Okay, Opcodes will know about the Executor but the Executor wont know about
// opcodes other the function pointer type and the forward decl of the Opcode
// handler class
//

#include <tanukigb/cpu/jump_table.h>
#include <tanukigb/cpu/register/register.h>
#include <tanukigb/cpu/register/register_type_traits.h>
#include <tanukigb/cpu/register_tags.h>
#include <tanukigb/types/types.h>
#include <tanukigb/utility/crtp.h>

#include <type_traits>
#include <utility>

namespace tanukigb {

using opcode_return_type = int;
using opcode_type = byte_t;

// Forward Declare actual Handler
template <opcode_type Opcode>
struct OpcodeHandler;

template <typename E>
class Executor : public Crtp<E, Executor> {
 public:
  enum class RegisterFlags : byte_t {
    Z = (1 << 7),
    N = (1 << 6),
    H = (1 << 5),
    C = (1 << 4)
  };

  Executor() = default;

  int Run();

  // TODO: Trailing return? ->
  // decltype(this->to_underlying().GetRegister<Tag>()) ?

  // Static_assert checking call to same function in underlying
  template <RegisterTag Tag>
  constexpr auto& GetRegister() noexcept(
      noexcept(std::declval<E>().GetRegister<Tag>())) {
    auto& reg = this->to_underlying().GetRegister<Tag>();
    static_assert(
        RegisterType<decltype(reg)>,
        "GetRegister must return a type with constraint RegisterType");

    if constexpr (std::is_base_of_v<register_tags::groups::Reg8Bit, Tag>) {
      static_assert(register_has_at_least_8_bits<decltype(reg)>,
                    "An 8 Bit register must have at least 8 bits.");

    } else if constexpr (std::is_base_of_v<register_tags::groups::Reg16Bit,
                                           Tag>) {
      static_assert(register_has_at_least_16_bits<decltype(reg)>,
                    "A 16 Bit register must have at least 16 bits.");

    } else if constexpr (std::is_base_of_v<register_tags::groups::RegComposite,
                                           Tag>) {
      static_assert(register_has_at_least_16_bits<decltype(reg)>,
                    "A 16 Bit composite register must have at least 16 bits.");

    } else {
      static_assert(false,
                    "Somehow Tag wasn't derived from any of the base classes!");
    }
    return reg;
  }

  template <RegisterTag Tag>
  constexpr const auto& GetRegister() const
      noexcept(noexcept(std::declval<E>().GetRegister<Tag>())) {
    const auto& reg = this->to_underlying().GetRegister<Tag>();
    static_assert(
        RegisterType<decltype(reg)>,
        "GetRegister must return a type with constraint RegisterType");

    if constexpr (std::is_base_of_v<register_tags::groups::Reg8Bit, Tag>) {
      static_assert(register_has_at_least_8_bits<decltype(reg)>,
                    "An 8 Bit register must have at least 8 bits.");

    } else if constexpr (std::is_base_of_v<register_tags::groups::Reg16Bit,
                                           Tag>) {
      static_assert(register_has_at_least_16_bits<decltype(reg)>,
                    "A 16 Bit register must have at least 16 bits.");

    } else if constexpr (std::is_base_of_v<register_tags::groups::RegComposite,
                                           Tag>) {
      static_assert(register_has_at_least_16_bits<decltype(reg)>,
                    "A 16 Bit composite register must have at least 16 bits.");

    } else {
      static_assert(false,
                    "Somehow Tag wasn't derived from any of the base classes!");
    }
    return reg;
  }

  // byte_t MemoryRead(word_t addr) const
  // noexcept(noexcept(this->to_underlying().MemoryRead(addr))) {
  byte_t MemoryRead(word_t addr) const
      noexcept(noexcept(std::declval<E>().MemoryRead(addr))) {
    return this->to_underlying().MemoryRead(addr);
  }

  /* constexpr inline bool IsZFlagSet() const
       noexcept(noexcept(std::declval<E>().GetRegister<Tag>())) {
     return IsFlagSet<RegisterFlags, RegisterFlags::Z>(
         GetRegister<register_tags::F>());
   }
   constexpr inline bool IsNFlagSet() const
       noexcept(noexcept(std::declval<E>().GetRegister<Tag>())) {
     return IsFlagSet<RegisterFlags, RegisterFlags::N>(
         GetRegister<register_tags::F>());
   }
   constexpr inline bool IsHFlagSet() const
       noexcept(noexcept(std::declval<E>().GetRegister<Tag>())) {
     return IsFlagSet<RegisterFlags, RegisterFlags::H>(
         GetRegister<register_tags::F>());
   }
   constexpr inline bool IsCFlagSet() const
       noexcept(noexcept(std::declval<E>().GetRegister<Tag>())) {
     return IsFlagSet<RegisterFlags, RegisterFlags::C>(
         GetRegister<register_tags::F>());
   }*/
 private:
  static constexpr const auto jump_table =
      GenerateJumpTable<opcode_type, OpcodeHandler, opcode_return_type,
                        Executor, 256>();
};

template <typename E>
int Executor<E>::Run() {
  int retcode = 0;
  byte_t opcode;

  auto& PC = GetRegister<register_tags::PC>();
  while (retcode == 0) {
    opcode = MemoryRead(PC);
    PC++;
    retcode = jump_table[opcode](std::forward<decltype(*this)>(*this));
  }
  return retcode;
}

}  // namespace tanukigb

#endif
