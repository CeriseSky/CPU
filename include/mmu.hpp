#ifndef _MMU_HPP_
#define _MMU_HPP_

#include <architecture.hpp>
#include <memory.hpp>
#include <signals.hpp>

namespace IMCC_Emulator {
  class MemoryUnit {
    public:
      enum SpecialAddrs : word {
        W_REQUEST = 0xffff,
        RW_DATA = 0xfffe,        // the result of requests, or a
                                 // parameter to pass to requests
        RW_DATA2 = 0xfffd,
      };

      enum Requests : word {
        RQ_NONE = 0x0000,     // always set W_REQUEST to RQ_NONE before setting
                              // parameters. W_REQUEST is set back to RQ_NONE
                              // after a request operation is completed
        RQ_GET_ROM_SIZE, // returns ROM size in bytes rounded to the
                         // next 4K to emulate the population of
                         // physical ROM slots
        RQ_MAP_PAGE, // the 4K region starting at RW_DATA is mapped to the
                     // physical 4K RAM region starting at RW_DATA2 rounded
                     // down to a 4K boundary
        RQ_GET_RAM_SIZE, // in bytes, rounded down to 4K boundary
      };

      MemoryUnit(const char *romPath, ControlWord *pControlBus,
                 word *pMar, word *pMdr, size_t ramBytes) :
        pControlBus(pControlBus),
        pMar(pMar), pMdr(pMdr),
        mRom(romPath, pControlBus, &vMar, pMdr),
        mRam(ramBytes, pControlBus, &vMar, pMdr) {}

      static void update(void *data);

    private:
      word vMar;

      word rRequest;
      word rData;
      word rData2;

      ControlWord *pControlBus;

      word *pMar, *pMdr;
      ROM mRom;
      RAM mRam;

      // pAddr = maps[vAddr / 4096] + (vAddr % 4096)
      word maps[16];

      void handleCommand();
  };
}

#endif

