#include <tanukigb/cpu/cpu.h>
#include <tanukigb/memory/mmu.h>
#include <tanukigb/types/types.h>

#include <ostream>

// #include <tanukigb/cpu/register_set.h>

namespace tanukigb {

/////////////////////////////////////////////////////////

enum class Flag : byte_t {
  Z = (1 << 7),
  N = (1 << 6),
  H = (1 << 5),
  C = (1 << 4)
};

/*
public:
  // Must be scoped as C and H are also function (register) names. Could call
  // them _Flag but... Must be byte_t so it matches register type Bitmask
  // functions implemented at end of header

  // remove fill later as this wont always be the case

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
*/

///////////////////////////////////////////////////////

class Cpu::CpuImpl {
 public:
  CpuImpl(MMU&& mmu) : mmu_(std::move(mmu)) {};  //, registers_(){};

  int Run();

  /*
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

  */

  /*
  std::ostream& DumpRegisters(std::ostream& os) const {
    return registers_.DumpRegisters(os);
  }

  std::ostream& PrettyDumpRegisters(std::ostream& os) const {
    return registers_.PrettyDumpRegisters(os);
  }
  */

 private:
  template <typename T>
  using OpcodeHandlerFunc = void(T&);

  template <typename T>
  using OpcodeHandlerFuncPtr = void (*)(T&);

  MMU mmu_;
  // RegisterSet registers_;
};

Cpu::Cpu(Pimpl<CpuImpl>&& impl) : impl_(std::move(impl)) {}
Cpu::~Cpu() = default;

Cpu::Cpu(Cpu&&) = default;
Cpu& Cpu::operator=(Cpu&&) = default;

Cpu Cpu::GameboyCpu() { return Cpu(Pimpl<CpuImpl>(MMU::GameboyMMU())); }
Cpu Cpu::ColourGameboyCpu() { return Cpu(MMU::ColourGameboyMMU()); }
/*

int Cpu::Run() { return impl_->Run(); }

std::ostream& Cpu::DumpRegisters(std::ostream& os) const {
  return impl_->DumpRegisters(os);
}
std::ostream& Cpu::PrettyDumpRegisters(std::ostream& os) const {
  return impl_->PrettyDumpRegisters(os);
}


int Cpu::CpuImpl::Run() {
  while (true) {
    byte_t opcode = mmu_.Read(registers_.PC());
    registers_.PC()++;

    switch (opcode) {
      case 0x31:
        // Todo: after MMU add helper as the postfix++ is mucky.
        registers_.SP() =
            mmu_.Read(registers_.PC()++) | mmu_.Read(registers_.PC()++) << 8;
        // registers_.PC() += 2;
        break;

      case 0xAF:
        // XOR's A with A (i.e. zeros it) we will cheat and just do that untill
        // we write the inner functions later
        registers_.A() = 0x00;
        registers_.SetFlags(RegisterSet::Flag::Z);
        registers_.ClearFlags(RegisterSet::Flag::N | RegisterSet::Flag::H |
                              RegisterSet::Flag::C);
        break;
      default:
        return opcode;
    }
  }

  return 0;
}
*/

}  // namespace tanukigb