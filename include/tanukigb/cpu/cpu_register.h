#ifndef __TANUKIGB_CPU_CPU_REGISTER_H__
#define __TANUKIGB_CPU_CPU_REGISTER_H__

#include <concepts>
#include <utility>
#include <ostream>
#include <iostream>


namespace tanukigb {

// I think actually these should all be inline since its a loose wrapper around T
//
// Additionally I think we should disable some of the move and copy operations as we need a 
// deeper think about the semantics of a register. Values of a register my be passed around but
// registers themselves probaby shouldn't
//
// NOTE: May need to make it possible to add smaller types into larger ones
//  however for now lets just typedef the underlying type
//
template <std::integral T>
class CpuRegister {
 public:
   using register_type = T;

  CpuRegister() : bits_{0} {}
  explicit CpuRegister(T initial_state) : bits_{initial_state} {}
  ~CpuRegister() = default;

  // Copy should only be done via assignment to copy the value of the other register but ...
  //   technically it's not "unsemantic" to copy a value, but theyre two distinct values
  CpuRegister(const CpuRegister& rhs) = default;

  CpuRegister(CpuRegister&& rhs) = delete;
  CpuRegister(const CpuRegister&& rhs) = delete;

  CpuRegister& operator=(const CpuRegister&) = default;
  CpuRegister& operator=(CpuRegister&&) = delete;

  CpuRegister& operator=(const T& value) {
    this->bits_ = value;
    return *this;
  }

  CpuRegister& operator=(T&& rhs) {
    bits_ = std::move(rhs);
    return *this;
  }

  // Should this return the underlying value like the postfix versions?
  CpuRegister& operator++() { 
    ++bits_;
    return *this;
  }

  //Usefull for asigning value before incrementing (which happens alot in gameboy instruction set)
  T operator++(int) { 
    T previous_value = bits_;
    ++bits_;
    return previous_value;
  }

  CpuRegister& operator--() {
    --bits_;
    return *this;
  }

  T operator--(int) {
    T previous_value = bits_;
    --bits_;
    return previous_value;
  }

  CpuRegister& operator+=(const T& rhs) {
    bits_ += rhs;
    return *this;
  }

  friend T operator+(T lhs, const CpuRegister& rhs) { 
    lhs += rhs.bits_;
    return lhs;
  }

  T operator+(T rhs) const {
    return rhs + *this;
  }

  CpuRegister& operator-=(const T& rhs) {
    bits_ -= rhs;
    return *this;
  }

 private:
   T bits_;
};


}



#endif