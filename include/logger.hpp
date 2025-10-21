#include <cpu.hpp>
#include <registers.hpp>

namespace IMCC_Emulator {
  class Logger {
    public:
      Logger(CPU *pCpu, RegisterSet *pRegisters) :
        pCpu(pCpu),
        pRegisters(pRegisters) {}

      static void update(void *data);

    private:
      CPU *pCpu;
      RegisterSet *pRegisters;
  };
}

