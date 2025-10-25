#include <memory.hpp>

namespace IMCC_Emulator {
  void ROM::update(void *data) {
    auto self = (ROM *)data;


    if(!self->pControlBus->clock ||
       !self->pControlBus->memOpen)
      return;

    if(!self->pControlBus->memIn &&
       *self->pMar < self->storage.size())
      *self->pMdr = self->storage[*self->pMar];
  }

  void RAM::update(void *data) {
    auto self = (RAM *)data;

    if(!self->pControlBus->clock ||
       !self->pControlBus->memOpen ||
       *self->pMar >= self->size())
      return;

    if(self->pControlBus->memIn)
      self->storage[*self->pMar] = *self->pMdr;
    else
      *self->pMdr = self->storage[*self->pMar];
  }
}

