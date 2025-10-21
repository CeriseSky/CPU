#include <chrono>
#include <logger.hpp>
#include <iostream>
#include <print>

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

    self->clockCycles += self->pCpu->controlBus.clock;

    if( (pollTime += dt) < pollLimit )
      return;

    self->log();
    std::println("Simulation Speed: {:.2f}MHz", 0.00'000'1 / dt);

    pollTime = 0.0;
  }

  void Logger::log() {
    std::print(std::cerr,
        "\033[2J\033[H"

        "Memory Address Register: 0b{:016b}\n"
        "Memory Data Register: 0b{:016b}\n"
        "\n"

        "Accumulator: 0b{:016b}\n"
        "Flags: 0b{:016b}\n"
        "Program Counter: 0x{:02x}\n"
        "\n"

        "Opcode: 0b{:016b}\n"
        "Operand: 0b{:016b}\n"
        "\n"

        "Control Bus: 0b{:016b}\n"
        "Data Bus: 0b{:016b}\n"
        "\n"

        "Total Clock Cycles: {}\n"

        , pRegisters->select[RS_MEM_ADDR]
        , pRegisters->select[RS_MEM_DATA]

        , pRegisters->select[RS_ACC]
        , pRegisters->select[RS_FLAGS]
        , pRegisters->select[RS_PC]

        , pRegisters->select[RS_CIR_OP]
        , pRegisters->select[RS_CIR_DATA]

        , *(uint8_t*)&pCpu->controlBus
        , pCpu->dataBus

        , clockCycles
        );
  }
}

