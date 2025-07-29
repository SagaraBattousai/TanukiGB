#include <ostream>

#include <tanukigb/cpu/cpu.h>
#include <tanukigb/memory/mmu.h>
#include <tanukigb/types/types.h>
#include <tanukigb/cpu/register_set.h>

namespace tanukigb {

/////////////////////////////////////////////////////////

/*
enum class Flag : byte_t {
  Z = (1 << 7),
  N = (1 << 6),
  H = (1 << 5),
  C = (1 << 4)
};



  byte_t GetFlags() const noexcept { return F(); }
  void SetFlags(Flag flags) noexcept { F() |= flags; }
  void ClearFlags(Flag flags) noexcept { F() &= ~flags; }
  // void ToggleFlags(Flag flags) noexcept { F() ^= flags; }

  bool IsZFlagSet() const noexcept { return (F() & Flag::Z) != 0; }
  bool IsNFlagSet() const noexcept { return (F() & Flag::N) != 0; }
  bool IsHFlagSet() const noexcept { return (F() & Flag::H) != 0; }
  bool IsCFlagSet() const noexcept { return (F() & Flag::C) != 0; }

 */

class Cpu::CpuImpl {
 public:
  CpuImpl(MMU&& mmu) : mmu_(std::move(mmu)) {};  //, registers_(){};

  int Run();

 /*
  byte_t GetFlags() const noexcept { return F(); }
  void SetFlags(Flag flags) noexcept { F() |= flags; }
  void ClearFlags(Flag flags) noexcept { F() &= ~flags; }
  // void ToggleFlags(Flag flags) noexcept { F() ^= flags; }

  bool IsZFlagSet() const noexcept { return (F() & Flag::Z) != 0; }
  bool IsNFlagSet() const noexcept { return (F() & Flag::N) != 0; }
  bool IsHFlagSet() const noexcept { return (F() & Flag::H) != 0; }
  bool IsCFlagSet() const noexcept { return (F() & Flag::C) != 0; }

  */

  
  inline std::ostream& PrintRegisters(std::ostream& os) const {
    return (os << registers_ << std::endl);
  }

  inline std::ostream& PrettyPrintRegisters(std::ostream& os) const {
    return tanukigb::PrettyPrintRegisters(os, registers_);
  }

 private:
  template <typename T>
  using OpcodeHandlerFunc = void(T&);

  template <typename T>
  using OpcodeHandlerFuncPtr = void (*)(T&);

  MMU mmu_;
  RegisterSet registers_;
};

Cpu::Cpu(Pimpl<CpuImpl>&& impl) : impl_(std::move(impl)) {}
Cpu::~Cpu() = default;

Cpu::Cpu(Cpu&&) = default;
Cpu& Cpu::operator=(Cpu&&) = default;

Cpu Cpu::GameboyCpu() { return Cpu(Pimpl<CpuImpl>(MMU::GameboyMMU())); }
Cpu Cpu::ColourGameboyCpu() { return Cpu(MMU::ColourGameboyMMU()); }

int Cpu::Run() { return impl_->Run(); }

inline std::ostream& Cpu::PrintRegisters(std::ostream& os) const {
  return impl_->PrintRegisters(os);
}

inline std::ostream& Cpu::PrettyPrintRegisters(std::ostream& os) const {
  return impl_->PrettyPrintRegisters(os);
}


int Cpu::CpuImpl::Run() {
  while (true) {
    byte_t opcode = mmu_.Read(static_cast<word_t>(registers_.PC));
    registers_.PC++;

    switch (opcode) {
      case 0x31:
        // Todo: after MMU add helper as the postfix++ is mucky.
        registers_.SP =
            mmu_.Read(registers_.PC++) | mmu_.Read(registers_.PC++) << 8;
        // registers_.PC() += 2;
        break;

      case 0xAF:
        // XOR's A with A (i.e. zeros it) we will cheat and just do that untill
        // we write the inner functions later
        registers_.A = 0x00;
        registers_.F = 0b1000'0000;
        //registers_.SetFlags(RegisterSet::Flag::Z);
        //registers_.ClearFlags(RegisterSet::Flag::N | RegisterSet::Flag::H |
        //                      RegisterSet::Flag::C);
        break;
      default:
        return opcode;
    }
  }

  return 0;
}

}  // namespace tanukigb