#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_8BIT_LOAD_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_8BIT_LOAD_H__

#include <tanukigb/cpu/opcode_tags.h>
#include <tanukigb/cpu/internal/opcode/opcode_handler_fwd_decls.h>


namespace tanukigb {

  template <typename Underlying>
  struct OpcodeHandlerCRTPBase<Underlying, opcode_tags::Load8Bit> {
    template <Executor E>
    static inline opcode_return_type execute(E& executor) {
      // TODO: Do stuff
      // TODO: set up what 8bit loads should return
      Underlying::do_8bit_load(executor);
      // TODO: Other stuff
    }
  };
}

#endif
