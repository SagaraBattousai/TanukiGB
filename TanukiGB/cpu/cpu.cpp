
#include <tanukigb/cpu/cpu.h>

#include <cstdint>

namespace tanukigb {

namespace {
constexpr int kRegisterBufferSize = 12;  // 12 * 8 = 96

enum RegisterSet {
  A = 0,
  F = 1,
  B = 2,
  C = 3,
  D = 4,
  E = 5,
  H = 6,
  L = 7,
  SP = 8,
  PC = 10,
  AF = 0,
  BC = 2,
  DE = 4,
  HL = 6
};

}  // namespace

// NOTE: The requirement on std::uint8_t is almost always fine but...
// technically it is possible for that not to be supported so ...
// Could use uint32_t as thats more ... universal but still....
// No member functions as i'm not sure if that messes it up....
//
// Must be defined above all the usages
//
struct Cpu::cpu_registers {
  // fast garuntee's to be at least 8bits (and should "always" exist :P)
  std::uint_fast8_t register_buffer[kRegisterBufferSize];
  // Register format =
  //                   A(8bit),F(8bit), (can be accessed as 16bit)
  //                   B(8bit),C(8bit), (can be accessed as 16bit)
  //                   D(8bit),E(8bit), (can be accessed as 16bit)
  //                   H(8bit),L(8bit), (can be accessed as 16bit)
  //                   SP(16bit),PC(16bit)
};

Cpu::Cpu(Bootrom&& bootrom)
    : registers_(std::make_unique<cpu_registers>()),
      bootrom_(std::move(bootrom)) {}

Cpu::~Cpu() = default;

void Cpu::Run() { 
  byte_t opcode = bootrom_[this->PC()]; 
  this->PC(this->PC() + 1);
  //Yeah this register interface needs work, its a bit rubbish at the moment
}

// TODO: Check std::move etc although by value may fix it, my goodness my C++ is
// rusty!
//  Definitly need to improve all this code
byte_t Cpu::A() const { return Read8BitRegister(RegisterSet::A); }
void Cpu::A(byte_t value) { Write8BitRegister(RegisterSet::A, value); }

byte_t Cpu::F() const { return Read8BitRegister(RegisterSet::F); }
void Cpu::F(byte_t value) { Write8BitRegister(RegisterSet::F, value); }

byte_t Cpu::B() const { return Read8BitRegister(RegisterSet::B); }
void Cpu::B(byte_t value) { Write8BitRegister(RegisterSet::B, value); }

byte_t Cpu::C() const { return Read8BitRegister(RegisterSet::C); }
void Cpu::C(byte_t value) { Write8BitRegister(RegisterSet::C, value); }

byte_t Cpu::D() const { return Read8BitRegister(RegisterSet::D); }
void Cpu::D(byte_t value) { Write8BitRegister(RegisterSet::D, value); }

byte_t Cpu::E() const { return Read8BitRegister(RegisterSet::E); }
void Cpu::E(byte_t value) { Write8BitRegister(RegisterSet::E, value); }

byte_t Cpu::H() const { return Read8BitRegister(RegisterSet::H); }
void Cpu::H(byte_t value) { Write8BitRegister(RegisterSet::H, value); }

byte_t Cpu::L() const { return Read8BitRegister(RegisterSet::L); }
void Cpu::L(byte_t value) { Write8BitRegister(RegisterSet::L, value); }

word_t Cpu::SP() const { return Read16BitRegister(RegisterSet::SP); }
void Cpu::SP(word_t value) { Write16BitRegister(RegisterSet::SP, value); }

word_t Cpu::PC() const { return Read16BitRegister(RegisterSet::PC); }
void Cpu::PC(word_t value) { Write16BitRegister(RegisterSet::PC, value); }

word_t Cpu::AF() const { return Read16BitRegister(RegisterSet::AF); }
void Cpu::AF(word_t value) { Write16BitRegister(RegisterSet::AF, value); }

word_t Cpu::BC() const { return Read16BitRegister(RegisterSet::BC); }
void Cpu::BC(word_t value) { Write16BitRegister(RegisterSet::BC, value); }

word_t Cpu::DE() const { return Read16BitRegister(RegisterSet::DE); }
void Cpu::DE(word_t value) { Write16BitRegister(RegisterSet::DE, value); }

word_t Cpu::HL() const { return Read16BitRegister(RegisterSet::HL); }
void Cpu::HL(word_t value) { Write16BitRegister(RegisterSet::HL, value); }

// byte_t Cpu::ZeroFlag() const {  }
// byte_t Cpu::SubtractFlag() const {
//
// }
// byte_t Cpu::HalfCarryFlag() const {
//
// }
// byte_t Cpu::CarryFlag() const {
//
// }

byte_t Cpu::Read8BitRegister(int memory_offset) const {
  return this->registers_->register_buffer[memory_offset];
}
void Cpu::Write8BitRegister(int memory_offset, byte_t value) {
  this->registers_->register_buffer[memory_offset] = value;
}

word_t Cpu::Read16BitRegister(int memory_offset) const {
  byte_t higher_bits = this->registers_->register_buffer[memory_offset];
  byte_t lower_bits = this->registers_->register_buffer[memory_offset + 1];

  return (word_t)((static_cast<word_t>(higher_bits) << 8) | lower_bits);
}
void Cpu::Write16BitRegister(int memory_offset, word_t value) {
  byte_t higher_bits = static_cast<byte_t>(value >> 8);
  byte_t lower_bits = static_cast<byte_t>(value & 0xFF);

  this->registers_->register_buffer[memory_offset] = higher_bits;
  this->registers_->register_buffer[memory_offset + 1] = lower_bits;
}

std::ostream& Cpu::DumpRegisters(std::ostream& os) const {
  os << std::hex << "A: " << (unsigned)this->A()
     << "\tF: " << (unsigned)this->F() << std::endl
     << "B: " << (unsigned)this->B() << "\tC: " << (unsigned)this->C()
     << std::endl
     << "D: " << (unsigned)this->D() << "\tE: " << (unsigned)this->E()
     << std::endl
     << "H: " << (unsigned)this->H() << "\tL: " << (unsigned)this->L()
     << std::endl
     << "SP: " << (unsigned)this->SP() << std::endl
     << "PC: " << (unsigned)this->PC() << std::endl;

  return os;
}

}  // namespace tanukigb