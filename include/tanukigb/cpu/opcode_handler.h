#ifndef __TANUKIGB_CPU_OPCODE_HANDLER_H__
#define __TANUKIGB_CPU_OPCODE_HANDLER_H__

// As This is an application and not a library I must remember that I can be
// bespoky (I love this pattern but I dont have time to waste trying to do so,
// its so awesome though).

//#include <tanukigb/cpu/executor.h>
#include <tanukigb/cpu/internal/opcode_handler_fwd_decls.h>
#include <tanukigb/cpu/opcode_tags.h>
#include <tanukigb/types/types.h>

#include <array>
#include <limits>
#include <utility>

// TODO: Remove iostream
#include <iostream>

namespace tanukigb {

template <typename E,
          opcode_type Num_Ops = std::numeric_limits<opcode_type>::max()>
using JumpTable =
    std::array<OpcodeExecutionFunctionPtr<E>, std::size_t(Num_Ops)>;

namespace opcode_details {

//template <Executor E, opcode_type... Ops>
template <typename E, opcode_type... Ops>
constexpr JumpTable<E, sizeof...(Ops)> GenerateJumpTable(
    std::integer_sequence<opcode_type, Ops...>) {
  return {(&OpcodeHandler<Ops>::template execute<E>)...};
}

}  // namespace opcode_details

//template <Executor E, opcode_type Num_Ops>
template <typename E, opcode_type Num_Ops>
constexpr auto GenerateJumpTable() {
  return opcode_details::GenerateJumpTable<E>(
      std::make_integer_sequence<opcode_type, Num_Ops>{});
}

template <typename Underlying, OpcodeTag Tag>
struct OpcodeHandlerCRTPBase {};


template <byte_t Opcode>
struct OpcodeHandler
    : OpcodeHandlerCRTPBase<OpcodeHandler<Opcode>, opcode_tags::Other> {
  template <typename E>
  static inline opcode_return_type execute(E& executor) {
    // TODO
    return Opcode;
  }
};
}  // namespace tanukigb

#include <tanukigb/cpu/internal/16bit_arithmetic.h>
#include <tanukigb/cpu/internal/16bit_load.h>
#include <tanukigb/cpu/internal/8bit_arithmetic.h>
#include <tanukigb/cpu/internal/8bit_load.h>
#include <tanukigb/cpu/internal/jump.h>
#include <tanukigb/cpu/internal/rotate_and_shift.h>
#include <tanukigb/cpu/internal/single_bit.h>

// template <typename T, byte_t... IS>
// constexpr std::array<OpcodeHandlerFuncPtr<T>, sizeof...(IS)> GenJumpTable()
// {
//   std::array<OpcodeHandlerFuncPtr<T>, sizeof...(IS)> arr{
//       (OpcodeHandler<T, IS>::execute)...};
//   return arr;
// }

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

GMB 16bit-Arithmetic/logical Commands
  add  HL,rr     x9           8 -0hc HL = HL+rr     ;rr may be BC,DE,HL,SP
  inc  rr        x3           8 ---- rr = rr+1      ;rr may be BC,DE,HL,SP
  dec  rr        xB           8 ---- rr = rr-1      ;rr may be BC,DE,HL,SP
  add  SP,dd     E8          16 00hc SP = SP +/- dd ;dd is 8bit signed number
  ld   HL,SP+dd  F8          12 00hc HL = SP +/- dd ;dd is 8bit signed number

GMB Rotate- und Shift-Commands
  rlca           07           4 000c rotate akku left
  rla            17           4 000c rotate akku left through carry
  rrca           0F           4 000c rotate akku right
  rra            1F           4 000c rotate akku right through carry
  rlc  r         CB 0x        8 z00c rotate left
  rlc  (HL)      CB 06       16 z00c rotate left
  rl   r         CB 1x        8 z00c rotate left through carry
  rl   (HL)      CB 16       16 z00c rotate left through carry
  rrc  r         CB 0x        8 z00c rotate right
  rrc  (HL)      CB 0E       16 z00c rotate right
  rr   r         CB 1x        8 z00c rotate right through carry
  rr   (HL)      CB 1E       16 z00c rotate right through carry
  sla  r         CB 2x        8 z00c shift left arithmetic (b0=0)
  sla  (HL)      CB 26       16 z00c shift left arithmetic (b0=0)
  swap r         CB 3x        8 z000 exchange low/hi-nibble
  swap (HL)      CB 36       16 z000 exchange low/hi-nibble
  sra  r         CB 2x        8 z00c shift right arithmetic (b7=b7)
  sra  (HL)      CB 2E       16 z00c shift right arithmetic (b7=b7)
  srl  r         CB 3x        8 z00c shift right logical (b7=0)
  srl  (HL)      CB 3E       16 z00c shift right logical (b7=0)

GMB Singlebit Operation Commands
  bit  n,r       CB xx        8 z01- test bit n
  bit  n,(HL)    CB xx       12 z01- test bit n
  set  n,r       CB xx        8 ---- set bit n
  set  n,(HL)    CB xx       16 ---- set bit n
  res  n,r       CB xx        8 ---- reset bit n
  res  n,(HL)    CB xx       16 ---- reset bit n

GMB CPU-Controlcommands
  ccf            3F           4 -00c cy=cy xor 1
  scf            37           4 -001 cy=1
  nop            00           4 ---- no operation
  halt           76         N*4 ---- halt until interrupt occurs (low power)
  stop           10 00        ? ---- low power standby mode (VERY low power)
  di             F3           4 ---- disable interrupts, IME=0
  ei             FB           4 ---- enable interrupts, IME=1

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
 *
 *
 *
*/

#endif
