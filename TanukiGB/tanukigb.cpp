#include <tanukigb/cpu/cpu.h>
#include <tanukigb/memory/bootrom.h>
#include <tanukigb/types/types.h>

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

template <typename T, byte_t Opcode, byte_t...>
//template <byte_t Opcode, byte_t...>
struct OpcodeHandler {
  //template<typename T>
  static void execute(T& t){//}, byte_t ...) {
    //Error
  }
};

template <typename T>
struct OpcodeHandler<T, 0x01> {
//template<>
//struct OpcodeHandler<0x01> {
  //template <typename T>
  static void execute(T& t) {
    std::cout << "0x01 Called" << std::endl;
  }
};

template <typename T, byte_t... Args>
struct OpcodeHandler<T, 0x02, Args...> {
//template <byte_t... Args>
//struct OpcodeHandler<0x02, Args...> {
  //template <typename T>
  static void execute(T& t) {
    std::cout << "0x02 Called with args: ";
    const int arg_count = sizeof...(Args);
    if (arg_count == 0) {
      std::cout << "None" << std::endl;
      return;
    }
    //plus one needed for when arg_count = 0 even though runtime wont hit here
    int dummy[arg_count + 1] = {(std::cout << Args << ", ", 0)...};
    std::cout << std::endl;
  }
};


template<typename T>
using OpcodeHandlerFunc = void(T&);

template<typename T>
using OpcodeHandlerFuncPtr = void(*)(T&);




////template<typename T, std::size_t... IS>
//template<typename T, byte_t... IS>
//constexpr std::array<OpcodeHandlerFuncPtr<T>, sizeof...(IS)> GenJumpTable(){
//  std::array<OpcodeHandlerFuncPtr<T>, sizeof...(IS)>arr {(OpcodeHandler<IS>::execute<T>)...};
//  return arr;
//}

template <typename T, byte_t... IS>
constexpr std::array<OpcodeHandlerFuncPtr<T>, sizeof...(IS)> GenJumpTable() {
  std::array<OpcodeHandlerFuncPtr<T>, sizeof...(IS)> arr{
      (OpcodeHandler<T,IS>::execute)...};
  return arr;
}


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

  int i = 7;

 auto JumpTable = GenJumpTable<int, 0, 1, 2>();

  JumpTable[0](i);
  JumpTable[1](i);
  JumpTable[2](i);

  return 0;
}
