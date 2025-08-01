#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_16BIT_LOAD_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_16BIT_LOAD_H__

#include <tanukigb/cpu/opcode_tags.h>
#include <tanukigb/cpu/internal/opcode/opcode_handler_fwd_decls.h>

namespace tanukigb {

template <typename Underlying>
struct OpcodeHandlerCRTP<Underlying, opcode_tags::Load16Bit> {
  template <Executor E>
  static inline opcode_return_type execute(E& executor) {
    // TODO: Do stuff
    // TODO: set up what 16bit loads should return
    std::cout << "CRTP\n";
    Underlying::do_16bit_load(executor);
    // TODO: Other stuff
    return 0;
  }
};


  template <>
struct OpcodeHandler<0x31>
    : OpcodeHandlerCRTP<OpcodeHandler<0x31>, opcode_tags::Load16Bit> {
  template <typename Executor>
  static inline opcode_return_type do_16bit_load(Executor& t) {
    std::cout << "This Works: " << t << std::endl;
    // Todo: after MMU add helper as the postfix++ is mucky.
    // registers_.SP = mmu_.Read(registers_.PC++) | mmu_.Read(registers_.PC++)
    //                                                 << 8;
    // registers_.PC() += 2;
    return 0;
  }
};





}

#endif
