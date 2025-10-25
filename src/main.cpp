#include <alu.hpp>
#include <clock.hpp>
#include <cstdlib>
#include <cpu.hpp>
#include <iostream>
#include <memory.hpp>
#include <mmu.hpp>
#include <logger.hpp>
#include <print>

int main(void) {
  using namespace IMCC_Emulator;

  CPU myCpu(10.0);

  RegisterSet registers(&myCpu.controlBus, &myCpu.dataBus);
  myCpu.components.push_back(CPU::Component(&registers, registers.update));

  MemoryUnit mmu("test.rom", &myCpu.controlBus,
                 &registers.select[RS_MEM_ADDR],
                 &registers.select[RS_MEM_DATA],
                 4096 * sizeof(word));
  myCpu.components.push_back(CPU::Component(&mmu, mmu.update));

  Logger info(&myCpu, &registers);
  myCpu.components.push_back(CPU::Component(&info, info.update));

  ALU alu(&myCpu.controlBus, &myCpu.dataBus, &registers.select[RS_ACC]);
  myCpu.components.push_back(CPU::Component(&alu, alu.update));

  while( !(registers.select[RS_FLAGS] & HALTED) )
    myCpu.step();

  info.log();
  std::println(std::cerr, "CPU has finished execution.");

  return EXIT_SUCCESS;
}

