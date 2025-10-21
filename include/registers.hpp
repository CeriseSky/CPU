#ifndef _REGISTERS_HPP_
#define _REGISTERS_HPP_

#include <architecture.hpp>
#include <signals.hpp>

namespace IMCC_Emulator {
  enum eFlags {
    HALTED = 1 << 0,
  };

  enum eRegisterSelect {
    RS_FLAGS = 0,
    RS_MEM_ADDR,
    RS_MEM_DATA,
    RS_ACC,
    RS_PC,
    RS_CIR_OP,
    RS_CIR_DATA,

    __rs_enum_last,
  };

  class RegisterSet {
    public:
      word select[__rs_enum_last];

      static void update(void *data);

      RegisterSet(ControlWord *pControlBus, word *pDataBus) :
        select { [RS_FLAGS] = !HALTED,
                 [RS_PC] = 0 },
        pControlBus(pControlBus),
        pDataBus(pDataBus) {}

    private:
      ControlWord *pControlBus;
      word *pDataBus;
  };
}

#endif

