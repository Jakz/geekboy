#ifndef _GB_SOUND_H_
#define _GB_SOUND_H_

#include <set>
#include "utils.h"
#include "cpu.h"
#include "memory.h"

#include <SDL.h>
#include <SDL_audio.h>
#include <queue>
#include <cmath>
#include <memory>

#include "blarrg/Basic_Gb_Apu.h"
#include "blarrg/Sound_Queue.h"

namespace gb {

class GBSound
{
  private:
    Sound_Queue bQueue;
    std::unique_ptr<Basic_Gb_Apu> bApu;

  public:
    GBSound();
    void reset();

    void start(const int sampleRate);

    void write(u16 address, u8 value);
    u8 read(u16 address);

    void update()
    {
      bApu->end_frame();
      writeBlarggSamples();
    }

    void writeBlarggSamples()
    {
      constexpr int buf_size = 2048;
      static blip_sample_t buf [buf_size];
      // Play whatever samples are available
      long count = bApu->read_samples( buf, buf_size );
      bQueue.write( buf, count );
    }
};

}

#endif
