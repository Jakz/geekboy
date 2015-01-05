#ifndef _GB_DISPLAY_H_
#define _GB_DISPLAY_H_

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "gbspec.h"

#include "cpu.h"
#include "memory.h"

#include "utils.h"

namespace gb {

class Emulator;
class Memory;
class CpuGB;


struct oam
{
  u8 yPos;
  u8 xPos;
  u8 tileNumber;
  u8 flags;
};

enum DrawLayer
{
  LAYER_SPRITE = 0,
  LAYER_BACKGROUND = 1
};
  
enum PriorityType : u8
{
  PRIORITY_NONE = 0,
  PRIORITY_SPRITE = 1,
  PRIORITY_BG = 2,
  PRIORITY_MAYBE_SPRITE = 3
};
  
struct PixelStatus
{
  bool hasSprite : 1;
  u8 spriteIndex : 6;
  u8 padding : 1;
  u8 spriteX : 8;
};

template<typename T>
class Display
{
  private:
    T* buffer;
    PriorityType *priorityMap;
    const u32 width, height;

    CpuGB& cpu;
    Memory& mem;
  
    Emulator& emu;
  
    // current scanline progression counter from CYCLES_PER_SCANLINE to 0
    s16 scanlineCounter;
  
    void colorsForPalette(DrawLayer layer, u8 index, T (&palette)[4]);

  public:
    Display(CpuGB& cpu, Memory& memory, Emulator& emu);
    ~Display();
    void setBuffer(T* buffer) { this->buffer = buffer; }
    void init();
    void reset();
  
    bool isEnabled();
  
    void update(u8 cycles);
  
    void manageSTAT();
  
  
    void drawScanline(u8 line);
  
    void drawTiles(u8 line);
    void drawWindow(u8 line);
    void drawSprites(u8 line);
};
  
}

#endif