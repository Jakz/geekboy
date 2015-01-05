#include "sound.h"

using namespace gb;

void audio_callback(void*, Uint8*, int);

GBSound::GBSound()
{
  bApu.set_sample_rate(FREQUENCY);
  bQueue.start(FREQUENCY, 2);
}

void GBSound::reset()
{
  
}


void GBSound::updateSound(s32 clocks)
{

}

void GBSound::updateCounters(int clocks)
{
  
}

void GBSound::write(u16 address, u8 value)
{
  bApu.write_register(address, value);
}

u8 GBSound::read(u16 address)
{
  return bApu.read_register(address);
}


void GBSound::init_steps()
{

}


void GBSound::add_step( double time, double delta1, double delta2)
{

}







void GBSound::fillBuffer(u8 *stream, int length)
{
}

void GBSound::callback(void *sound, u8 *stream, int length)
{
  ((GBSound*)sound)->fillBuffer(stream, length);
}
