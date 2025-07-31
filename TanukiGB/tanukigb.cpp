
#include <tanukigb/cpu/cpu.h>
#include <tanukigb/cpu/register_set.h>
#include <tanukigb/types/types.h>
#include <tanukigb/cpu/opcode_handler.h>

#include <array>
#include <bit>
#include <format>
#include <cstring>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

using tanukigb::byte_t;
using tanukigb::word_t;

// Could make utility function taking Container that can report size but meh...
// Maybe just for array
// since chunking (or peaking I cant remember what it was
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

static void RunGameBoy(tanukigb::Cpu& cpu) {
  int ret = cpu.Run();

  if (ret != 0) {
    std::cout << std::format("Unknown Opcode: {:#02x}\n", ret);
    cpu.PrintRegisters(std::cout) << std::endl;
  }
}

int main() {
  tanukigb::Cpu cpu = tanukigb::Cpu::GameboyCpu();
  RunGameBoy(cpu);
  cpu.PrettyPrintRegisters(std::cout);

  std::array<tanukigb::OpcodeExecutionFunctionPtr<int>, 1> arr = {
    &tanukigb::OpcodeHandler<0x31>::template execute<int>
  };

  int x = 7;
  arr[0](x);

  return 0;
}