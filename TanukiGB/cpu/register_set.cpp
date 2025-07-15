
#include <tanukigb/cpu/register_set.h>

#include <cstdint>
#include <format>
#include <type_traits>

namespace tanukigb {

namespace {

template <typename E>  // requires is_scoped_enum_t<E> // if we switch to c++23
constexpr auto ToUnderlying(E enumueration) {
  return static_cast<std::underlying_type_t<E>>(enumueration);
}

constexpr byte_t kByteMask = 0xFF;
constexpr byte_t kByteShift =
    8;  // Not using CHAR_BIT as could be different on a 9bit computer ....
}  // namespace

enum class RegisterSet::R8Bit : int_fast8_t {
  A = 0,
  F = 1,
  B = 2,
  C = 3,
  D = 4,
  E = 5,
  H = 6,
  L = 7
};
enum class RegisterSet::R16Bit : std::underlying_type_t<RegisterSet::R8Bit> {
  SP = 4,
  PC = 5
};  // Offset in short... bit iffy
enum class RegisterSet::RComposite : std::underlying_type_t<
    RegisterSet::R8Bit> {
  AF = R8Bit::A,
  BC = R8Bit::B,
  DE = R8Bit::D,
  HL = R8Bit::H
};

//RegisterSet::RegisterSet() : raw_register_buffer_() {
//  raw_register_buffer_.fill(0x00);
//}

byte_t RegisterSet::A() const noexcept { return Get8Bit(R8Bit::A); }
byte_t& RegisterSet::A() noexcept { return Get8Bit(R8Bit::A); }

byte_t RegisterSet::F() const noexcept { return Get8Bit(R8Bit::F); }
byte_t& RegisterSet::F() noexcept { return Get8Bit(R8Bit::F); }

// TODO: Flags

byte_t RegisterSet::B() const noexcept { return Get8Bit(R8Bit::B); }
byte_t& RegisterSet::B() noexcept { return Get8Bit(R8Bit::B); }

byte_t RegisterSet::C() const noexcept { return Get8Bit(R8Bit::C); }
byte_t& RegisterSet::C() noexcept { return Get8Bit(R8Bit::C); }

byte_t RegisterSet::D() const noexcept { return Get8Bit(R8Bit::D); }
byte_t& RegisterSet::D() noexcept { return Get8Bit(R8Bit::D); }

byte_t RegisterSet::E() const noexcept { return Get8Bit(R8Bit::E); }
byte_t& RegisterSet::E() noexcept { return Get8Bit(R8Bit::E); }

byte_t RegisterSet::H() const noexcept { return Get8Bit(R8Bit::H); }
byte_t& RegisterSet::H() noexcept { return Get8Bit(R8Bit::H); }

byte_t RegisterSet::L() const noexcept { return Get8Bit(R8Bit::L); }
byte_t& RegisterSet::L() noexcept { return Get8Bit(R8Bit::L); }

word_t RegisterSet::SP() const noexcept { return Get16Bit(R16Bit::SP); }
word_t& RegisterSet::SP() noexcept { return Get16Bit(R16Bit::SP); }

word_t RegisterSet::PC() const noexcept { return Get16Bit(R16Bit::PC); }
word_t& RegisterSet::PC() noexcept { return Get16Bit(R16Bit::PC); }

word_t RegisterSet::AF() const noexcept { return GetComposite(RComposite::AF); }
void RegisterSet::SetAF(word_t value) noexcept {
  return SetComposite(RComposite::AF, value);
}

word_t RegisterSet::BC() const noexcept { return GetComposite(RComposite::BC); }
void RegisterSet::SetBC(word_t value) noexcept {
  return SetComposite(RComposite::BC, value);
}

word_t RegisterSet::DE() const noexcept { return GetComposite(RComposite::DE); }
void RegisterSet::SetDE(word_t value) noexcept {
  return SetComposite(RComposite::DE, value);
}

word_t RegisterSet::HL() const noexcept { return GetComposite(RComposite::HL); }
void RegisterSet::SetHL(word_t value) noexcept {
  return SetComposite(RComposite::HL, value);
}

byte_t RegisterSet::Get8Bit(R8Bit offset) const noexcept {
  auto ptr = reinterpret_cast<const byte_t*>(this->raw_register_buffer_.data());
  return ptr[ToUnderlying(offset)];
}
byte_t& RegisterSet::Get8Bit(R8Bit offset) noexcept {
  auto ptr = reinterpret_cast<byte_t*>(this->raw_register_buffer_.data());
  return ptr[ToUnderlying(offset)];
}

word_t RegisterSet::Get16Bit(R16Bit offset) const noexcept {
  auto ptr = reinterpret_cast<const word_t*>(this->raw_register_buffer_.data());
  return ptr[ToUnderlying(offset)];
}

word_t& RegisterSet::Get16Bit(R16Bit offset) noexcept {
  auto ptr = reinterpret_cast<word_t*>(this->raw_register_buffer_.data());
  return ptr[ToUnderlying(offset)];
}

word_t RegisterSet::GetComposite(RComposite offset) const noexcept {
  auto ptr = reinterpret_cast<const byte_t*>(this->raw_register_buffer_.data());
  const byte_t* hi_ptr = ptr + ToUnderlying(offset);
  return (static_cast<word_t>(*hi_ptr) << kByteShift) | hi_ptr[1];
}
void RegisterSet::SetComposite(RComposite offset, word_t value) noexcept {
  auto ptr = reinterpret_cast<byte_t*>(this->raw_register_buffer_.data());
  byte_t* hi_ptr = ptr + ToUnderlying(offset);

  hi_ptr[0] = static_cast<byte_t>((value >> kByteShift) & kByteMask);
  hi_ptr[1] = static_cast<byte_t>(value & kByteMask);
}

std::ostream& RegisterSet::PrettyDumpRegisters(std::ostream& os) const {
  os << "A: " << std::format("{:02x}", this->A())
     << "\tF: " << std::format("{:02x}", this->F())
     << "\nB: " << std::format("{:02x}", this->B())
     << "\tC: " << std::format("{:02x}", this->C())
     << "\nD: " << std::format("{:02x}", this->D())
     << "\tE: " << std::format("{:02x}", this->E())
     << "\nH: " << std::format("{:02x}", this->H())
     << "\tL: " << std::format("{:02x}", this->L())
     << "\nSP: " << std::format("{:04x}", this->SP())
     << "\nPC: " << std::format("{:04x}", this->PC()) << std::endl;

  return os;
}

std::ostream& RegisterSet::DumpRegisters(std::ostream& os) const {
  os << "Register Buffer Dump:\n\t0x";

  for (const byte_t& b : this->raw_register_buffer_ ) {
    os << std::format("{:02x}", b);
  }

  os << std::endl;

  return os;
}
}  // namespace tanukigb