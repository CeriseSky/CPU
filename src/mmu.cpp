#include <mmu.hpp>

namespace IMCC_Emulator {
  void MemoryUnit::update(void *data) {
    auto self = (MemoryUnit *)data;

    if(!self->pControlBus->clock || !self->pControlBus->memOpen)
      return;

    switch(*self->pMar) {
      case W_REQUEST:
        if(!self->pControlBus->memIn)
          break;

        self->rRequest = *self->pMdr;
        self->handleCommand();
        break;

      case RW_DATA:
        if(!self->pControlBus->memIn)
          *self->pMdr = self->rData;
        else
          self->rData = *self->pMdr;
        break;

      case RW_DATA2:
        if(self->pControlBus->memIn)
          self->rData2 = *self->pMdr;
        else *self->pMdr = self->rData2;
        break;

      default:

        if(*self->pMar < self->mRom.size()) {
          self->vMar = *self->pMar;
          self->mRom.update(&self->mRom);
        }
        else {
          self->vMar = self->maps[*self->pMar / 4096] +
                       (*self->pMar & 0xfff);
          if(self->vMar < self->mRam.size())
           self->mRam.update(&self->mRam);
        }

        break;
    }
  }

  void MemoryUnit::handleCommand() {
    switch(rRequest) {
      case RQ_GET_ROM_SIZE:
        rData = mRom.size() - (mRom.size() % 4096);
        break;

      case RQ_GET_RAM_SIZE:
        rData = mRam.size() - (mRam.size() % 4096);
        break;

      case RQ_MAP_PAGE:
        maps[rData / 4096] = rData2;
        break;

      default:
        break;
    }
  }
}

