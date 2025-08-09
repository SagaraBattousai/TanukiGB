#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_8BIT_ARITHMETIC_LOAD_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_8BIT_ARITHMETIC_LOAD_H__

#include <tanukigb/cpu/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode_tags.h>
#include <tanukigb/cpu/register_tags.h>

namespace tanukigb {

template <typename Underlying>
struct OpcodeHandlerCRTPBase<Underlying, opcode_tags::Arithmetic8Bit> {
  template <typename E>
  static inline opcode_return_type execute(E& executor) {
    int ret;
    // TODO: Do stuff
    // TODO: set up what 8bit loads should return
    ret = Underlying::do_8bit_arithmetic(executor);
    // TODO: Other stuff

    return ret;
  }
};

template <>
struct OpcodeHandler<0xAF>
    : Arithmetic8BitOpcodeHandlerBase<OpcodeHandler<0xAF>> {
  constexpr static const char* const Neumonic = "XOR A";
  constexpr static int InstructionBytes = 1;
  constexpr static int Cycles = 1;
  constexpr static const char* const Flags = "Z 0 0 0";

  template <typename E>
  static inline opcode_return_type do_8bit_arithmetic(E& exe) {
    auto& A = exe.template GetRegister<register_tags::A>();
    auto& F = exe.template GetRegister<register_tags::F>();

    // Same as ClearRegister(registers_.A) but VV is technically what the Opcode
    // calls for:
    A ^= A;

    SetFlags<typename E::RegisterFlags, E::RegisterFlags::Z>(F);

    // While clearing all flags before setting the one above achieves a similar
    // result, it is technically wrong as it would destroy the lower (unused)
    // bits.
    ClearFlags<typename E::RegisterFlags, E::RegisterFlags::N,
               E::RegisterFlags::H, E::RegisterFlags::C>(F);

    return 0;
  }
};

}  // namespace tanukigb

#endif
