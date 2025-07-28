
#include <tanukigb/cpu/cpu.h>
#include <tanukigb/cpu/register_set.h>
#include <tanukigb/types/types.h>

#include <array>
#include <bit>
#include <chrono>
#include <cstring>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

using tanukigb::byte_t;
using tanukigb::word_t;

// Could make utility function taking Container that can report size but meh...
// Maybe just for array since chunking (or peaking I cant remember what it was
// called) is one of the "acceptable" uses of reinterpret cast and other types
// may use packing I guess? I need to find a hardcore C++ developer to learn
// about why reinterpret_cast is considered evil
template <typename T, std::size_t Count>
std::ostream& operator<<(std::ostream& os, const std::array<T, Count>& arr) {
  os << "0x";
  const unsigned char* const ptr =
      reinterpret_cast<const unsigned char* const>(arr.data());
  for (auto i = 0; i < Count; ++i) {
    os << std::format("{:02x}", ptr[i]);
  }
  return os;
}

/*
void RunGameBoy(tanukigb::Cpu& cpu) {
  int ret = cpu.Run();

  if (ret != 0) {
    std::cout << std::format("Unknown Opcode: {:#02x}\n", ret);
    cpu.DumpRegisters(std::cout);
  }
}
*/

/*
uint16_t read16(std::size_t index) const {
  assert(index + 1 < kSize);
  std::array<Byte, 2> temp = {data_[index], data_[index + 1]};
  return std::bit_cast<uint16_t>(temp);  // Little-endian assumed
}

// Write a 16-bit value across two adjacent 8-bit registers
void write16(std::size_t index, uint16_t value) {
  assert(index + 1 < kSize);
  std::array<Byte, 2> temp = std::bit_cast<std::array<Byte, 2>>(value);
  data_[index] = temp[0];
  data_[index + 1] = temp[1];
}
*/

int main() {
  tanukigb::Cpu cpu = tanukigb::Cpu::GameboyCpu();
  // RunGameBoy(cpu);
  // cpu.PrettyDumpRegisters(std::cout);

  tanukigb::RegisterSet rs{};

  rs.A = 7;
  rs.B = 8;
  rs.C = 7;

  bool i = rs.A == rs.B;

  return 0;
}