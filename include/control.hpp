#ifndef _CONTROL_UNIT_HPP_
#define _CONTROL_UNIT_HPP_

#include <signals.hpp>

namespace IMCC_Emulator {
  class ControlUnit {
    public:
      ControlUnit(SigControl *pControlBus) : pControlBus(pControlBus) {}
      static void update(void *data);

    private:
      SigControl *pControlBus;
  };
}

#endif

