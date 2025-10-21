#include <clock.hpp>
#include <cstdlib>
#include <cpu.hpp>
#include <memory.hpp>
#include <logger.hpp>
#include <iostream>

int main(void) {
  using namespace IMCC_Emulator;

  CPU myCpu(5.0);

  RegisterSet registers(&myCpu.controlBus, &myCpu.dataBus);
  myCpu.components.push_back(CPU::Component(&registers, registers.update));

  ROM rom("test.rom", &myCpu.controlBus,
          &registers.select[RS_MEM_ADDR],
          &registers.select[RS_MEM_DATA]);
  myCpu.components.push_back(CPU::Component(&rom, rom.update));

  Logger info(&myCpu, &registers);
  myCpu.components.push_back(CPU::Component(&info, info.update));

  while( !(registers.select[RS_FLAGS] & HALTED) )
    myCpu.step();

  std::cerr << "CPU has finished execution.\n";
  return EXIT_SUCCESS;
}

