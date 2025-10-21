#include <architecture.hpp>
#include <cpu.hpp>
#include <registers.hpp>

namespace IMCC_Emulator {
  void CPU::setReg(uint8_t regSelect, word val) {
    cycle();

    dataBus = val;
    regIO(regSelect, true);
  }

  void CPU::loadReg(uint8_t regSelect, word addr) {
    setReg(RS_MEM_ADDR, addr);
    memIO(false);
    setRegR(regSelect, RS_MEM_DATA);
  }

  void CPU::regIO(uint8_t regSelect, bool write) {
    cycle();

    controlBus.regSelect = regSelect;
    controlBus.regIn = write;
    controlBus.regOpen = true;

    cycle();
    controlBus.regOpen = false;
  }

  void CPU::setRegR(uint8_t a, uint8_t b) {
    regIO(b, false);
    regIO(a, true);
  }

  void CPU::step() {
    fetch();
    execute();
  }

  void CPU::fetch() {
    setRegR(RS_MEM_ADDR, RS_PC);
    memIO(false);
    setRegR(RS_CIR_OP, RS_MEM_DATA);

    controlBus.pcInc = true;
    cycle();
    controlBus.pcInc = false;

    setRegR(RS_MEM_ADDR, RS_PC);
    memIO(false);
    setRegR(RS_CIR_DATA, RS_MEM_DATA);

    controlBus.pcInc = true;
    cycle();
    controlBus.pcInc = false;
  }

  void CPU::memIO(bool write) {
    cycle();

    controlBus.memOpen = true;
    controlBus.memIn = write;
    cycle();

    controlBus.memOpen = false;
  }

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

      default:
        break;
    }
  }
}

