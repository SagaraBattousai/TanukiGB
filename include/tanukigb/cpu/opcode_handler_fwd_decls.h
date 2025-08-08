#ifndef __TANUKIGB_CPU_OPCODE_HANDLER_FWD_DECLS_H__
#define __TANUKIGB_CPU_OPCODE_HANDLER_FWD_DECLS_H__

#include <tanukigb/cpu/opcode_tags.h>
#include <tanukigb/cpu/jump_table.h>
#include <tanukigb/types/types.h>

namespace tanukigb {

using opcode_return_type = int;
using opcode_type = byte_t;

// template <Executor E>
//template <typename E>
//using OpcodeExecutionFunctionPtr = opcode_return_type (*)(E&);

//Want to say CRTP Executor but then wed have circulars (or forward decls)
// template <Executor E, std::size_t Num_Ops>
template <typename E, std::size_t Num_Ops>
using OpcodeJumpTable = JumpTable<opcode_return_type, E, std::size_t Num_Ops>>;

template <typename Underlying, OpcodeTag Tag>
struct OpcodeHandlerCRTPBase;

// Forward Declare actual Handler
template <opcode_type Opcode>
struct OpcodeHandler;

template <typename OpHandler>
using Load8BitOpcodeHandlerBase =
    OpcodeHandlerCRTPBase<OpHandler, opcode_tags::Load8Bit>;

template <typename OpHandler>
using Load16BitOpcodeHandlerBase =
    OpcodeHandlerCRTPBase<OpHandler, opcode_tags::Load16Bit>;

template <typename OpHandler>
using Arithmetic8BitOpcodeHandlerBase =
    OpcodeHandlerCRTPBase<OpHandler, opcode_tags::Arithmetic8Bit>;

template <typename OpHandler>
using Arithmetic16BitOpcodeHandlerBase =
    OpcodeHandlerCRTPBase<OpHandler, opcode_tags::Arithmetic16Bit>;

template <typename OpHandler>
using RotateAndShiftOpcodeHandlerBase =
    OpcodeHandlerCRTPBase<OpHandler, opcode_tags::RotateAndShift>;

template <typename OpHandler>
using SingleBitOpcodeHandlerBase =
    OpcodeHandlerCRTPBase<OpHandler, opcode_tags::SingleBit>;

template <typename OpHandler>
using JumpOpcodeHandlerBase = OpcodeHandlerCRTPBase<OpHandler, opcode_tags::Jump>;

template <typename OpHandler>
using HaltOpcodeHandlerBase = OpcodeHandlerCRTPBase<OpHandler, opcode_tags::Halt>;

template <typename OpHandler>
using OtherOpcodeHandlerBase = OpcodeHandlerCRTPBase<OpHandler, opcode_tags::Other>;

}  // namespace tanukigb
#endif