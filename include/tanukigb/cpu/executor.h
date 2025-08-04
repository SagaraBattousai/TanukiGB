#ifndef __TANUKIGB_CPU_EXECUTOR_H__
#define __TANUKIGB_CPU_EXECUTOR_H__

#include <tanukigb/cpu/register.h>
#include <tanukigb/types/types.h>
#include <tanukigb/utility/concepts.h>

#include <concepts>

namespace tanukigb {

namespace register_tags {
namespace groups {
// Unused hierachial tags
struct Reg8Bit {};
struct Reg16Bit {};
struct RegComposite : Reg16Bit {};
}  // namespace groups

struct A : groups::Reg8Bit {};
struct F : groups::Reg8Bit {};
struct B : groups::Reg8Bit {};
struct C : groups::Reg8Bit {};
struct D : groups::Reg8Bit {};
struct E : groups::Reg8Bit {};
struct H : groups::Reg8Bit {};
struct L : groups::Reg8Bit {};

struct SP : groups::Reg16Bit {};
struct PC : groups::Reg16Bit {};

struct AF : groups::RegComposite {};
struct BC : groups::RegComposite {};
struct DE : groups::RegComposite {};
struct HL : groups::RegComposite {};
}  // namespace register_tags

template <typename Tag>
concept RegisterTag =
    one_of<Tag, register_tags::A, register_tags::F, register_tags::B,
           register_tags::C, register_tags::D, register_tags::E,
           register_tags::H, register_tags::L, register_tags::SP,
           register_tags::PC, register_tags::AF, register_tags::BC,
           register_tags::DE, register_tags::HL>;

// TODO: Setup a proper concept for Executor
template <typename E>
concept Executor = //true;
 requires(E exe) {
   {
     exe.template GetRegister<register_tags::A>()
   } noexcept -> RegisterLike<byte_t>;
   {
     exe.template GetRegister<register_tags::PC>()
   } noexcept -> RegisterLike<word_t>;
   {
     exe.template GetRegister<register_tags::AF>()
   } noexcept -> RegisterLike<word_t>;
 };

// template <typename E>
// concept Executor = requires(E exe) {
//   {
//     exe.template GetRegister<register_tags::groups::Reg8Bit>()
//   } noexcept -> RegisterLike<byte_t>;
//   {
//     exe.template GetRegister<register_tags::groups::Reg16Bit>()
//   } noexcept -> RegisterLike<word_t>;
//   {
//     exe.template GetRegister<register_tags::groups::RegComposite>()
//   } noexcept -> RegisterLike<word_t>;
// };

}  // namespace tanukigb

#endif
