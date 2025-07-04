
#include <tanukigb/cpu/cpu.h>

#include <cstdint>

namespace tanukigb {

Cpu::Cpu(Bootrom&& bootrom) : bootrom_(std::move(bootrom)) {}

int Cpu::Run() {
  while (true) {
    byte_t opcode = bootrom_[static_cast<word_t>(PC_)];
    PC_++;

    switch (opcode) {
      case 0x31:
        SP_ = bootrom_[static_cast<word_t>(PC_)] |
              static_cast<word_t>(bootrom_[static_cast<word_t>(PC_) + 1]) << 8;
        PC_ += 2;
        break;
      default:
        return opcode;
    }
  }

  return 0;
}

std::ostream& Cpu::DumpRegisters(std::ostream& os) const {
  os << "A: " << A_ << "\tF: " << F_ << "\nB: " << B_ << "\tC: " << C_
     << "\nD: " << D_ << "\tE: " << E_ << "\nH: " << H_ << "\tL: " << L_
     << "\nSP: " << SP_ << "\nPC: " << PC_ << std::endl;

  return os;
}

/*
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
*/

}  // namespace tanukigb