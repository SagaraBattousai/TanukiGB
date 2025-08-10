#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_8BIT_ARITHMETIC_LOAD_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_8BIT_ARITHMETIC_LOAD_H__

#include <tanukigb/cpu/opcode/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode/opcode_tags.h>
#include <tanukigb/cpu/register_tags.h>  //TODO:

// Undefed at end of file. Used to save typing but not for external visability
#define Arithmetic8BitOpcodeHandler(opcode)          \
  template <>                                        \
  struct OpcodeHandler<opcode>                       \
      : OpcodeHandlerCRTPBase<OpcodeHandler<opcode>, \
                              opcode_tags::Arithmetic8Bit>

namespace tanukigb {

template <typename Derived>
struct OpcodeHandlerCRTPBase<Derived, opcode_tags::Arithmetic8Bit> {
  template <OpcodeExecutor Executor>
  static inline opcode_return_type execute(Executor& exe) {
    int ret;
    // TODO: Do stuff
    // TODO: set up what 8bit loads should return
    ret = Derived::do_8bit_arithmetic(exe);
    // TODO: Other stuff

    return ret;
  }
};

Arithmetic8BitOpcodeHandler(0xAF) {
  constexpr static const char* const Neumonic = "XOR A";
  constexpr static int InstructionBytes = 1;
  constexpr static int Cycles = 1;
  constexpr static const char* const Flags = "Z 0 0 0";

  template <OpcodeExecutor Executor>
  static inline opcode_return_type do_8bit_arithmetic(Executor & exe) {
    auto& A = exe.template GetRegister<register_tags::A>();
    auto& F = exe.template GetRegister<register_tags::F>();

    // Same as ClearRegister(registers_.A) but VV is technically what the Opcode
    // calls for:
    A ^= A;

    SetFlags<typename Executor::RegisterFlags, Executor::RegisterFlags::Z>(F);

    // While clearing all flags before setting the one above achieves a similar
    // result, it is technically wrong as it would destroy the lower (unused)
    // bits.
    ClearFlags<typename Executor::RegisterFlags, Executor::RegisterFlags::N,
               Executor::RegisterFlags::H, Executor::RegisterFlags::C>(F);

    return 0;
  }
};

}  // namespace tanukigb

/*
GMB 8bit-Arithmetic/logical Commands
  add  A,r         8x         4 z0hc A=A+r
  add  A,n         C6 nn      8 z0hc A=A+n
  add  A,(HL)      86         8 z0hc A=A+(HL)
  adc  A,r         8x         4 z0hc A=A+r+cy
  adc  A,n         CE nn      8 z0hc A=A+n+cy
  adc  A,(HL)      8E         8 z0hc A=A+(HL)+cy
  sub  r           9x         4 z1hc A=A-r
  sub  n           D6 nn      8 z1hc A=A-n
  sub  (HL)        96         8 z1hc A=A-(HL)
  sbc  A,r         9x         4 z1hc A=A-r-cy
  sbc  A,n         DE nn      8 z1hc A=A-n-cy
  sbc  A,(HL)      9E         8 z1hc A=A-(HL)-cy
  and  r           Ax         4 z010 A=A & r
  and  n           E6 nn      8 z010 A=A & n
  and  (HL)        A6         8 z010 A=A & (HL)
  xor  r           Ax         4 z000
  xor  n           EE nn      8 z000
  xor  (HL)        AE         8 z000
  or   r           Bx         4 z000 A=A | r
  or   n           F6 nn      8 z000 A=A | n
  or   (HL)        B6         8 z000 A=A | (HL)
  cp   r           Bx         4 z1hc compare A-r
  cp   n           FE nn      8 z1hc compare A-n
  cp   (HL)        BE         8 z1hc compare A-(HL)
  inc  r           xx         4 z0h- r=r+1
  inc  (HL)        34        12 z0h- (HL)=(HL)+1
  dec  r           xx         4 z1h- r=r-1
  dec  (HL)        35        12 z1h- (HL)=(HL)-1
  daa              27         4 z-0x decimal adjust akku
  cpl              2F         4 -11- A = A xor FF
*/

#undef Arithmetic8BitOpcodeHandler

#endif
