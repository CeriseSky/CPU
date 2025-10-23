#ifndef _ARCHITECTURE_HPP_
#define _ARCHITECTURE_HPP_

#include <bit>
#include <cstdint>

namespace IMCC_Emulator {
  using word = uint16_t;

  enum OPCODES : word {
    OP_HLT = 0x0000, // Operand is ignored
    OP_LDA = 0x0001, // Operand is the memory address to retrieve value from
    OP_ADD = 0x0002, // Operand is memory address to retrieve addend from
  };

  // TODO: make code independent of machine's endianness
  static_assert(std::endian::native == std::endian::little,
                "Machine must be little endian");
}

#endif

