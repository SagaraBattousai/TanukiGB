#ifndef __TANUKIGB_CPU_OPCODE_OPCODE_TYPE_TRAITS_H__
#define __TANUKIGB_CPU_OPCODE_OPCODE_TYPE_TRAITS_H__

#include <tanukigb/types/types.h>

namespace tanukigb {

using opcode_return_type = int;
using opcode_type = byte_t;

// TODO:
template <typename E>
concept OpcodeExecutor = true;

}  // namespace tanukigb

#endif