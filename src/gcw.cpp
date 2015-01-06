#ifndef __GEEK_BOY_GCW_H__
#define __GEEK_BOY_GCW_H__

#include "../../src/core/emu_interface.h"

#include "emulator.h"

using namespace gb;
using namespace gcw;

enum KeyShift
{
  KEY_RIGHT = 0,
  KEY_LEFT = 1,
  KEY_UP = 2,
  KEY_DOWN = 3,
  
  KEY_A = 4,
  KEY_B = 5,
  KEY_SELECT = 6,
  KEY_START = 7
};

class GeekBoyCore : public CoreInterface
{
private:
  Emulator *emulator;
  
public:
  GeekBoyCore()
  {
    registerInformations(System::Type::GAME_BOY, "geekboy", "Geek Boy", "0.2a");
  }
  
  void emulationFrame() override
  {
    emulator->run(CYCLES_PER_REFRESH);
  }
  
  void loadRomByFileName(const std::string& name) override
  {
    emulator->mem.cart->load(name.c_str());
  }
  
  void emulationSuspended() override { }
  
  void emulationStarted() override { }
  
  void initialize() {
    emulator = new Emulator();
    emulator->setupSound(48000);
    // framerate 59.73
    emulator->display->setBuffer(reinterpret_cast<u16*>(gfxBuffer.data));
  }
  
  void updateKeys()
  {
    
  }
  
  void releaseResources() override
  {
    
  }
  
  void reset() override
  {
    
  }
  
  
};

static GeekBoyCore emulator;

extern "C" CoreInterface* retrieve()
{
	return &emulator;
}

#endif