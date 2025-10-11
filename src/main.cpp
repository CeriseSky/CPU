#include <clock.hpp>
#include <cstdlib>
#include <cpu.hpp>
#include <iostream>

int main(void) {
  std::cout << "Hello, world!\n";

  IMCC_Emulator::CPU myCpu(1.0);
  while( !(myCpu.registers.flags & myCpu.HALTED) )
    myCpu.tick();

  std::cerr << "CPU has finished execution.\n";
  return EXIT_SUCCESS;
}

