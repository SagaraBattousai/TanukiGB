#ifndef __TANUKIGB_CPU_OPCODE_HANDLER_H__
#define __TANUKIGB_CPU_OPCODE_HANDLER_H__

#include <tanukigb/cpu/opcode/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode/opcode_tags.h>
#include <tanukigb/types/types.h>

#include <tanukigb/cpu/opcode/internal/16bit_arithmetic.h>
#include <tanukigb/cpu/opcode/internal/16bit_load.h>
#include <tanukigb/cpu/opcode/internal/8bit_arithmetic.h>
#include <tanukigb/cpu/opcode/internal/8bit_load.h>
#include <tanukigb/cpu/opcode/internal/jump.h>
#include <tanukigb/cpu/opcode/internal/rotate_and_shift.h>
#include <tanukigb/cpu/opcode/internal/single_bit.h>

namespace tanukigb {

template <typename Derived, OpcodeTag Tag>
struct OpcodeHandlerCRTPBase {};

template <opcode_type Opcode>
struct OpcodeHandler
    : OpcodeHandlerCRTPBase<OpcodeHandler<Opcode>, opcode_tags::Other> {

  template<typename Executor>
  static inline opcode_return_type execute(Executor& e) {
    // TODO
    return Opcode;
  }
};
}  // namespace tanukigb


/*

GMB CPU-Controlcommands
  ccf            3F           4 -00c cy=cy xor 1
  scf            37           4 -001 cy=1
  nop            00           4 ---- no operation
  halt           76         N*4 ---- halt until interrupt occurs (low power)
  stop           10 00        ? ---- low power standby mode (VERY low power)
  di             F3           4 ---- disable interrupts, IME=0
  ei             FB           4 ---- enable interrupts, IME=1

 *
 *
 *
*/

#endif
