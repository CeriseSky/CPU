#include <signals.hpp>
#include <cpu.hpp>

namespace IMCC_Emulator {
  class Logger {
    public:
      Logger(CPU *pCpu) :
        pCpu(pCpu) {}

      static void update(void *data);

    private:
      CPU *pCpu;
  };
}

