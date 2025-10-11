#ifndef _SIGNALS_HPP_
#define _SIGNALS_HPP_

#include <cstdint>

namespace IMCC_Emulator {
  enum eSigControl : uint8_t {
    CLK = 1 << 0,
    ACC_R = 1 << 1,
    ACC_W = 1 << 2,
  };
  using SigControl = uint8_t;


};

#endif

