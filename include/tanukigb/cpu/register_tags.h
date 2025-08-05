#ifndef __TANUKIGB_CPU_REGISTER_TAGS_H__
#define __TANUKIGB_CPU_REGISTER_TAGS_H__

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

template <typename Tag>
concept RegisterTag8Bit =
    std::derived_from<Tag, register_tags::groups::Reg8Bit> && RegisterTag<Tag>;

template <typename Tag>
concept RegisterTag16Bit =
    std::derived_from<Tag, register_tags::groups::Reg16Bit> && RegisterTag<Tag>;

template <typename Tag>
concept RegisterTagComposite =
    std::derived_from<Tag, register_tags::groups::RegComposite> &&
    RegisterTag<Tag>;

}  // namespace tanukigb

#endif