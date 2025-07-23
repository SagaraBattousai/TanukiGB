#include <tanukigb/cpu/cpu.h>
#include <tanukigb/memory/bootrom.h>
#include <tanukigb/types/types.h>
#include <tanukigb/utility/property.h>
#include <tanukigb/cpu/register_set.h>

#include <array>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <format>
#include <functional>
#include <iostream>
#include <memory>
#include <tuple>
#include <type_traits>

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

// using MFP = int&(Foo::*)(int&& v);

int main() {
  tanukigb::Cpu cpu = tanukigb::Cpu::GameboyCpu();
  // RunGameBoy(cpu);
  // cpu.PrettyDumpRegisters(std::cout);

  auto rs = tanukigb::RegisterSet<12, alignof(int)>::InitalizedRegisterSet();

  std::cout << rs << std::endl;

  rs.Get<unsigned char>(3) = 0xAB;
  rs.Get<unsigned char>(4) = 0xCD;

  std::cout << rs << std::endl;

  short x = rs.GetComposite<short, unsigned char>(3); //0); //3,4); //, 4);

  std::cout << std::hex << "0x" << x << std::endl;

  return 0;
}
