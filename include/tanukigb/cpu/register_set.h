#ifndef __TANUKIGB_CPU_REGISTER_SET_H__
#define __TANUKIGB_CPU_REGISTER_SET_H__

#include <tanukigb/types/types.h>

#include <array>
#include <format>
#include <ostream>

namespace tanukigb {

// So RegisterSet will be a class specific to the game boy (remember you're not
// making a library) however Register will be property-esque

class RegisterSet {
 private:
  constexpr static int kRegisterSetBufferBytes = 12;

  using buffer_type = std::array<unsigned char, kRegisterSetBufferBytes>;
  alignas(word_t) buffer_type register_buffer_;

 public:
  RegisterSet() = default;

  static RegisterSet InitalizedRegisterSet(unsigned char init = 0x00) {
    RegisterSet rs{};
    rs.register_buffer_.fill(init);
    return rs;
  }

  friend std::ostream& operator<<(std::ostream& os, const RegisterSet& obj) {
    os << "0x";
    for (const unsigned char& b : obj.register_buffer_) {
      os << std::format("{:02x}", b);
    }
    return os;
  }

  std::ostream& PrettyDumpRegisters(std::ostream& os) const;
};

}  // namespace tanukigb
#endif