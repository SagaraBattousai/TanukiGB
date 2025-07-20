#include <array>
#include <concepts>
#include <cstdint>
#include <format>
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>

#include <tanukigb/cpu/cpu.h>
#include <tanukigb/memory/bootrom.h>
#include <tanukigb/types/types.h>
#include <tanukigb/utility/property.h>

using tanukigb::byte_t;
using tanukigb::word_t;



//class Foo {


//};


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

  int x = 0;

  auto get = [&x]() -> int& { return x; };
  auto cset = [&x](const int& rhs) -> int& {
    x = rhs;
    return x;
  };

  auto mset = [&x](int&& rhs) -> int& { x = std::move(rhs);
    return x;
  };


  // Not really how properties should work but lets have a look :)
  tanukigb::Property<int, decltype(get), decltype(cset), decltype(mset)> px(get, cset, mset);

  std::cout << "px = " << px << " x = " << x << std::endl;

  //int y = 9;
  px = 9;

    std::cout << "px = " << px << " x = " << x << std::endl;


  return 0;
}
