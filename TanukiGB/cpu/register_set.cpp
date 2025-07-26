
#include <tanukigb/cpu/register_set.h>

namespace tanukigb {

//#if defined(_WIN32) || defined(__CYGWIN__)
//template class TANUKIGB_EXPORT Register<byte_t, RegisterSetFnoid<byte_t, true>>;
//#endif

namespace {
using array_size_type = std::array<int, 0>::size_type;

// Is this allowed to be in the annonmous namespace
template <array_size_type BigEndianOffset, array_size_type LittleEndianOffset>
consteval array_size_type EndianOffset() {
  if constexpr (std::endian::native == std::endian::big) {
    return BigEndianOffset;
  } else if constexpr (std::endian::native == std::endian::little) {
    return LittleEndianOffset;
  } else {
    static_assert(
        false,
        "Mixed endian is (potentially currently) not supported. A per type "
        "endianness check may soon be implemented if some types have different "
        "endianness but niche byte layouts (e.g. using words instead of bytes "
        "or odd ordering) is unlikely to be supported).");
  }
}
}  // namespace

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