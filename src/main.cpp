#include <clock.hpp>
#include <cstdlib>
#include <cpu.hpp>
#include <memory.hpp>
#include <logger.hpp>
#include <iostream>

int main(void) {
  using namespace IMCC_Emulator;

  CPU myCpu(1.0);

  Logger info(&myCpu);
  ROM rom("test.rom", &myCpu.addrBus, &myCpu.controlBus, &myCpu.dataBus,
          &myCpu.registers.select[RS_MEM_ADDR],
          &myCpu.registers.select[RS_MEM_DATA]);

  myCpu.components.push_back(CPU::Component(&info, info.update));
  myCpu.components.push_back(CPU::Component(&rom, rom.update));

  while( !(myCpu.registers.select[RS_FLAGS] & HALTED) ) {
    myCpu.loadReg(RS_ACC, 0);
    myCpu.setReg(RS_FLAGS, HALTED);
  }

  std::cout << "Accumulator = " <<
    std::format("0x{:X}\n", myCpu.registers.select[RS_ACC]);
  std::cerr << "CPU has finished execution.\n";
  return EXIT_SUCCESS;
}

