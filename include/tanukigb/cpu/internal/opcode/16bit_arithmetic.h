#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_16BIT_ARITHMETIC_LOAD_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_16BIT_ARITHMETIC_LOAD_H__

#include <tanukigb/cpu/opcode_tags.h>
#include <tanukigb/cpu/internal/opcode/opcode_handler_fwd_decls.h>

namespace tanukigb {

  template <typename Underlying>
  struct OpcodeHandlerCRTPBase<Underlying, opcode_tags::Arithmetic16Bit> {
    template <Executor E>
    static inline opcode_return_type execute(E& executor) {
      // TODO: Do stuff
      // TODO: set up what 8bit loads should return
      Underlying::do_16bit_arithmetic(executor);
      // TODO: Other stuff
    }
  };
}

#endif
