#include <memory.hpp>

namespace IMCC_Emulator {
  void ROM::update(void *data) {
    auto self = (ROM *)data;

    if(!self->pControlBus->clock ||
       !self->pControlBus->memOpen)
      return;

    if(!self->pControlBus->memIn &&
       *self->pMdr < self->storage.size())
      *self->pMdr = self->storage[*self->pMar];
  }
}

