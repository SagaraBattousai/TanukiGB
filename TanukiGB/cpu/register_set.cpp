
#include <tanukigb/cpu/register_set.h>

namespace tanukigb {

//template class TANUKIGB_EXPORT Register<byte_t, RegisterSetFnoid<byte_t, true>>;
template class TANUKIGB_EXPORT RegisterSetFnoid<byte_t, true>;
template class TANUKIGB_EXPORT Register<byte_t, RegisterSetFnoid<byte_t, true>>;

// Do not use explicitly template initalisation definite the following (word_t
// defined in tanukigb/types/types.h as std::uint16_t)
template class TANUKIGB_EXPORT RegisterSetFnoid<word_t, true>;
template class TANUKIGB_EXPORT Register<word_t, RegisterSetFnoid<word_t, true>>;

RegisterSet::RegisterSet()
    : register_buffer_{},
      // TODO: make neater/use constants to remove magic numbers
      A{ByteRegisterFnoid{register_buffer_.data() + EndianOffset<0, 1>()}},
      F{ByteRegisterFnoid{register_buffer_.data() + EndianOffset<1, 0>()}},

      B{ByteRegisterFnoid{register_buffer_.data() + EndianOffset<2, 3>()}},
      C{ByteRegisterFnoid{register_buffer_.data() + EndianOffset<3, 2>()}},

      D{ByteRegisterFnoid{register_buffer_.data() + EndianOffset<4, 5>()}},
      E{ByteRegisterFnoid{register_buffer_.data() + EndianOffset<5, 4>()}},

      H{ByteRegisterFnoid{register_buffer_.data() + EndianOffset<6, 7>()}},
      L{ByteRegisterFnoid{register_buffer_.data() + EndianOffset<7, 6>()}},

      SP{WordRegisterFnoid{register_buffer_.data() + 8}},
      PC{WordRegisterFnoid{register_buffer_.data() + 10}},

      BC{WordRegisterFnoid{register_buffer_.data() + 2}},
      DE{WordRegisterFnoid{register_buffer_.data() + 4}},
      HL{WordRegisterFnoid{register_buffer_.data() + 6}} {}

// Could do one where we also print the composite registers (although they're "fake")
std::ostream& PrettyPrintRegisters(std::ostream& os, const RegisterSet& rs) {
  os << "A: " << rs.A
     << "\tF: " << rs.F
     << "\nB: " << rs.B
     << "\tC: " << rs.C
     << "\nD: " << rs.D
     << "\tE: " << rs.E
     << "\nH: " << rs.H
     << "\tL: " << rs.L
     << "\nSP: " << rs.SP
     << "\nPC: " << rs.PC
     << std::endl;
  return os;
}

}  // namespace tanukigb