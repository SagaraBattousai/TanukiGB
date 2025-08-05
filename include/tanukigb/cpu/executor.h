#ifndef __TANUKIGB_CPU_EXECUTOR_H__
#define __TANUKIGB_CPU_EXECUTOR_H__

#include <tanukigb/cpu/opcode_handler.h>
#include <tanukigb/cpu/register/register.h>
#include <tanukigb/cpu/register_tags.h>
#include <tanukigb/types/types.h>
#include <tanukigb/utility/crtp.h>

#include <type_traits>

namespace tanukigb {

template <typename E>
class Executor : public Crtp<E, Executor> {
 protected:
  static constexpr auto jump_table = GenerateJumpTable<Executor, 255>();

 public:
  Executor() = default;

  template <RegisterTag Tag>
  constexpr auto& GetRegister() {
    auto& reg = this->to_underlying().GetRegister<Tag>();
    if constexpr (std::is_base_of_v<register_tags::groups::Reg8Bit, Tag>) {
      static_assert(RegisterLike<decltype(reg), byte_t>);
    } else if constexpr (std::is_base_of_v<register_tags::groups::Reg16Bit,
                                           Tag>) {
      static_assert(RegisterLike<decltype(reg), word_t>);
    } else if constexpr (std::is_base_of_v<register_tags::groups::RegComposite,
                                           Tag>) {
      static_assert(RegisterLike<decltype(reg), word_t>);
    } else {
      static_assert(false,
                    "Somehow Tag wasnt derived from any of the base classes!");
    }
    return reg;
  }

  template <RegisterTag Tag>
  constexpr const auto& GetRegister() const {
    auto& reg = this->to_underlying().GetRegister<Tag>();
    if constexpr (std::is_base_of_v<register_tags::groups::Reg8Bit, Tag>) {
      static_assert(RegisterLike<decltype(reg), byte_t>);
    } else if constexpr (std::is_base_of_v<register_tags::groups::Reg16Bit,
                                           Tag>) {
      static_assert(RegisterLike<decltype(reg), word_t>);
    } else if constexpr (std::is_base_of_v<register_tags::groups::RegComposite,
                                           Tag>) {
      static_assert(RegisterLike<decltype(reg), word_t>);
    } else {
      static_assert(false,
                    "Somehow Tag wasnt derived from any of the base classes!");
    }
    return reg;
  }

  byte_t MemoryRead(word_t addr) const noexcept {
    return this->to_underlying().MemoryRead(addr);
  }
};

}  // namespace tanukigb

#endif
