#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_16BIT_ARITHMETIC_LOAD_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_16BIT_ARITHMETIC_LOAD_H__

#include <tanukigb/cpu/opcode/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode/opcode_tags.h>

#define Arithmetic16OpcodeHandler(opcode)            \
  template <>                                        \
  struct OpcodeHandler<opcode>                       \
      : OpcodeHandlerCRTPBase<OpcodeHandler<opcode>, \
                              opcode_tags::Arithmetic16Bit>

namespace tanukigb {

template <typename Derived>
struct OpcodeHandlerCRTPBase<Derived, opcode_tags::Arithmetic16Bit> {
  template <OpcodeExecutor Executor>
  static inline opcode_return_type execute(Executor& exe) {
    // TODO: Do stuff
    // TODO: set up what 8bit loads should return
    Derived::do_16bit_arithmetic(exe);
    // TODO: Other stuff
  }
};
}  // namespace tanukigb

/*
GMB 16bit-Arithmetic/logical Commands
  add  HL,rr     x9           8 -0hc HL = HL+rr     ;rr may be BC,DE,HL,SP
  inc  rr        x3           8 ---- rr = rr+1      ;rr may be BC,DE,HL,SP
  dec  rr        xB           8 ---- rr = rr-1      ;rr may be BC,DE,HL,SP
  add  SP,dd     E8          16 00hc SP = SP +/- dd ;dd is 8bit signed number
  ld   HL,SP+dd  F8          12 00hc HL = SP +/- dd ;dd is 8bit signed number

*/

#undef Arithmetic16OpcodeHandler
#endif
