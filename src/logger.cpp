#include <chrono>
#include <logger.hpp>
#include <iostream>

namespace IMCC_Emulator {
  void Logger::update(void *data) {
    auto self = (Logger *)data;

    using std::chrono::high_resolution_clock;
    using std::chrono::system_clock;
    using std::chrono::duration;
    using std::chrono::seconds;

    static system_clock::time_point last;

    static double pollTime = 0.0;
    constexpr double pollLimit = 1.0/180;

    auto now = high_resolution_clock::now();
    duration<double> dur = now - last;

    double dt = dur.count();
    last = now;

    static size_t clockCycles = 0;
    clockCycles += self->pCpu->controlBus.clock;

    if( (pollTime += dt) < pollLimit )
      return;

    std::cerr << std::format(
        "\033[2J\033[H"
        "Flags: 0b{:016b}\n"
        "MAR: 0b{:016b}\n"
        "MDR: 0b{:016b}\n"
        "Accumulator: 0b{:016b}\n"
        "Opcode: 0b{:016b}\n"
        "Operand: 0b{:016b}\n"
        "Program Counter: 0b{:016b}\n"
        "\n"
        "Control Bus: 0b{:016b}\n"
        "Data Bus: 0b{:016b}\n"
        "CPU Clock Speed: {:.2f}Hz\n"
        "Simulation Speed: {:.2f}MHz\n"
        , self->pRegisters->select[RS_FLAGS]
        , self->pRegisters->select[RS_MEM_ADDR]
        , self->pRegisters->select[RS_MEM_DATA]
        , self->pRegisters->select[RS_ACC]
        , self->pRegisters->select[RS_CIR_OP]
        , self->pRegisters->select[RS_CIR_DATA]
        , self->pRegisters->select[RS_PC]

        , *(uint8_t *)&self->pCpu->controlBus
        , self->pCpu->dataBus
        , (double)clockCycles / pollLimit
        , 0.00'000'1 / dt);

    pollTime = 0.0;
    clockCycles = 0;
  }
}

