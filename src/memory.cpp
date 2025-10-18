#include <memory.hpp>

namespace IMCC_Emulator {
  void RAM::update(void *data) {
    auto self = (RAM *)data;

    if(!self->pControlBus->clock ||
       !self->pControlBus->memOpen ||
       self->addrMax < *self->pMar)
      return;

    if(self->pControlBus->memIn)
      self->storage[*self->pMar] = *self->pMdr;
    else
      *self->pMdr = self->storage[*self->pMar];
  }
}

