#ifndef _ALU_HPP_
#define _ALU_HPP_

#include <architecture.hpp>
#include <signals.hpp>

namespace IMCC_Emulator {
  class ALU {
    public:
      ALU(ControlWord *pControlBus, word *pDataBus, word *pAccumulator) :
        pControlBus(pControlBus),
        pDataBus(pDataBus),
        pAccumulator(pAccumulator) {};

      static void update(void *data);

    private:
      ControlWord *pControlBus;
      word *pDataBus;
      word *pAccumulator;
  };
}

#endif

