#include <clock.hpp>
#include <cstdlib>
#include <cpu.hpp>
#include <logger.hpp>
#include <iostream>

int main(void) {
  using namespace IMCC_Emulator;

  CPU myCpu(1.0);

  Logger info(&myCpu);
  myCpu.components.push_back(
      CPU::Component(&info, info.update));

  while( !(myCpu.registers.select[RS_FLAGS] & HALTED) ) {
    myCpu.loadReg(RS_ACC, 0);
    myCpu.setReg(RS_FLAGS, HALTED);
  }

  std::cout << "Accumulator = " <<
    std::format("0x{:x}\n", myCpu.registers.select[RS_ACC]);
  std::cerr << "CPU has finished execution.\n";
  return EXIT_SUCCESS;
}

