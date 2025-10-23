#include <alu.hpp>
#include <signals.hpp>

namespace IMCC_Emulator {
  void ALU::update(void *data) {
    auto self = (ALU *)data;

    if(!self->pControlBus->clock ||
       !self->pControlBus->aluOpen)
      return;

    switch(self->pControlBus->aluOperation) {
      case ALU_ADD:
        *self->pAccumulator += *self->pDataBus;
        break;

      default:
        break;
    }
  }
}

