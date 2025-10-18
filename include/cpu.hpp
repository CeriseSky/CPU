#ifndef _CPU_HPP_
#define _CPU_HPP_

#include <clock.hpp>
#include <memory.hpp>
#include <registers.hpp>
#include <signals.hpp>
#include <vector>

namespace IMCC_Emulator {
  class CPU {
    public:
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

      RegisterSet registers;

      CPU(double freq) : components({
                           Component(&clock, clock.update),
                           Component(&registers, registers.update),
                           Component(&memory, memory.update),
                         }),
                         registers(&controlBus, &dataBus),
                         controlBus(0),
                         clock(&controlBus, freq),
                         memory(&addrBus, &controlBus, &dataBus,
                                &registers.select[RS_MEM_ADDR],
                                &registers.select[RS_MEM_DATA],
                                0xff /* tmp max addr */) {}

      // registers.select[regSelect] will = val after this call is finished,
      // Takes 3 clock cycles
      void setReg(uint8_t regSelect, word val);

      // registers.select[a] = registers.select[b] after this call is finished.
      // Takes 4 clock cycles
      void setRegR(uint8_t a, uint8_t b);

      // registers.select[regSelect] will = the val at address addr after this
      // call is finished. Takes 8 clock cycles
      void loadReg(uint8_t regSelect, word addr);

    private:
      ControlWord controlBus;
      word dataBus;
      word addrBus;

      Clock clock;
      RAM memory;

      // waits for next clock signal
      inline void cycle() {
        do tick(); while(!controlBus.clock);
      }

      // read from/write to the data bus
      void regIO(uint8_t regSelect, bool write);
 };

};

#endif

