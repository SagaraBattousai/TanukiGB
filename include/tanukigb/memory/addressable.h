#ifndef __TANUKIGB_MEMORY_ADDRESSABLE_H__
#define __TANUKIGB_MEMORY_ADDRESSABLE_H__

#include <concepts>
#include <type_traits>
#include <utility>

#include <tanukigb/types/types.h>

namespace tanukigb {

// I've got to stop thinking of this as a library (which I can't seem to do) it's an
//  application!

// I have to be careful, the C++20 guidelines specify that concepts must specify meaningful semantics
//  as opposed to a syntactic constraint, and this is a bit syntactic rather than semantic as operator[]
//  is syntatic sugar and really we want to say we require a read and write function.
// Since these types arent used directly perhaps we can say the functions should be Read and Write and
//  wrap their calls in operator[]....

template <typename A>
//concept Addressable = requires(A&& a, word_t addr, byte_t reg) { // Dont need universal ref stuff
concept Addressable = requires(A a, const A ca, word_t addr, byte_t reg) {
  { ca[addr] } -> std::same_as<byte_t>; 
  // ^^ constant readable, could just say writable as (in operator[] form it subsumes readable but not const....
  //{ a[addr] } -> std::convertible_to<byte_t>;
  { a[addr] = reg }; // writable
};

}  // namespace tanukigb

#endif