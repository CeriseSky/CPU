#include <cpu.hpp>
#include <registers.hpp>

namespace IMCC_Emulator {
  class Logger {
    public:
      Logger(CPU *pCpu, RegisterSet *pRegisters) :
        clockCycles(0),
        pCpu(pCpu),
        pRegisters(pRegisters) {}

      static void update(void *data);
      void log();

      size_t clockCycles;

    private:
      CPU *pCpu;
      RegisterSet *pRegisters;
  };
}

