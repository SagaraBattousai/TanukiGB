#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_8BIT_LOAD_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_8BIT_LOAD_H__

#include <tanukigb/cpu/opcode/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode/opcode_tags.h>

// Undefed at end of file. Used to save typing but not for external visability
#define Load8OpcodeHandler(opcode) \
  template <>                      \
  struct OpcodeHandler<opcode>     \
      : OpcodeHandlerCRTPBase<OpcodeHandler<opcode>, opcode_tags::Load8Bit>

namespace tanukigb {

template <typename Derived>
struct OpcodeHandlerCRTPBase<Derived, opcode_tags::Load8Bit> {
  template <OpcodeExecutor Executor>
  static inline opcode_return_type execute(Executor& exe) {
    // TODO: Do stuff
    // TODO: set up what 8bit loads should return
    Derived::do_8bit_load(exe);
    // TODO: Other stuff
  }
};
}  // namespace tanukigb

/*
// GMB 8bit-Loadcommands
inline void load(byte_t& to, byte_t from) { to = from; }

  ld   r,r         xx         4 ---- r=r
  ld   r,n         xx nn      8 ---- r=n
  ld   r,(HL)      xx         8 ---- r=(HL)
  ld   (HL),r      7x         8 ---- (HL)=r
  ld   (HL),n      36 nn     12 ----
  ld   A,(BC)      0A         8 ----
  ld   A,(DE)      1A         8 ----
  ld   A,(nn)      FA        16 ----
  ld   (BC),A      02         8 ----
  ld   (DE),A      12         8 ----
  ld   (nn),A      EA        16 ----
  ld   A,(FF00+n)  F0 nn     12 ---- read from io-port n (memory FF00+n)
  ld   (FF00+n),A  E0 nn     12 ---- write to io-port n (memory FF00+n)
  ld   A,(FF00+C)  F2         8 ---- read from io-port C (memory FF00+C)
  ld   (FF00+C),A  E2         8 ---- write to io-port C (memory FF00+C)
  ldi  (HL),A      22         8 ---- (HL)=A, HL=HL+1
  ldi  A,(HL)      2A         8 ---- A=(HL), HL=HL+1
  ldd  (HL),A      32         8 ---- (HL)=A, HL=HL-1
  ldd  A,(HL)      3A         8 ---- A=(HL), HL=HL-1
*/

#undef Load8OpcodeHandler
#endif
