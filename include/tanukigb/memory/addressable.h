#ifndef __TANUKIGB_MEMORY_ADDRESSABLE_H__
#define __TANUKIGB_MEMORY_ADDRESSABLE_H__

#include <concepts>
#include <type_traits>
#include <utility>

#include <tanukigb/types/types.h>

namespace tanukigb {

// I've got to stop thinking of this as a library (which I can't seem to do) it's an
//  application!

template <typename A>
//concept Addressable = requires(A&& a, word_t addr, byte_t reg) { // Dont need universal ref stuff
concept Addressable = requires(A a, const A ca, word_t addr, byte_t reg) {
  //{ ca[addr] } -> std::same_as<byte_t>; //Do I want to specify a read version or is a write that also reads okay? i.e. if its const It can be read ...?
  { a[addr] } -> std::convertible_to<byte_t>;
  { a[addr] = reg };
};

}  // namespace tanukigb

#endif