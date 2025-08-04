#include <tanukigb/cpu/cpu.h>
#include <tanukigb/cpu/opcode_handler.h>
#include <tanukigb/cpu/register_set.h>
#include <tanukigb/memory/mmu.h>
#include <tanukigb/types/types.h>
#include <tanukigb/utility/enum_utils.h>

#include <array>
#include <ostream>
#include <utility>

namespace tanukigb {

class Cpu::CpuImpl {
 public:
  enum class RegisterFlags : byte_t {
    Z = (1 << 7),
    N = (1 << 6),
    H = (1 << 5),
    C = (1 << 4)
  };

  CpuImpl(MMU&& mmu) : mmu_{std::move(mmu)}, registers_{} {};

  int Run();

  std::ostream& PrintRegisters(std::ostream& os) const {
    return (os << registers_ << std::endl);
  }

  std::ostream& PrettyPrintRegisters(std::ostream& os) const {
    return tanukigb::PrettyPrintRegisters(os, registers_);
  }

  byte_t MemoryRead(word_t addr) const { return mmu_.Read(addr); }

  template <RegisterTag Tag>
  constexpr decltype(auto) GetRegister() noexcept {
    return registers_.template GetRegister<Tag>();
  }

  template <RegisterTag Tag>
  constexpr auto& GetRegister() const noexcept {
    return registers_.GetRegister<Tag>();
  }

 private:  // Most functions can be private since this is a Pimpl's Impl
  bool IsZFlagSet() const noexcept {
    return IsFlagSet<RegisterFlags, RegisterFlags::Z>(
        GetRegister<register_tags::F>());
  }
  bool IsNFlagSet() const noexcept {
    return IsFlagSet<RegisterFlags, RegisterFlags::N>(
        GetRegister<register_tags::F>());
  }
  bool IsHFlagSet() const noexcept {
    return IsFlagSet<RegisterFlags, RegisterFlags::H>(
        GetRegister<register_tags::F>());
  }
  bool IsCFlagSet() const noexcept {
    return IsFlagSet<RegisterFlags, RegisterFlags::C>(
        GetRegister<register_tags::F>());
  }

  template <typename T>
  using OpcodeHandlerFunc = void(T&);

  template <typename T>
  using OpcodeHandlerFuncPtr = void (*)(T&);

 /*static constexpr auto jump_table_ =
      []() constexpr noexcept {
    return GenerateJumpTable<CpuImpl, 255>();
  }();*/

  MMU mmu_;
  RegisterSet registers_;
};

Cpu::Cpu(Pimpl<CpuImpl>&& impl) : impl_(std::move(impl)) {}
Cpu::~Cpu() = default;

Cpu::Cpu(Cpu&&) = default;
Cpu& Cpu::operator=(Cpu&&) = default;

Cpu Cpu::GameboyCpu() { return Cpu(Pimpl<CpuImpl>(MMU::GameboyMMU())); }
Cpu Cpu::ColourGameboyCpu() {
  return Cpu(Pimpl<CpuImpl>(MMU::ColourGameboyMMU()));
}

int Cpu::Run() { return impl_->Run(); }

inline std::ostream& Cpu::PrintRegisters(std::ostream& os) const {
  return impl_->PrintRegisters(os);
}

inline std::ostream& Cpu::PrettyPrintRegisters(std::ostream& os) const {
  return impl_->PrettyPrintRegisters(os);
}

// TODO:
int Cpu::CpuImpl::Run() {
  int retcode = 0;
  auto& PC = GetRegister<register_tags::PC>();
  while (true) {
    byte_t opcode = mmu_.Read(PC);
    PC++;

    retcode = 7;
    //jump_table_[opcode](*this);
    if (retcode != 0) {
      break;
    }
  }
  return retcode;
}

// switch (opcode) {
//   case 0x31:
//     // Todo: after MMU add helper as the postfix++ is mucky.
//     registers_.SP = mmu_.Read(registers_.PC++) |
//     mmu_.Read(registers_.PC++)
//                                                      << 8;
//     // registers_.PC() += 2;
//     break;

//  case 0xAF:
//    // Same as ClearRegister(registers_.A) but VV is technically what the
//    // Opcode calls for:
//    // TODO: make nicer
//    registers_.A ^= registers_.A;

//    SetFlags<RegisterFlags, RegisterFlags::Z>(registers_.F);

//    // While clearing all flags before setting the one above achieves a
//    // similar result, it is technically wrong as it would destroy the
//    lower
//    // (unused) bits.
//    ClearFlags<RegisterFlags, RegisterFlags::N, RegisterFlags::H,
//               RegisterFlags::C>(registers_.F);
//    break;
//  default:
//    return opcode;
//}

}  // namespace tanukigb
