#include "sound.h"

using namespace gb;

GBSound::GBSound() : bApu(std::unique_ptr<Basic_Gb_Apu>(new Basic_Gb_Apu()))
{

}

void GBSound::start(const int sampleRate)
{
  bApu->set_sample_rate(sampleRate);
  bQueue.start(sampleRate, 2);
}

void GBSound::reset()
{
  bQueue.stop();
}

void GBSound::write(u16 address, u8 value)
{
  bApu->write_register(address, value);
}

u8 GBSound::read(u16 address)
{
  return bApu->read_register(address);
}
