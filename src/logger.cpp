#include <logger.hpp>
#include <iostream>

namespace IMCC_Emulator {
  void Logger::update(void *data) {
    auto self = (Logger *)data;

    std::cerr << std::format(
        "\033[2J\033[H"
        "Flags: 0b{:08b}\n"
        "MAR: 0b{:08b}\n"
        "MDR: 0b{:08b}\n"
        "Accumulator: 0b{:08b}\n"
        "\n"
        "Address Bus: 0b{:08b}\n"
        "Control Bus: 0b{:08b}\n"
        "Data Bus: 0b{:08b}\n"
        , self->pCpu->registers.select[RS_FLAGS]
        , self->pCpu->registers.select[RS_MEM_ADDR]
        , self->pCpu->registers.select[RS_MEM_DATA]
        , self->pCpu->registers.select[RS_ACC]

        , self->pCpu->addrBus
        , *(uint8_t *)&self->pCpu->controlBus
        , self->pCpu->dataBus);
  }
}

