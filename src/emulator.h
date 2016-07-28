#ifndef _GB_EMULATOR_H_
#define _GB_EMULATOR_H_

#include "utils.h"

#include "display.h"
#ifndef DEBUGGER
#include "sound.h"
#endif
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
  void timerTrigger();

  bool doubleSpeed;
  bool lcdChangedState;

public:
  Emulator();

  void init();
  
  void setupSound(int sampleRate);


  void resetTimerCounter();
  void resetDivCounter();
  u32 timerTicks();


  u8 step();
  bool run(u32 cycles);

  void requestInterrupt(Interrupt interrupt);

  u64 cycles;
  Mode mode;

  static constexpr u32 timerFrequencies[4] = {KB4, 262144, 65536, KB16};

  void keyPressed(Key key);
  void keyReleased(Key key);
  u8 keyPadState(u8 writeValue) const;


  CpuGB cpu;
  Memory mem;
  Display<PixelFormat::ARGB51>* display;
#ifndef DEBUGGER
  GBSound sound;
#endif

  const EmuSpec spec = {160,144};
  
  void toggleLcdState() { lcdChangedState = true; }
  
  void toggleDoubleSpeed(bool value) { doubleSpeed = value; }
  bool isDoubleSpeedEnabled() const;
  
};
  
}

#endif