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
  explicit RegisterSetFnoid(unsigned char* const buff_ptr)
      : buff_ptr_{buff_ptr} {}

  T operator()() const { return *(reinterpret_cast<T* const>(buff_ptr_)); }

  T operator()(T value) { 
    *(reinterpret_cast<T* const>(buff_ptr_)) = value; 
    return value;
  }

 private:
  unsigned char* const buff_ptr_;
};

template <std::integral T>
class RegisterSetFnoid<T, false> {
 public:
  explicit RegisterSetFnoid(unsigned char* const buff_ptr)
      : buff_ptr_{buff_ptr} {}

  T operator()() const {
    T ret{};
    std::memcpy(&ret, buff_ptr_, sizeof(T));
    return ret;
  }

  T operator()(T value) {
    std::memcpy(buff_ptr_, &value, sizeof(T));
    return value;
  }

 private:
  unsigned char* const buff_ptr_;
};

}  // namespace tanukigb
#endif
