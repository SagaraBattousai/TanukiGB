#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_16BIT_LOAD_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_16BIT_LOAD_H__

#include <tanukigb/cpu/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode_tags.h>
#include <tanukigb/cpu/register_tags.h>

namespace tanukigb {

template <typename Underlying>
struct OpcodeHandlerCRTPBase<Underlying, opcode_tags::Load16Bit> {
  template <typename E>
  static inline opcode_return_type execute(E& executor) {
    // TODO: Do stuff
    
    //if constexpr ()

    // TODO: set up what 16bit loads should return
    Underlying::do_16bit_load(executor);
    // TODO: Other stuff
    return 0;
  }
};


//TOD: See if there's a way to handle all opcodes that end in 1 (for example)

template <>
struct OpcodeHandler<0x21> : Load16BitOpcodeHandlerBase<OpcodeHandler<0x21>> {
  constexpr static const char* const Neumonic = "LD HL, d16";
  constexpr static int InstructionBytes = 3;
  constexpr static int Cycles = 3;
  constexpr static const char* const Flags = "- - - -";

  template <typename E>
  static inline opcode_return_type do_16bit_load(E& exe) {
    //auto& sp = exe.template GetRegister<register_tags::SP>();
    //auto& pc = exe.template GetRegister<register_tags::PC>();

    // Todo: after MMU add helper as the postfix++ is mucky.
    //sp = exe.MemoryRead(pc++) | exe.MemoryRead(pc++) << 8;
    // registers_.PC() += 2;
    return 0x21;
  }
};

template <>
struct OpcodeHandler<0x31>
    : Load16BitOpcodeHandlerBase<OpcodeHandler<0x31>> {
  constexpr static const char* const Neumonic = "LD SP, d16";
  constexpr static int InstructionBytes = 3;
  constexpr static int Cycles = 3;
  constexpr static const char* const Flags = "- - - -";

  template <typename E>
  static inline opcode_return_type do_16bit_load(E& exe) {
    auto& sp = exe.template GetRegister<register_tags::SP>();
    auto& pc = exe.template GetRegister<register_tags::PC>();

    // Todo: after MMU add helper as the postfix++ is mucky.
    sp = exe.MemoryRead(pc++) | exe.MemoryRead(pc++) << 8;
    // registers_.PC() += 2;
    return 0;
  }
};

/*
GMB 16bit-Loadcommands
  ld   rr,nn       x1 nn nn  12 ---- rr=nn (rr may be BC,DE,HL or SP)
  ld   SP,HL       F9         8 ---- SP=HL
  push rr          x5        16 ---- SP=SP-2  (SP)=rr   (rr may be
BC,DE,HL,AF) pop  rr          x1        12 (AF) rr=(SP)  SP=SP+2   (rr may be
BC,DE,HL,AF)
*/

}  // namespace tanukigb

#endif
