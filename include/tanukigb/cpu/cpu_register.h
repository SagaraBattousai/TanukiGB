#ifndef __TANUKIGB_CPU_CPU_REGISTER_H__
#define __TANUKIGB_CPU_CPU_REGISTER_H__

#include <concepts>
#include <utility>
#include <ostream>
#include <iostream>
#include <cstddef>
#include <format>


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

  // Life would be easier if it could be implicit but, safer this way
  // TODO: Can we make it usesable to index arrays?
  //
  // Actually I think it's alright as we can hide the conversion in a private function
  //
  explicit operator T() const { return bits_; }

  CpuRegister& operator=(CpuRegister&&) = delete;

  CpuRegister& operator=(const CpuRegister&) = default;
 
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

  friend T operator-(T lhs, const CpuRegister& rhs) {
    lhs -= rhs.bits_;
    return lhs;
  }

  T operator-(T rhs) const { 
    return static_cast<T>(*this) - rhs; 
  }

  CpuRegister& operator-=(const T& rhs) {
    bits_ -= rhs;
    return *this;
  }

  // Unfortunatly it needs to be a friend for the private constexpr static var
  // but then saves us a
  //   copy :)
  friend std::ostream& operator<<(std::ostream& os, const CpuRegister& reg) {
    os << std::format("{:#0{}x}", reg.bits_, CpuRegister::kFormatWidth);
    return os;
  }

  // NOTE: I am so annoyed that I cannot remember the proper solution I came up with while sleeping
  //    last night so here's the basic solution for now...
  //
  // Should this be defined here to ensure its hidden from non-ADL even though I dont think it should be 
  // inline.
  //
  // If this works well we can implement bitwise operators and we wont need to make these friends :)
  //
  template<std::integral U>
  friend U GetFromPair(CpuRegister& hi, CpuRegister& lo, int shift) {
    return static_cast<U>( (static_cast<U>(hi.bits_) << shift) | lo.bits_ );
  }

  //template <std::integral U>
  //friend void SetToPair(CpuRegister& hi, CpuRegister& lo, U value, int shift, U mask);

 private:
   T bits_;
   static constexpr std::size_t kFormatWidth = (sizeof(T) * 2) + 2;
};

// Doesn't need to be a friend :)
template <std::integral T, std::integral U>
inline void SetToPair(CpuRegister<T>& hi, CpuRegister<T>& lo, U value, int shift,
               U mask) {
  lo = static_cast<T>(value & mask);
  hi = static_cast<T>(value >> shift); // do we also & with mask? no as mask may not always be 0x00..FF..
}

}



#endif