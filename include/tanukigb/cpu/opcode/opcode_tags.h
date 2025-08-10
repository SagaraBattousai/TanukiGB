#ifndef __TANUKIGB_CPU_OPCODE_TAGS_H__
#define __TANUKIGB_CPU_OPCODE_TAGS_H__

#include <tanukigb/utility/concepts.h>

#include <array>
#include <concepts>
#include <utility>

namespace tanukigb {

namespace opcode_tags {

// Dont need inheritance structure (at least for now)

struct Load8Bit {};
struct Load16Bit {};

struct Arithmetic8Bit {};
struct Arithmetic16Bit {};

struct RotateAndShift {};

struct SingleBit {};

struct Jump {};

struct Halt {};

struct Other {};

}  // namespace opcode_tags

// Add new opcodes to the list.
template <typename Tag>
concept OpcodeTag =
    one_of<Tag, opcode_tags::Load8Bit, opcode_tags::Load16Bit,
           opcode_tags::Arithmetic8Bit, opcode_tags::Arithmetic16Bit,
           opcode_tags::RotateAndShift, opcode_tags::SingleBit,
           opcode_tags::Jump, opcode_tags::Halt, opcode_tags::Other>;

}  // namespace tanukigb
#endif
