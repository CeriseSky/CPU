#ifndef _SIGNALS_HPP_
#define _SIGNALS_HPP_

#include <bit>
#include <cstdint>

namespace IMCC_Emulator {
  struct ControlWord {
    bool clock : 1;
    bool regOpen : 1;
    uint8_t regSelect : 3;
    bool regIn : 1; // 1 = dataBus into register, 0 = register into databus
    bool memOpen : 1;
    bool memIn : 1;
    bool pcInc : 1;

    constexpr ControlWord(uint16_t sig) {
      *this = std::bit_cast<ControlWord>(sig);
    }
  } __attribute__((packed));
  static_assert(sizeof(ControlWord) == sizeof(uint16_t),
                "ControlWord does not match SigControl");
};

#endif

