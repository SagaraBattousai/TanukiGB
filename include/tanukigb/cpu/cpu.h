#ifndef __TANUKIGB_CPU_CPU_H__
#define __TANUKIGB_CPU_CPU_H__

#include <_TanukiGB_config.h>
#include <tanukigb/cpu/executor.h>
#include <tanukigb/cpu/opcode_handler.h>
#include <tanukigb/cpu/register/register.h>
#include <tanukigb/cpu/register/register_set.h>
#include <tanukigb/memory/mmu.h>

#include <ostream>
#include <utility>

namespace tanukigb {

class Cpu : public Executor<Cpu> {
 public:
  static TANUKIGB_EXPORT Cpu GameboyCpu() { return Cpu(MMU::GameboyMMU()); }

  static TANUKIGB_EXPORT Cpu ColourGameboyCpu() {
    return Cpu(MMU::ColourGameboyMMU());
  }

  TANUKIGB_EXPORT ~Cpu() = default;

  Cpu(Cpu&&) = delete;
  Cpu& operator=(Cpu&&) = delete;
  Cpu(const Cpu&) = delete;
  Cpu& operator=(const Cpu&) = delete;

  TANUKIGB_EXPORT int Run();

  TANUKIGB_EXPORT std::ostream& PrintRegisters(std::ostream& os) const {
    return (os << registers_ << std::endl);
  }

  TANUKIGB_EXPORT std::ostream& PrettyPrintRegisters(std::ostream& os) const {
    return tanukigb::PrettyPrintRegisters(os, registers_);
  }

  TANUKIGB_EXPORT byte_t MemoryRead(word_t addr) const noexcept {
    return mmu_.Read(addr);
  }

  template <RegisterTag Tag>
  constexpr decltype(auto) GetRegister() noexcept {
    return registers_.template GetRegister<Tag>();
  }

  template <RegisterTag Tag>
  constexpr auto& GetRegister() const noexcept {
    return registers_.GetRegister<Tag>();
  }

 private:
  Cpu(MMU&& mmu) : mmu_{std::move(mmu)}, registers_{} {};

  MMU mmu_;
  RegisterSet registers_;
};

}  // namespace tanukigb

#endif
