#ifndef _CLOCK_HPP_
#define _CLOCK_HPP_

#include <chrono>
#include <signals.hpp>

namespace IMCC_Emulator {

  class Clock {
    public:
      Clock(ControlWord *pControlBus, double frequency) :
        frequency(frequency),
        pControlBus(pControlBus) {}

      static void update(void *data);

    private:
      double frequency;
      std::chrono::system_clock::time_point lastCycle;
      ControlWord *pControlBus;
  };

};

#endif

