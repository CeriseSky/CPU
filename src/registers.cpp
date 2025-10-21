#include <cstddef>
#include <registers.hpp>
#include <signals.hpp>

void IMCC_Emulator::RegisterSet::update(void *data) {
  auto self = (RegisterSet *)data;
  auto &cw = self->pControlBus;

  if(!cw->clock)
    return;

  if(cw->pcInc)
    self->select[RS_PC]++;

  if(!cw->regOpen)
    return;
  for(size_t i = 0; i < sizeof(self->select)/sizeof(word); i++)
    if(cw->regSelect == i) {
      if(cw->regIn)
        self->select[i] = *self->pDataBus;
      else
        *self->pDataBus = self->select[i];
      break;
    }
}

