#include <cpu.hpp>
#include <registers.hpp>

namespace IMCC_Emulator {
  void CPU::execute() {
    regIO(RS_CIR_OP, false);

    switch(dataBus) {
      case OP_HLT:
        regIO(RS_FLAGS, false);
        dataBus |= HALTED;
        regIO(RS_FLAGS, true);
        break;

      case OP_LDA:
        setRegR(RS_MEM_ADDR, RS_CIR_DATA);
        memIO(false);
        setRegR(RS_ACC, RS_MEM_DATA);
        break;

      case OP_ADD:
        setRegR(RS_MEM_ADDR, RS_CIR_DATA);
        memIO(false);
        regIO(RS_MEM_DATA, false);

        controlBus.aluOpen = true;
        controlBus.aluOperation = ALU_ADD;
        cycle();
        controlBus.aluOpen = false;
        break;

      default:
        break;
    }
  }
}

