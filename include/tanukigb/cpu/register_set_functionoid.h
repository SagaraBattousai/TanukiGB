#ifndef __TANUKIGB_CPU_REGISTER_SET_FUNCTIONOID_H__
#define __TANUKIGB_CPU_REGISTER_SET_FUNCTIONOID_H__

#include <array>
#include <bit>
#include <cstring>

namespace tanukigb {

template <std::integral T, bool is_alignment_garunteed>
class RegisterSetFnoid {};

template <std::integral T>
class RegisterSetFnoid<T, true> {
 public:
  explicit RegisterSetFnoid(unsigned char* const buff_ref)
      : buff_ref_{buff_ref} {}

  T operator()() const { return *(reinterpret_cast<T* const>(buff_ref_)); }

  T operator()(T value) { 
    *(reinterpret_cast<T* const>(buff_ref_)) = value; 
    return value;
  }

 private:
  unsigned char* const buff_ref_;
};

template <std::integral T>
class RegisterSetFnoid<T, false> {
 public:
  explicit RegisterSetFnoid(unsigned char* const buff_ref)
      : buff_ref_{buff_ref} {}

  T operator()() const {
    T ret{};
    std::memcpy(&ret, buff_ref_, sizeof(T));
    return ret;
  }

  T operator()(T value) {
    std::memcpy(buff_ref_, &value, sizeof(T));
    return value;
  }

 private:
  unsigned char* const buff_ref_;
};

}  // namespace tanukigb
#endif
