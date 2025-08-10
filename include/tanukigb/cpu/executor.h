#ifndef __TANUKIGB_CPU_EXECUTOR_H__
#define __TANUKIGB_CPU_EXECUTOR_H__

// Okay we'll go the otherway and force Executor to know about Opcodes but
// opcodes only need to know about a conceptual executor.
//

#include <tanukigb/cpu/jump_table.h>
#include <tanukigb/cpu/register/register.h>
#include <tanukigb/cpu/register/register_type_traits.h>
#include <tanukigb/cpu/register_tags.h>
#include <tanukigb/types/types.h>
#include <tanukigb/utility/crtp.h>

#include <tanukigb/cpu/opcode/opcode_handler.h>

#include <type_traits>
#include <utility>

namespace tanukigb {

template <typename Derived>
class Executor : public Crtp<Derived, Executor> {
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
  // decltype(this->as_derived().GetRegister<Tag>()) ?

  // Static_assert checking call to same function in underlying
  template <RegisterTag Tag>
  constexpr auto& GetRegister() noexcept(
      noexcept(std::declval<Derived>().GetRegister<Tag>())) {
    auto& reg = this->as_derived().GetRegister<Tag>();
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
      noexcept(noexcept(std::declval<Derived>().GetRegister<Tag>())) {
    const auto& reg = this->as_derived().GetRegister<Tag>();
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
  // noexcept(noexcept(this->as_derived().MemoryRead(addr))) {
  byte_t MemoryRead(word_t addr) const
      noexcept(noexcept(std::declval<Derived>().MemoryRead(addr))) {
    return this->as_derived().MemoryRead(addr);
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
    retcode = jump_table[opcode](*this);
  }
  return retcode;
}

}  // namespace tanukigb

#endif
