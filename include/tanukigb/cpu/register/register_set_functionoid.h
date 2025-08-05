#ifndef __TANUKIGB_CPU_REGISTER_SET_FUNCTIONOID_H__
#define __TANUKIGB_CPU_REGISTER_SET_FUNCTIONOID_H__

#include <array>
#include <bit>
#include <cstring>

namespace tanukigb {
// Although reinterpret cast is "technically" safe when our buffer was aligned
// on the off chance std::uint8_t wasnt unsigned char (or the compiler
// disallowed it for strict aliasing memcpy is just safer (and faster than
// bit_cast for pointer (unless the original source was local (too function, not
// just "on" the stack)
template <std::integral T>
class RegisterSetFnoid {
 public:
  explicit RegisterSetFnoid(unsigned char* const buff_ptr)
      : buff_ptr_{buff_ptr} {}

  T operator()() const noexcept {
    T ret{};
    std::memcpy(&ret, buff_ptr_, sizeof(T));
    return ret;
  }

  T operator()(T value) noexcept {
    std::memcpy(buff_ptr_, &value, sizeof(T));
    return value;
  }

 private:
  unsigned char* const buff_ptr_;
};

}  // namespace tanukigb
#endif
