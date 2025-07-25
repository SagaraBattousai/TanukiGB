#ifndef __TANUKIGB_CPU_REGISTER_H__
#define __TANUKIGB_CPU_REGISTER_H__

#include <concepts>
#include <utility>
#include <format>
#include <ostream>

namespace tanukigb {

namespace {
constexpr auto kHexCharsPerByte = 2;
}

// May need a Register private base to remove code bloat
// Don't want offset as a NTTP as A) it means we'd need to
// template each function and a bunch of other things i just forgot (Thanks Halo
// tv show)
//
// Hard to decouble however without additional template parameters.
// We want Registers of the same integral type (16 bit registers 8 bit registers
// etc to be the "same type" passing a functionoid will be difficult without
// templates making them each distinct types but if we coulple them to the
// register set class then... not great!
// Actually if they take the same functionoid its okay so...

template <std::integral T, typename Functionoid>
class Register {
 public:
   //For now
  Register(T init) : value_{init} {}

  // Could just pass by value as it's less duplication but in this case its not
  // a big deal
  T& operator=(const T&);
  T& operator=(T&&);

  //For now
  operator T() const { return value_; }
  //For now
  operator T&() { return value_; }


  friend std::ostream& operator<<(std::ostream& os, const Register& obj) {
    os << std::format("{:#0{}x}", obj.GetValue(),
                      (1 + sizeof(T)) * kHexCharsPerByte);
    return os;
  }

  private:
  // For now
  T value_;
};

}  // namespace tanukigb
#endif