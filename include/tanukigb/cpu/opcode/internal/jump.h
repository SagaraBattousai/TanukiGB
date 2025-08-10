#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_JUMP_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_JUMP_H__

#include <tanukigb/cpu/opcode/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode/opcode_tags.h>

#define JumpOpcodeHandler(opcode)                              \
  template <OpcodeExecutor Executor>                           \
  struct OpcodeHandler<Executor, opcode>                       \
      : OpcodeHandlerCRTPBase<OpcodeHandler<Executor, opcode>, Executor, \
                              opcode_tags::Jump>

namespace tanukigb {

template <typename Derived, OpcodeExecutor Executor>
struct OpcodeHandlerCRTPBase<Derived, Executor, opcode_tags::Jump> {
  static inline opcode_return_type execute(Executor& exe) {
    // TODO: Do stuff
    // TODO: set up what 8bit loads should return
    Derived::do_jump(exe);
    // TODO: Other stuff
  }
};
}  // namespace tanukigb

/*
GMB Jumpcommands
  jp   nn        C3 nn nn    16 ---- jump to nn, PC=nn
  jp   HL        E9           4 ---- jump to HL, PC=HL
  jp   f,nn      xx nn nn 16;12 ---- conditional jump if nz,z,nc,c
  jr   PC+dd     18 dd       12 ---- relative jump to nn (PC=PC+/-7bit)
  jr   f,PC+dd   xx dd     12;8 ---- conditional relative jump if nz,z,nc,c
  call nn        CD nn nn    24 ---- call to nn, SP=SP-2, (SP)=PC, PC=nn
  call f,nn      xx nn nn 24;12 ---- conditional call if nz,z,nc,c
  ret            C9          16 ---- return, PC=(SP), SP=SP+2
  ret  f         xx        20;8 ---- conditional return if nz,z,nc,c
  reti           D9          16 ---- return and enable interrupts (IME=1)
  rst  n         xx          16 ---- call to 00,08,10,18,20,28,30,38
*/

#undef JumpOpcodeHandler
#endif
