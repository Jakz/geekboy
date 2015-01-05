#ifndef _GB_SOUND_H_
#define _GB_SOUND_H_

#include <set>
#include "utils.h"
#include "cpu.h"
#include "memory.h"
#include "emulator.h"

#include <SDL.h>
#include <SDL_audio.h>
#include <queue>
#include <cmath>

#include "blarrg/Basic_Gb_Apu.h"
#include "blarrg/Sound_Queue.h"

namespace gb {

const int FREQUENCY = 44100;

class GBSound
{
  private:
    Sound_Queue bQueue;
    Basic_Gb_Apu bApu;

  public:
    GBSound();
    void reset();
    void updateSound(s32 clocks);
    void updateCounters(int clocks);

    void write(u16 address, u8 value);
    u8 read(u16 address);
  
    void fillBuffer(u8 *stream, int length);
    static void callback(void *sound, Uint8 *stream, int length);
  
    void init_steps();
    void add_step(double time, double delta, double delta2);
  
    void update()
    {
      bApu.end_frame();
      writeBlarggSamples();
    }
  
    void writeBlarggSamples()
    {
      int const buf_size = 2048;
      static blip_sample_t buf [buf_size];
      // Play whatever samples are available
      long count = bApu.read_samples( buf, buf_size );
      bQueue.write( buf, count );
    }
};
  
}

#endif