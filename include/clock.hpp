#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_

#include <ctime>
#include <signals.hpp>

namespace IMCC_Emulator {

  class Clock {
    public:
      Clock(ControlWord *pControlBus, double frequency) :
        frequency(frequency),
        lastCycle(clock()),
        pControlBus(pControlBus) {}

      static void update(void *data);

    private:
      double frequency;
      clock_t lastCycle;
      ControlWord *pControlBus;
  };

};

#endif

