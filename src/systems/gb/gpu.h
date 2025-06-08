#ifndef _GB_DISPLAY_H_
#define _GB_DISPLAY_H_

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <type_traits>

#include "gbspec.h"
#include "utils.h"

namespace gb
{
  class Emulator;
  class Memory;
  class Mos6502;

  enum DrawLayer
  {
    LAYER_SPRITE = 0,
    LAYER_BACKGROUND = 1
  };

  enum DrawLayer;
  enum PriorityType : u8;

  using pixel_t = uint32_t;

  class GpuGB
  {
  private:
    pixel_t* buffer;
    PriorityType *priorityMap;
    const u32 width, height;

    Memory& mem;

    Emulator& emu;

    // current scanline progression counter from CYCLES_PER_SCANLINE to 0
    s16 scanlineCounter;
    u8 line;
  
    enum Mode
    {
      HBLANK = 0,
      VBLANK = 1,
      OAM_TRANSFER = 2,
      OAM_VRAM_TRANSFER = 3
    };

    const pixel_t bcolors[4];

    void setMode(u8& reg, Mode mode) const { reg &= ~0x03; reg |= mode; }
    void manageSTAT();
    bool isEnabled();

  public:

    GpuGB(Memory& memory, Emulator& emu, const EmuSpec& spec);
    ~GpuGB();
    void setBuffer(pixel_t* buffer) { this->buffer = buffer; }

    void init();
    void reset();
    void update(u8 cycles);

  protected:
    void drawScanline(u8 line);

    void drawTiles(u8 line);
    void drawWindow(u8 line);
    void drawSprites(u8 line);
  
  public:
    void colorsForPalette(DrawLayer layer, u8 index, pixel_t(&palette)[4]);
    s16 getScanlineCounter() const { return scanlineCounter; }

    static pixel_t ccc(u8 r, u8 g, u8 b);
  };
}

#endif