
#include <tanukigb/cpu/cpu_register_map.h>

namespace tanukigb {

namespace {

enum RegisterSetOffset {
  kAOffset = 0,
  kFOffset = 1,
  kBOffset = 2,
  kCOffset = 3,
  kDOffset = 4,
  kEOffset = 5,
  kHOffset = 6,
  kLOffset = 7,
  kSPOffset = 8,
  kPCOffset = 10,
  kAFOffset = 0,
  kBCOffset = 2,
  kDEOffset = 4,
  kHLOffset = 6
};

}  // namespace

CpuRegisterMap::CpuRegisterMap() 
  : A_(&raw_register_buffer_[kAOffset])
  , F_(&raw_register_buffer_[kFOffset])
  , B_(&raw_register_buffer_[kBOffset])
  , C_(&raw_register_buffer_[kCOffset])
  , D_(&raw_register_buffer_[kDOffset])
  , E_(&raw_register_buffer_[kEOffset])
  , H_(&raw_register_buffer_[kHOffset])
  , L_(&raw_register_buffer_[kLOffset])
  , SP_(reinterpret_cast<word_t*>(&raw_register_buffer_[kSPOffset]))
  , PC_(reinterpret_cast<word_t*>(&raw_register_buffer_[kPCOffset]))

{ 
  raw_register_buffer_.fill(0x00); 
}

std::ostream& CpuRegisterMap::DumpRegisters(std::ostream& os) const {
  os << std::hex << "A: 0x" << (unsigned)this->A()
     << "\tF: 0x" << (unsigned)this->F() << std::endl
     << "B: 0x" << (unsigned)this->B() << "\tC: 0x" << (unsigned)this->C()
     << std::endl
     << "D: 0x" << (unsigned)this->D() << "\tE: 0x" << (unsigned)this->E()
     << std::endl
     << "H: 0x" << (unsigned)this->H() << "\tL: 0x" << (unsigned)this->L()
     << std::endl
     << "SP: 0x" << (unsigned)this->SP() << std::endl
     << "PC: 0x" << (unsigned)this->PC() << std::endl;

  return os;
}


}