#ifndef __TANUKIGB_MEMORY_MMU_H__
#define __TANUKIGB_MEMORY_MMU_H__

#include <_TanukiGB_config.h>
#include <tanukigb/memory/bootrom.h>
#include <tanukigb/memory/concepts.h>
#include <tanukigb/types/types.h>

#include <memory>

namespace tanukigb {

// Am I going to too much trouble to avoid runtime polymorphism?

// Perhaps runtime polymorphism and an array is better..... (don't like
// requirement on order)

class MMU {  // Could make two classes one for each....?
 public:
  // I dont think we should dllexport inline functions but I would like to delve
  // more into this at some point
  static MMU GameboyMMU() { return MMU(Bootrom::GBRom()); }
  static MMU ColourGameboyMMU() { return MMU(Bootrom::CGBRom()); }

  TANUKIGB_EXPORT byte_t Read(word_t addr) const;

  TANUKIGB_EXPORT void Write(word_t addr, byte_t value);

 private:
  MMU(Bootrom&& bootrom)
      : bootrom_(std::move(bootrom)),
        psudo_ram_{std::make_unique<byte_t[]>(FULL_RAM_BUFFER_SIZE)} {}

  // No end as variable depending on Colour or Standard gameboy.
  static constexpr word_t BOOTROM_START = 0x00;

  static constexpr word_t BOOT_REGISTER_ADDRESS = 0xFF50;

  bool IsBootromDisabled() const { return false; }  // TODO:
  // { return (this->Read(BOOT_REGISTER_ADDRESS) & 0x01) == 0x01; };
  void DisableBootRom() {
  }  // TODO: // { this->Write(BOOT_REGISTER_ADDRESS, 0x01); }

  // template<ROM R>
  // const R& GetROM(word_t addr) const;

  Bootrom bootrom_;

  // NOTE: Temp! fake ram that handles everything for now
  static constexpr size_t FULL_RAM_BUFFER_SIZE = 0x01'00'00;  // 65,536
  std::unique_ptr<byte_t[]> psudo_ram_;
  // byte_t psudo_ram_[FULL_RAM_BUFFER_SIZE];
};

// template <ROM R>
// const R& MMU::GetROM(word_t addr) const {
//   if (!IsBootromDisabled()) {
//     if (addr >= 0 && addr < bootrom_.rom_size_) {
//       return
//     }
//   } else {
//     return nullptr;
//   }
//
// }

}  // namespace tanukigb

#endif