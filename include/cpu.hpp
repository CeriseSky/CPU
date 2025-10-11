#ifndef _CPU_HPP_
#define _CPU_HPP_

#include <clock.hpp>
#include <control.hpp>
#include <cstdint>
#include <signals.hpp>
#include <vector>

namespace IMCC_Emulator {
  class CPU {
    public:
      using word = uint8_t;

      struct Component {
        using update_t = void (*)(void *);

        void *data;
        update_t pfnUpdate;

        Component(void *data, update_t pfnUpdate) : data(data),
                                                    pfnUpdate(pfnUpdate) {}

        inline void operator()() const {
          pfnUpdate(data);
        };
      };

      std::vector<Component> components;
      void tick() {
        for(auto& update : components)
          update();
      }

      CPU(double freq) : components({
                           Component(&clock, clock.update),
                           Component(&cu, cu.update),
                         }),
                         registers({!HALTED}),
                         controlBus(0),
                         clock(&controlBus, freq),
                         cu(&controlBus) {}

      enum eFlags : word {
        HALTED = 1 << 0,
      };
      struct RegisterSet {
        word flags;
      };
      RegisterSet registers;

    private:
      SigControl controlBus;

      Clock clock;
      ControlUnit cu;
 };

};

#endif

