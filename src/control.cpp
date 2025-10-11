#include <control.hpp>
#include <cstdio>

void IMCC_Emulator::ControlUnit::update(void *data) {
  auto self = (ControlUnit *)data;
  printf("\r%.8b", *self->pControlBus);
}

