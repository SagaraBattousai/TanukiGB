#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_16BIT_LOAD_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_16BIT_LOAD_H__

#include <tanukigb/cpu/opcode/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode/opcode_tags.h>
#include <tanukigb/cpu/register_tags.h>  //TODO

// Undefed at end of file. Used to save typing but not for external visability
#define Load16OpcodeHandler(opcode) \
  template <>                       \
  struct OpcodeHandler<opcode>      \
      : OpcodeHandlerCRTPBase<OpcodeHandler<opcode>, opcode_tags::Load16Bit>

namespace tanukigb {

template <typename, typename = void>
static inline constexpr bool has_tag_v = false;
template <typename T>
static inline constexpr bool has_tag_v<T, std::void_t<typename T::Tag>> = true;

namespace load16_tags {
struct load_immidiate {};
}  // namespace load16_tags

template <typename Derived>
struct OpcodeHandlerCRTPBase<Derived, opcode_tags::Load16Bit> {
  template <OpcodeExecutor Executor>
  static inline opcode_return_type execute(Executor& exe) {
    // TODO: Do stuff

    opcode_return_type ret_code;
    if constexpr (has_tag_v<Derived>) {
      ret_code = do_16bit_load(exe, typename Derived::Tag{});
    } else {
      ret_code = Derived::do_16bit_load(exe);
    }
    // TODO: Other stuff
    return ret_code;
  }

 private:
  template <OpcodeExecutor Executor>
  constexpr static inline opcode_return_type do_16bit_load(
      Executor& exe, load16_tags::load_immidiate) {
    auto& load_reg =
        exe.template GetRegister<typename Derived::ImmidiateLoadRegister>();
    auto& pc = exe.template GetRegister<register_tags::PC>();

    // Todo: after MMU add helper as the postfix++ is mucky.
    load_reg = exe.MemoryRead(pc++) | exe.MemoryRead(pc++) << 8;
    // registers_.PC() += 2;
    return 0;
  }
};

Load16OpcodeHandler(0x21) {
  constexpr static const char* const Neumonic = "LD HL, d16";
  constexpr static int InstructionBytes = 3;
  constexpr static int Cycles = 3;
  constexpr static const char* const Flags = "- - - -";

  using Tag = load16_tags::load_immidiate;
  using ImmidiateLoadRegister = typename register_tags::HL;
};

Load16OpcodeHandler(0x31) {
  constexpr static const char* const Neumonic = "LD SP, d16";
  constexpr static int InstructionBytes = 3;
  constexpr static int Cycles = 3;
  constexpr static const char* const Flags = "- - - -";

  using Tag = load16_tags::load_immidiate;
  using ImmidiateLoadRegister = typename register_tags::SP;
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

#undef Load16OpcodeHandler

#endif
