
#include <type_traits>

#include <tanukigb/cpu/register_set.h>

namespace tanukigb {

RegisterSet::RegisterSet() : raw_register_buffer_() {
  raw_register_buffer_.fill(0x00);
}

word_t RegisterSet::Get(Register16Bit register_name) const {
  const word_t* ptr =
      reinterpret_cast<const word_t*>(this->raw_register_buffer_.data());
  return ptr[static_cast<std::underlying_type_t<Register16Bit>>(register_name)];
  // Hopefully this will work with offset changes. I could use a template but technically less safe
  // as the wrong register type could be passed in!
}

word_t& RegisterSet::Get(Register16Bit register_name) {
  word_t* ptr =
      reinterpret_cast<word_t*>(this->raw_register_buffer_.data());
  return ptr[static_cast<std::underlying_type_t<Register16Bit>>(register_name)];
}

std::ostream& RegisterSet::PrettyDumpRegisters(std::ostream& os) const {
  std::ios_base::fmtflags original_flags = os.flags();

  os << std::hex << "A: 0x" << (unsigned)Get(Register8Bit::A) << "\tF: 0x"
     << (unsigned)Get(Register8Bit::F) << "\nB: 0x"
     << (unsigned)Get(Register8Bit::B) << "\tC: 0x"
     << (unsigned)Get(Register8Bit::C) << "\nD: 0x"
     << (unsigned)Get(Register8Bit::D) << "\tE: 0x"
     << (unsigned)Get(Register8Bit::E) << "\nH: 0x"
     << (unsigned)Get(Register8Bit::H) << "\tL: 0x"
     << (unsigned)Get(Register8Bit::L) << "\nSP: 0x"
     << (unsigned)Get(Register16Bit::SP) << "\nPC: 0x"
     << (unsigned)Get(Register16Bit::PC) << std::endl;

  // Restore flags
  os.flags(original_flags);

  return os;
}

std::ostream& RegisterSet::DumpRegisters(std::ostream& os) const {
  std::ios_base::fmtflags original_flags = os.flags();

  // Since in hex does it matter if it's signed or unsigned? thats why unary +
  // is probably the cleaverest option
  os << std::hex << "Register Buffer Dump:\n\t0x";

  // Cast to unsigned char to avoid endinaness stuff
  const unsigned char* mem_ptr =
      reinterpret_cast<const unsigned char*>(this->raw_register_buffer_.data());

  for (int i = 0; i < RegisterSet::kRawRegisterBufferSize; ++i) {
    unsigned char byte = mem_ptr[i];
    if (byte < 0x10) {
      os << 0U;
    }
    os << (unsigned)mem_ptr[i];
  }

  os << std::endl;

  // Restore flags
  os.flags(original_flags);

  return os;
}
}  // namespace tanukigb