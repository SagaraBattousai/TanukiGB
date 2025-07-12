#ifndef __TANUKIGB_MEMORY_ADDRESSABLE_H__
#define __TANUKIGB_MEMORY_ADDRESSABLE_H__

#include <concepts>
#include <type_traits>
#include <utility>

#include <tanukigb/types/types.h>

namespace tanukigb {

// I've got to stop thinking of this as a library (which I can't seem to do) it's an
//  application!

// Clearly I didnt understand operator[] with its const and non const versions
//  Lets just stick with read and write

//template <typename T, typename Addr_Type, typename Index_Type>
//concept Addressable = requires(T t, const T const_a, word_t addr, byte_t reg) {
//  { const_a.Read(addr) } -> std::same_as<decltype(reg)>; 
//  { a.Write(addr, reg) } -> std::same_as<void>; // Is that good? Should it matter what it returns?
//  // No Contains function as, to me, it's not ones own job to know where it is
//};

template <typename T>
concept ROM = requires(T rom, word_t addr, byte_t data) {
  { rom.Read(addr) } -> std::same_as<decltype(data)>;
};

template <typename T>
concept RAM = ROM<T> && requires(T ram, word_t addr, byte_t data) {
  { ram.Write(addr, data) };
};






}  // namespace tanukigb

#endif