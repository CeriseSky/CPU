#include <clock.hpp>
#include <cstdlib>
#include <cpu.hpp>
#include <iostream>

int main(void) {
  using namespace IMCC_Emulator;

  CPU myCpu(10.0);

  while( !(myCpu.registers.select[RS_FLAGS] & HALTED) ) {
    myCpu.loadReg(RS_ACC, 0);
    myCpu.setReg(RS_FLAGS, HALTED);
  }

  std::cout << "Accumulator = " <<
    std::format("0x{:x}\n", myCpu.registers.select[RS_ACC]);
  std::cerr << "CPU has finished execution.\n";
  return EXIT_SUCCESS;
}

