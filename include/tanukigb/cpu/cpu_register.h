#ifndef __TANUKIGB_CPU_CPU_REGISTER_H__
#define __TANUKIGB_CPU_CPU_REGISTER_H__

#include <concepts>
#include <cstdint>

// NOTE: The requirement on std::uint8_t is almost always fine but...
// technically it is possible for that not to be supported so ...

namespace tanukigb {

// Pass size as arg since sizeof(T) may not equal register_size.
// That said 16bit registers are "technically" a different type to 8bit etc...
// keep in mind
template <std::unsigned_integral T>
class CpuRegister {
 public:
  CpuRegister(T* data_ptr, int register_size);

  T Get() const { return *data_ptr_; }

  CpuRegister& operator++();
  void operator++(int) { this->operator++(); }

  CpuRegister& operator--();
  void operator--(int) { this->operator--(); }

 private :
  T* data_ptr_;
  // in bytes
  int register_size_;
};

template <std::unsigned_integral T>
CpuRegister<T>::CpuRegister(T* data_ptr, int register_size)
    : data_ptr_(data_ptr), register_size_(register_size) {}

template <std::unsigned_integral T>
CpuRegister<T>& CpuRegister<T>::operator++() {
  ++(*(this->data_ptr_));
  return *this;
}


template <std::unsigned_integral T>
CpuRegister<T>& CpuRegister<T>::operator--() {
  --(*(this->data_ptr_));
  return *this;
}





}  // namespace tanukigb

#endif