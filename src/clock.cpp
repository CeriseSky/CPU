#include <chrono>
#include <clock.hpp>

void IMCC_Emulator::Clock::update(void *data) {
  auto self = (Clock *)data;
  self->pControlBus->clock = 0;

  using std::chrono::high_resolution_clock;
  using std::chrono::system_clock;
  using std::chrono::duration;
  using std::chrono::seconds;

  auto now = high_resolution_clock::now();
  duration<double> dur = now - self->lastCycle;

  if( dur.count() >= 1.0/self->frequency ) {
    self->pControlBus->clock = 1;
    self->lastCycle = now;
  }
}

