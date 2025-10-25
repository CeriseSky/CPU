#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

#include <architecture.hpp>
#include <fstream>
#include <signals.hpp>
#include <stdexcept>
#include <vector>

namespace IMCC_Emulator {

  // doesn't use any address bus: instead it can be thought of as being
  // directly wired/connected to the MDR and MAR of the register set
  class ROM {
    public:
      ROM(const char *path, ControlWord *pControlBus,
          word *pMar, word *pMdr) :
        pControlBus(pControlBus),
        pMar(pMar), pMdr(pMdr) {
          std::fstream file(path);
          if(!file.is_open())
            throw std::runtime_error("Failed to open ROM file");

          file.seekg(0, std::ios::end);
          size_t size = file.tellg();
          storage.resize(size);
          file.seekg(0, std::ios::beg);
          file.read((char *)storage.data(), size);
          if(file.fail())
            throw std::runtime_error("Failed to read ROM file");
        }

      static void update(void *data);

      size_t size() { return storage.size(); }

    private:
      ControlWord *pControlBus;

      word *pMar;
      word *pMdr;

      std::vector<word> storage;
  };

  class RAM {
    public:
      RAM(size_t bytes, ControlWord *pControlBus, word *pMar, word *pMdr) :
        pControlBus(pControlBus),
        pMar(pMar),
        pMdr(pMdr),
        storage(bytes/sizeof(word), 0) {}

      static void update(void *data);

      size_t size() { return storage.size(); };

    private:
      ControlWord *pControlBus;

      word *pMar;
      word *pMdr;

      std::vector<word> storage;
  };
}

#endif

