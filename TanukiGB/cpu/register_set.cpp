
#include <tanukigb/cpu/register_set.h>

#include <format>
#include <type_traits>

namespace tanukigb {

namespace {
template <typename E>  // requires scoped enum if we upgrade to C++ 23
constexpr auto toUnderlying(E enumurator) noexcept {
  return static_cast<std::underlying_type_t<E>>(enumurator);
}
}  // namespace

RegisterSet::RegisterSet() : raw_register_buffer_() {
  raw_register_buffer_.fill(0x00);
}

byte_t RegisterSet::operator[](R8Bit register_name) const {
  auto ptr = reinterpret_cast<const byte_t*>(this->raw_register_buffer_.data());
  return ptr[toUnderlying<R8Bit>(register_name)];
}

byte_t& RegisterSet::operator[](R8Bit register_name) {
  auto ptr = reinterpret_cast<byte_t*>(this->raw_register_buffer_.data());
  return ptr[toUnderlying<R8Bit>(register_name)];
}

word_t RegisterSet::operator[](R16Bit register_name) const {
  auto ptr = reinterpret_cast<const word_t*>(this->raw_register_buffer_.data());
  return ptr[toUnderlying<R16Bit>(register_name)];
}

word_t& RegisterSet::operator[](R16Bit register_name) {
  auto ptr = reinterpret_cast<word_t*>(this->raw_register_buffer_.data());
  return ptr[toUnderlying<R16Bit>(register_name)];
}

word_t RegisterSet::operator[](RComposite register_name) const {
  auto ptr = reinterpret_cast<const byte_t*>(this->raw_register_buffer_.data());
  auto hi_ptr = ptr + toUnderlying<RComposite>(register_name);
  return (static_cast<word_t>(*hi_ptr) << 8) | *(hi_ptr + 1);
}

void RegisterSet::SetComposite(RComposite register_name, word_t value) {
  auto ptr = reinterpret_cast<byte_t*>(this->raw_register_buffer_.data());
  auto hi_ptr = ptr + toUnderlying<RComposite>(register_name);

  hi_ptr[0] = static_cast<byte_t>((value >> 8) & 0xFF);
  hi_ptr[1] = static_cast<byte_t>(value & 0xFF);
}

std::ostream& RegisterSet::PrettyDumpRegisters(std::ostream& os) const {
  os << "A: " << std::format("{:02x}", this->operator[](R8Bit::A))
     << "\tF: " << std::format("{:02x}", this->operator[](R8Bit::F))
     << "\nB: " << std::format("{:02x}", this->operator[](R8Bit::B))
     << "\tC: " << std::format("{:02x}", this->operator[](R8Bit::C))
     << "\nD: " << std::format("{:02x}", this->operator[](R8Bit::D))
     << "\tE: " << std::format("{:02x}", this->operator[](R8Bit::E))
     << "\nH: " << std::format("{:02x}", this->operator[](R8Bit::H))
     << "\tL: " << std::format("{:02x}", this->operator[](R8Bit::L))
     << "\nSP: " << std::format("{:04x}", this->operator[](R16Bit::SP))
     << "\nPC: " << std::format("{:04x}", this->operator[](R16Bit::PC))
     << std::endl;

  return os;
}

std::ostream& RegisterSet::DumpRegisters(std::ostream& os) const {
  os << "Register Buffer Dump:\n\t0x";

  const unsigned char* mem_ptr =
      reinterpret_cast<const unsigned char*>(this->raw_register_buffer_.data());

  for (int i = 0; i < RegisterSet::kRegistersByteSize; ++i) {
    os << std::format("{:02x}", mem_ptr[i]);
  }

  os << std::endl;

  return os;
}
}  // namespace tanukigb