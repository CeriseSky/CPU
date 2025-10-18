#include <clock.hpp>

void IMCC_Emulator::Clock::update(void *data) {
  auto self = (Clock *)data;
  self->pControlBus->clock = 0;

  if( ((double)clock() - self->lastCycle)/CLOCKS_PER_SEC >= 0.5/self->frequency ) {
    self->pControlBus->clock = 1;
    self->lastCycle = clock();
  }
}

