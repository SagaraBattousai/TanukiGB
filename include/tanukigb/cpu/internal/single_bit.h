#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_SINGLE_BIT_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_SINGLE_BIT_H__

#include <tanukigb/cpu/internal/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode_tags.h>

namespace tanukigb {

template <typename Underlying>
struct OpcodeHandlerCRTPBase<Underlying, opcode_tags::SingleBit> {
  template <typename E>
  static inline opcode_return_type execute(E& executor) {
    // TODO: Do stuff
    // TODO: set up what 8bit loads should return
    Underlying::do_single_bit(executor);
    // TODO: Other stuff
  }
};
}  // namespace tanukigb

#endif
