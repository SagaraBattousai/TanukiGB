#ifndef __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_16BIT_LOAD_H__
#define __TANUKIGB_CPU_OPCODE_INTERNAL_OPCODE_16BIT_LOAD_H__

#include <tanukigb/cpu/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode_tags.h>
#include <tanukigb/cpu/register_tags.h>

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

template <typename Underlying>
struct OpcodeHandlerCRTPBase<Underlying, opcode_tags::Load16Bit> {
  template <typename E>
  static inline opcode_return_type execute(E& executor) {
    // TODO: Do stuff

    opcode_return_type ret_code;
    if constexpr (has_tag_v<Underlying>) {
      ret_code = do_16bit_load(executor, typename Underlying::Tag{});
    } else {
      ret_code = Underlying::do_16bit_load(executor);
    }
    // TODO: Other stuff
    return ret_code;
  }

 private:
  template <typename E>
  constexpr static inline opcode_return_type do_16bit_load(
      E& executor, load16_tags::load_immidiate) {
    //could static_assert underlying with tag has ImmidiateLoadRegister but compiler warning isnt too scary
    auto& load_reg =
        executor
            .template GetRegister<typename Underlying::ImmidiateLoadRegister>();
    auto& pc = executor.template GetRegister<register_tags::PC>();

    // Todo: after MMU add helper as the postfix++ is mucky.
    load_reg = executor.MemoryRead(pc++) | executor.MemoryRead(pc++) << 8;
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
