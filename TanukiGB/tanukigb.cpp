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
 private:
  int x_;
  int GetX() const { return x_; }

 public:
  int& SetX(int&& x) {
    x_ = std::move(x);
    return x_;
  }
  Foo& self = *this;

 public:
  Foo() : x_{37}, p{*this} {}
  tanukigb::Property<int, Foo, &Foo::GetX, nullptr, &Foo::SetX> p;
};

void RunGameBoy(tanukigb::Cpu& cpu) {
  int ret = cpu.Run();

  if (ret != 0) {
    std::cout << std::format("Unknown Opcode: {:#02x}\n", ret);
    cpu.DumpRegisters(std::cout);
  }
}

// using MFP = int&(Foo::*)(int&& v);

int main() {
  tanukigb::Cpu cpu = tanukigb::Cpu::GameboyCpu();
  RunGameBoy(cpu);
  cpu.PrettyDumpRegisters(std::cout);

  Foo f{};

  std::cout << "prop p = " << f.p << std::endl;

  f.p = 9;

  std::cout << "prop p = " << f.p << std::endl;


  return 0;
}
