#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_ROTATE_AND_SHIFT_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_ROTATE_AND_SHIFT_H__

#include <tanukigb/cpu/internal/opcode/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode_tags.h>

namespace tanukigb {

template <typename Underlying>
struct OpcodeHandlerCRTP<Underlying, opcode_tags::RotateAndShift> {
  template <Executor E>
  static inline opcode_return_type execute(E& executor) {
    // TODO: Do stuff
    // TODO: set up what 8bit loads should return
    Underlying::do_rotate_and_shift(executor);
    // TODO: Other stuff
  }
};
}  // namespace tanukigb

#endif
