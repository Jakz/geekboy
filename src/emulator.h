#ifndef _GB_EMULATOR_H_
#define _GB_EMULATOR_H_

#define _BLARGG_APU_
#define _NO_SOUND_

#include "utils.h"

#include "display.h"
#include "sound.h"
#include "cpu.h"

namespace gb {

template<PixelFormat T>
class Display;

class GBSound;
class Memory;
class CpuGB;

enum Mode
{
  MODE_CGB = 0,
  MODE_GB = 1,
  MODE_CGB_IN_GB = 2
};

class Emulator
{
private:

  s32 dividerCounter;
  s32 timerCounter;

  u32 cyclesAdjust;

  u8 keysState;

  bool isTimerEnabled();
  void updateTimers(u16 cycles);

  bool doubleSpeed;
  
  CpuGB* cpu;
  Memory* mem;
  Display<PixelFormat::ARGB565>* display;
  GBSound sound;

public:
  Emulator();

  void init();
  
  void setupSound(int sampleRate);


  void resetTimerCounter();
  u32 timerTicks();


  u8 step();
  bool run(u32 cycles);

  void requestInterrupt(u8 interrupt);

  u64 cycles;
  Mode mode;

  static constexpr u32 timerFrequencies[4] = {KB4, 262144, 65536, KB16};

  void keyPressed(Key key);
  void keyReleased(Key key);
  u8 keyPadState(u8 writeValue) const;

  GBSound& getSound() { return sound; }
  Display<PixelFormat::ARGB565>* getDisplay() { return display; }
  Memory* getMemory() { return mem; }


  const EmuSpec spec = {160,144};
  
  
  void toggleDoubleSpeed(bool value) { doubleSpeed = value; }
  bool isDoubleSpeedEnabled() const;
  
};
  
}

#endif