#include <tanukigb/cpu/cpu.h>
#include <tanukigb/memory/addressable.h>
#include <tanukigb/memory/bootrom.h>
#include <tanukigb/types/types.h>

#include <array>
#include <concepts>
#include <cstdint>
#include <format>
#include <iostream>
#include <tuple>

struct Foo {
  Foo() = default;

  //const tanukigb::byte_t& operator[](tanukigb::word_t) const { return val; }
  tanukigb::byte_t& operator[](tanukigb::word_t) { return val; }

 private:
  tanukigb::byte_t val = 0xBE;
};

template <tanukigb::Addressable A>
class Mem {
 public:
  Mem(A addr) : addr_(addr) {}

 private:
  A addr_;
};

void RunGameBoy(tanukigb::Cpu& cpu) {
  int ret = cpu.Run();

  if (ret != 0) {
    std::cout << std::format("Unknown Opcode: {:#02x}\n", ret);
    cpu.DumpRegisters(std::cout);
  }
}

int main() {
  // tanukigb::Cpu cpu = tanukigb::Cpu::GameboyCpu();
  // RunGameBoy(cpu);
  // cpu.PrettyDumpRegisters(std::cout);

  // Mem<Foo> mem{Foo()};

  // decltype(std::declval<Foo>()[2])

  std::cout << "Is Foo Addressable? " << std::boolalpha
            << tanukigb::Addressable<Foo> << std::endl;

  return 0;
}
