#include <clock.hpp>

void IMCC_Emulator::Clock::update(void *data) {
  auto self = (IMCC_Emulator::Clock *)data;
  if( ((double)clock() - self->lastCycle)/CLOCKS_PER_SEC >= 0.5/self->frequency ) {
    *self->pControlBus ^= eSigControl::CLK;
    self->lastCycle = clock();
  }
}

