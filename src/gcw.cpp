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

#	define likely(x)       __builtin_expect((x),1)
#	define unlikely(x)     __builtin_expect((x),0)
#	define prefetch(x, y)  __builtin_prefetch((x),(y))


class GBFullBlit : public Blitter
{
  inline void gb_upscale(uint32_t *to, uint32_t *from)
  {
    uint32_t reg1, reg2, reg3, reg4;
    unsigned int x,y;
    
    /* Before:
     *    a b
     *    c d
     *    e f
     *
     * After (parenthesis = average):
     *    a      a      b      b
     *    (a,c)  (a,c)  (b,d)  (b,d)
     *    c      c      d      d
     *    (c,e)  (c,e)  (d,f)  (d,f)
     *    e      e      f      f
     */
    
    for (y=0; y < 240/5; y++) {
      for(x=0; x < 320/4; x++) {
        prefetch(to+4, 1);
        
        /* Read b-a */
        reg2 = *from;
        reg1 = reg2 & 0xffff0000;
        reg1 |= reg1 >> 16;
        
        /* Write b-b */
        *(to+1) = reg1;
        reg2 = reg2 & 0xffff;
        reg2 |= reg2 << 16;
        
        /* Write a-a */
        *to = reg2;
        
        /* Read d-c */
        reg4 = *(from + 160/2);
        reg3 = reg4 & 0xffff0000;
        reg3 |= reg3 >> 16;
        
        /* Write d-d */
        *(to + 2*320/2 +1) = reg3;
        reg4 = reg4 & 0xffff;
        reg4 |= reg4 << 16;
        
        /* Write c-c */
        *(to + 2*320/2) = reg4;
        
        /* Write (b,d)-(b,d) */
        if (unlikely(reg1 != reg3))
          reg1 = ((reg1 & 0xf7def7de) >> 1) + ((reg3 & 0xf7def7de) >> 1);
        *(to + 320/2 +1) = reg1;
        
        /* Write (a,c)-(a,c) */
        if (unlikely(reg2 != reg4))
          reg2 = ((reg2 & 0xf7def7de) >> 1) + ((reg4 & 0xf7def7de) >> 1);
        *(to + 320/2) = reg2;
        
        /* Read f-e */
        reg2 = *(from++ + 2*160/2);
        reg1 = reg2 & 0xffff0000;
        reg1 |= reg1 >> 16;
        
        /* Write f-f */
        *(to + 4*320/2 +1) = reg1;
        reg2 = reg2 & 0xffff;
        reg2 |= reg2 << 16;
        
        /* Write e-e */
        *(to + 4*320/2) = reg2;
        
        /* Write (d,f)-(d,f) */
        if (unlikely(reg2 != reg4))
          reg2 = ((reg2 & 0xf7def7de) >> 1) + ((reg4 & 0xf7def7de) >> 1);
        *(to++ + 3*320/2) = reg2;
        
        /* Write (c,e)-(c,e) */
        if (unlikely(reg1 != reg3))
          reg1 = ((reg1 & 0xf7def7de) >> 1) + ((reg3 & 0xf7def7de) >> 1);
        *(to++ + 3*320/2) = reg1;
      }
      
      to += 4*320/2;
      from += 2*160/2;
    }
  }
  
  void blit(const GfxBuffer& buffer, const Offset& offset, SDL_Surface* dest)
  {
    gb_upscale(static_cast<u32*>(dest->pixels), buffer.getData<u32>());
  }
};

class GeekBoyCore : public CoreInterface
{
private:
  Emulator *emulator;
  ButtonStatus oldStatus;
  const BlitterFactorySimple<GBFullBlit, 320, 240> fullScreenBlitter = BlitterFactorySimple<GBFullBlit, 320, 240>("Fullscreen");
  
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
    
    registerScaler(fullScreenBlitter);
    
    setGfxFormat(160, 144, FORMAT_RGB565);
    
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