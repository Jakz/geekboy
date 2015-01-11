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
  ButtonStatus oldStatus;
  
public:
  GeekBoyCore()
  {
    registerInformations({System::Type::GAME_BOY, System::Type::GAME_BOY_COLOR}, "geekboy", "Geek Boy", "0.2a");
    
    registerButton(ButtonSetting("A", GCW_KEY_A, KEY_A, true));
    registerButton(ButtonSetting("B", GCW_KEY_B, KEY_B, true));
    registerButton(ButtonSetting("Start", GCW_KEY_START, KEY_START, true));
    registerButton(ButtonSetting("Select", GCW_KEY_SELECT, KEY_SELECT, true));
    registerButton(ButtonSetting("Up", GCW_KEY_UP, KEY_UP, true));
    registerButton(ButtonSetting("Right", GCW_KEY_RIGHT, KEY_RIGHT, true));
    registerButton(ButtonSetting("Left", GCW_KEY_LEFT, KEY_LEFT, true));
    registerButton(ButtonSetting("Down", GCW_KEY_DOWN, KEY_DOWN, true));
    
    setGfxFormat(160, 144, FORMAT_565);
    
  }
  
  void emulationFrame() override
  {
    updateKeys();
    emulator->run(CYCLES_PER_REFRESH);
  }
  
  void loadRomByFileName(const std::string& name) override
  {
    emulator->getMemory()->cart->load(name.c_str());
    emulator->init();
  }
  
  void emulationSuspended() override { }
  void emulationResumed() override { }
  void emulationStopped() override { }
  void emulationStarted() override { }
  
  void initialize() {
    emulator = new Emulator();
    emulator->setupSound(36000);
    // framerate 59.73
    emulator->getDisplay()->setBuffer(reinterpret_cast<u16*>(gfxBuffer.data));
    oldStatus = 0x00;
  }
  
  void updateKeys()
  {
    for (int i = KEY_RIGHT; i <= KEY_START; ++i)
    {
      if ((oldStatus & (1 << i)) ^ (buttonStatus & (1 << i))) // old status and new status are not equal
      {
        if (buttonStatus & (1 << i)) // and now it's pressed
          emulator->keyPressed(static_cast<Key>(i));
        else
          emulator->keyReleased(static_cast<Key>(i));
      }
    }
    
    oldStatus = buttonStatus;
  }
  
  void releaseResources() override
  {
    
  }
  
  void reset() override
  {
    
  }
  
  
};

static GeekBoyCore* emulator = nullptr;;

extern "C" CoreInterface* retrieve()
{
	if (!emulator)
    emulator = new GeekBoyCore();
  
  return emulator;
}

#endif