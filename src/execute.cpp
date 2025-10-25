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

      case OP_STA:
        setRegR(RS_MEM_ADDR, RS_CIR_DATA);
        setRegR(RS_MEM_DATA, RS_ACC);
        memIO(true);
        break;

      case OP_JNZ:
        regIO(RS_FLAGS, false);
        if(!(dataBus & ZERO))
          setRegR(RS_PC, RS_CIR_DATA);
        break;

      case OP_LDP:
        setRegR(RS_MEM_ADDR, RS_ACC);
        memIO(false);
        setRegR(RS_ACC, RS_MEM_DATA);
        break;

      case OP_STP:
        setRegR(RS_MEM_ADDR, RS_CIR_DATA);
        memIO(false);
        setRegR(RS_MEM_ADDR, RS_ACC);
        memIO(true);
        break;

      default:
        break;
    }
  }
}

