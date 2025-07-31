
#include <tanukigb/cpu/register_set.h>
#include <tanukigb/utility/endianness.h>

namespace tanukigb {

// Do not use explicitly template initalisation definite the following (byte_t
// defined in tanukigb/types/types.h as std::uint16_t)
template class TANUKIGB_EXPORT RegisterSetFnoid<byte_t>;
template class TANUKIGB_EXPORT Register<byte_t, RegisterSetFnoid<byte_t>>;

// Do not use explicitly template initalisation definite the following (word_t
// defined in tanukigb/types/types.h as std::uint16_t)
template class TANUKIGB_EXPORT RegisterSetFnoid<word_t>;
template class TANUKIGB_EXPORT Register<word_t, RegisterSetFnoid<word_t>>;

namespace {

consteval std::size_t min(std::size_t a, std::size_t b) {
  return a < b ? a : b;
}

enum RegisterOffset : std::size_t {
  A = EndianOffset<0, 1>(),
  F = EndianOffset<1, 0>(),

  B = EndianOffset<2, 3>(),
  C = EndianOffset<3, 2>(),

  D = EndianOffset<4, 5>(),
  E = EndianOffset<5, 4>(),

  H = EndianOffset<6, 7>(),
  L = EndianOffset<7, 6>(),

  SP = 8,
  PC = 10,

  BC = min(B, C),
  DE = min(D, E),
  HL = min(H, L)
};
}  // namespace

RegisterSet::RegisterSet()
    : register_buffer_{},
      // TODO: make neater/use constants to remove magic numbers
      A{ByteRegisterFnoid{register_buffer_.data() + RegisterOffset::A}},
      F{ByteRegisterFnoid{register_buffer_.data() + RegisterOffset::F}},

      B{ByteRegisterFnoid{register_buffer_.data() + RegisterOffset::B}},
      C{ByteRegisterFnoid{register_buffer_.data() + RegisterOffset::C}},

      D{ByteRegisterFnoid{register_buffer_.data() + RegisterOffset::D}},
      E{ByteRegisterFnoid{register_buffer_.data() + RegisterOffset::E}},

      H{ByteRegisterFnoid{register_buffer_.data() + RegisterOffset::H}},
      L{ByteRegisterFnoid{register_buffer_.data() + RegisterOffset::L}},

      SP{WordRegisterFnoid{register_buffer_.data() + RegisterOffset::SP}},
      PC{WordRegisterFnoid{register_buffer_.data() + RegisterOffset::PC}},

      BC{WordRegisterFnoid{register_buffer_.data() + RegisterOffset::BC}},
      DE{WordRegisterFnoid{register_buffer_.data() + RegisterOffset::DE}},
      HL{WordRegisterFnoid{register_buffer_.data() + RegisterOffset::HL}} {}

// Could do one where we also print the composite registers (although they're
// "fake")
std::ostream& PrettyPrintRegisters(std::ostream& os, const RegisterSet& rs) {
  os << "|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n"
     << "| Flags: Z: N: H: C: - Unused |\n"
     << std::format(
            "|        {:d}  {:d}  {:d}  {:d}  - {:04b}   "
            "|\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n",
            IsFlagSet<128>(rs.F), IsFlagSet<64>(rs.F), IsFlagSet<32>(rs.F),
            IsFlagSet<16>(rs.F), (rs.F & 0b0000'1111))

     << "| A: " << rs.A << "\tF: " << rs.F << "       |\n| B: " << rs.B
     << "\tC: " << rs.C << "       |\n| D: " << rs.D << "\tE: " << rs.E
     << "       |\n| H: " << rs.H << "\tL: " << rs.L
     << "       |\n| SP: " << rs.SP << "                  |\n| PC: " << rs.PC
     << "                  |\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|" << std::endl;
  return os;
}

}  // namespace tanukigb