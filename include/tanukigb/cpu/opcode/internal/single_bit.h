#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_SINGLE_BIT_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_SINGLE_BIT_H__

#include <tanukigb/cpu/opcode/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode/opcode_tags.h>

#define SingleBitOpcodeHandler(opcode) \
  template <>                          \
  struct OpcodeHandler<opcode>         \
      : OpcodeHandlerCRTPBase<OpcodeHandler<opcode>, opcode_tags::SingleBit>

namespace tanukigb {

template <typename Derived>
struct OpcodeHandlerCRTPBase<Derived, opcode_tags::SingleBit> {
  template <OpcodeExecutor Executor>
  static inline opcode_return_type execute(Executor& exe) {
    // TODO: Do stuff
    // TODO: set up what 8bit loads should return
    Derived::do_single_bit(exe);
    // TODO: Other stuff
  }
};
}  // namespace tanukigb

/*

GMB Singlebit Operation Commands
  bit  n,r       CB xx        8 z01- test bit n
  bit  n,(HL)    CB xx       12 z01- test bit n
  set  n,r       CB xx        8 ---- set bit n
  set  n,(HL)    CB xx       16 ---- set bit n
  res  n,r       CB xx        8 ---- reset bit n
  res  n,(HL)    CB xx       16 ---- reset bit n
*/

#undef SingleBitOpcodeHandler
#endif
