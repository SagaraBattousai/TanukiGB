#ifndef __TANUKIGB_CPU_INTERNAL_OPCODE_OPCODE_HANDLER_FWD_DECLS_H__
#define __TANUKIGB_CPU_INTERNAL_OPCODE_OPCODE_HANDLER_FWD_DECLS_H__

#include <tanukigb/types/types.h>
#include <tanukigb/cpu/executor.h>
#include <tanukigb/cpu/opcode_tags.h>

namespace tanukigb {

using opcode_return_type = int;
using opcode_type = byte_t;

//template <Executor E>
template <typename E>
using OpcodeExecutionFunctionPtr = opcode_return_type (*)(E&);

template <typename Underlying, OpcodeTag Tag>
struct OpcodeHandlerCRTPBase;

// Forward Declare actual Handler
template <opcode_type Opcode>
struct OpcodeHandler;


}
#endif