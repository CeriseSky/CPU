#include <cpu.hpp>

namespace IMCC_Emulator {
  void CPU::setReg(uint8_t regSelect, word val) {
    cycle();

    dataBus = val;
    regIO(regSelect, true);
  }

  void CPU::loadReg(uint8_t regSelect, word addr) {
    setReg(RS_MEM_ADDR, addr);

    controlBus.memOpen = true;
    controlBus.memIn = false;
    cycle();

    controlBus.memOpen = false;
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
}

