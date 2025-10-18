#include <architecture.hpp>
#include <signals.hpp>
#include <vector>

namespace IMCC_Emulator {

  class RAM {
    static constexpr uint8_t initVal = 0xe5;

    public:
      RAM(word *pAddrBus, ControlWord *pControlBus, word *pDataBus,
          word *pMar, word *pMdr, word addrMax) :
        pAddrBus(pAddrBus),
        pControlBus(pControlBus),
        pDataBus(pDataBus),
        pMar(pMar), pMdr(pMdr),
        addrMax(addrMax), storage(addrMax, initVal) {}

      static void update(void *data);

    private:
      word *pAddrBus;
      ControlWord *pControlBus;
      word *pDataBus;

      word *pMar;
      word *pMdr;

      word addrMax;
      std::vector<word> storage;
  };
}

