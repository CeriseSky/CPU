#include <architecture.hpp>
#include <fstream>
#include <signals.hpp>
#include <stdexcept>
#include <vector>

namespace IMCC_Emulator {

  class ROM {
    static constexpr uint8_t initVal = 0xe5;

    public:
      ROM(const char *path, word *pAddrBus, ControlWord *pControlBus,
          word *pDataBus, word *pMar, word *pMdr) :
        pAddrBus(pAddrBus),
        pControlBus(pControlBus),
        pDataBus(pDataBus),
        pMar(pMar), pMdr(pMdr) {
          std::fstream file(path);
          if(!file.is_open())
            throw std::runtime_error("Failed to open ROM file");

          file.seekg(std::ios::end);
          size_t size = file.tellg();
          storage.resize(size);
          file.seekg(std::ios::beg);
          file.read((char *)storage.data(), size);
          if(file.fail())
            throw std::runtime_error("Failed to read ROM file");
        }

      static void update(void *data);

    private:
      word *pAddrBus;
      ControlWord *pControlBus;
      word *pDataBus;

      word *pMar;
      word *pMdr;

      std::vector<word> storage;
  };
}

