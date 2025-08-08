#ifndef __TANUKIGB_CPU_EXECUTOR_H__
#define __TANUKIGB_CPU_EXECUTOR_H__

#include <tanukigb/cpu/opcode_handler.h>
#include <tanukigb/cpu/register/register.h>
#include <tanukigb/cpu/register/register_type_traits.h>
#include <tanukigb/cpu/register_tags.h>
#include <tanukigb/types/types.h>
#include <tanukigb/utility/crtp.h>

#include <type_traits>
#include <utility>

namespace tanukigb {

// Trying out noexcept operator (inside specifier)
template <typename E>
class Executor : public Crtp<E, Executor> {
 public:
  enum class RegisterFlags : byte_t {
    Z = (1 << 7),
    N = (1 << 6),
    H = (1 << 5),
    C = (1 << 4)
  };

 protected:
  static constexpr const auto jump_table = GenerateJumpTable<Executor, 255>();

 public:
  Executor() = default;

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

 private:
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
};

}  // namespace tanukigb

#endif
