#ifndef __TANUKIGB_CPU_OPCODE_HANDLER_FWD_DECLS_H__
#define __TANUKIGB_CPU_OPCODE_HANDLER_FWD_DECLS_H__

#include <tanukigb/cpu/opcode/opcode_tags.h>
#include <tanukigb/cpu/opcode/opcode_type_traits.h>

namespace tanukigb {

 template <typename Derived, OpcodeExecutor Executor, OpcodeTag Tag>
 struct OpcodeHandlerCRTPBase;

// Forward Declare actual Handler
 template <OpcodeExecutor Executor, opcode_type Opcode>
 struct OpcodeHandler;

}  // namespace tanukigb
#endif