#ifndef __TANUKIGB_CPU_OPCODE_HANDLER_FWD_DECLS_H__
#define __TANUKIGB_CPU_OPCODE_HANDLER_FWD_DECLS_H__

#include <tanukigb/cpu/opcode_tags.h>
#include <tanukigb/types/types.h>

namespace tanukigb {

 template <typename Underlying, OpcodeTag Tag>
 struct OpcodeHandlerCRTPBase;

// Forward Declare actual Handler
 template <opcode_type Opcode>
 struct OpcodeHandler;

}  // namespace tanukigb
#endif