#ifndef _ARCHITECTURE_HPP_
#define _ARCHITECTURE_HPP_

#include <bit>
#include <cstdint>

namespace IMCC_Emulator {
  using word = uint16_t;

  enum OPCODES : word {
    OP_HLT = 0x0000, // Flags |= HALTED
    OP_LDA = 0x0001, // Accumulator = *operand
    OP_ADD = 0x0002, // Accumulator += *operand
    OP_STA = 0x0003, // *operand = Accumulator
    OP_JNZ = 0x0004, // ProgramCounter = operand
    OP_LDP = 0x0005, // Accumulator = *Accumulator
    OP_STP = 0x0006, // *Accumulator = *operand
  };

  // TODO: make code independent of machine's endianness
  static_assert(std::endian::native == std::endian::little,
                "Machine must be little endian");
}

#endif

