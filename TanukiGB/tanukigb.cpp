#include <tanukigb/cpu/cpu.h>
#include <tanukigb/memory/bootrom.h>
#include <tanukigb/types/types.h>
#include <tanukigb/utility/property.h>

#include <array>
#include <concepts>
#include <cstdint>
#include <format>
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>

using tanukigb::byte_t;
using tanukigb::word_t;

class Foo {
 public:
  tanukigb::Property<int, Foo, true, false, true> p{*this, &Foo::GetX};

 private:
  int x_;
  int GetX() { return x_; }
};

void RunGameBoy(tanukigb::Cpu& cpu) {
  int ret = cpu.Run();

  if (ret != 0) {
    std::cout << std::format("Unknown Opcode: {:#02x}\n", ret);
    cpu.DumpRegisters(std::cout);
  }
}

int main() {
  tanukigb::Cpu cpu = tanukigb::Cpu::GameboyCpu();
  RunGameBoy(cpu);
  cpu.PrettyDumpRegisters(std::cout);

  std::cout << "Sizeof(Foo) = " << sizeof(Foo) << " Sizeof Foo.p "
            << sizeof(decltype(std::declval<Foo>().p)) << std::endl;

  return 0;
}
