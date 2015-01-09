#ifndef _GB_GBSPEC_H_
#define _GB_GBSPEC_H_

#include "utils.h"

namespace gb
{

  const u16 PORT_JOYP = 0xFF00;

  const u16 PORT_SB = 0xFF01;

  const u16 PORT_DIV = 0xFF04;
  const u16 PORT_TIMA = 0xFF05;
  const u16 PORT_TMA = 0xFF06;
  const u16 PORT_TAC = 0xFF07;

  const u16 PORT_LCDC = 0xFF40;
  const u16 PORT_STAT = 0xFF41;
  const u16 PORT_LY = 0xFF44;
  const u16 PORT_LYC = 0xFF45;
  const u16 PORT_DMA = 0xFF46;
  const u16 PORT_BGP = 0xFF47;
  const u16 PORT_OBP0 = 0xFF48;
  const u16 PORT_OBP1 = 0xFF49;

  const u16 PORT_SCY = 0xFF42;
  const u16 PORT_SCX = 0xFF43;
  const u16 PORT_WY = 0xFF4A;
  const u16 PORT_WX = 0xFF4B;

  const u16 PORT_HDMA1 = 0xFF51;
  const u16 PORT_HDMA2 = 0xFF52;
  const u16 PORT_HDMA3 = 0xFF53;
  const u16 PORT_HDMA4 = 0xFF54;
  const u16 PORT_HDMA5 = 0xFF55;

  const u16 PORT_BGPI = 0xFF68;
  const u16 PORT_BGPD = 0xFF69;
  const u16 PORT_OBPI = 0xFF6A;
  const u16 PORT_OBPD = 0xFF6B;

  const u16 PORT_VBK = 0xFF4F; // switch vram bank in cgb
  const u16 PORT_SVBK = 0xFF70; // switch wram in cgb
  const u16 PORT_KEY1 = 0xFF4D;

  const u16 PORT_NR10 = 0xFF10;
  const u16 PORT_NR11 = 0xFF11;
  const u16 PORT_NR12 = 0xFF12;
  const u16 PORT_NR13 = 0xFF13;
  const u16 PORT_NR14 = 0xFF14;

  const u16 PORT_NR20 = 0xFF15;
  const u16 PORT_NR21 = 0xFF16;
  const u16 PORT_NR22 = 0xFF17;
  const u16 PORT_NR23 = 0xFF18;
  const u16 PORT_NR24 = 0xFF19;

  const u16 PORT_NR30 = 0xFF1A;
  const u16 PORT_NR31 = 0xFF1B;
  const u16 PORT_NR32 = 0xFF1C;
  const u16 PORT_NR33 = 0xFF1D;
  const u16 PORT_NR34 = 0xFF1E;

  const u16 PORT_NR40 = 0xFF1F;
  const u16 PORT_NR41 = 0xFF20;
  const u16 PORT_NR42 = 0xFF21;
  const u16 PORT_NR43 = 0xFF22;
  const u16 PORT_NR44 = 0xFF23;

  const u16 PORT_NR50 = 0xFF24;
  const u16 PORT_NR51 = 0xFF25;
  const u16 PORT_NR52 = 0xFF26;

  const u16 PORT_IF = 0xFF0F;
  const u16 PORT_EF = 0xFFFF;



  const u32 DIVIDER_REGISTER_TICK = gb::KB16;

  const u32 CYCLES_PER_SECOND = 4194304;
  const u32 CYCLES_PER_REFRESH = 70224;
  const u32 CYCLES_PER_VBLANK = 4560;
  const u32 CYCLES_PER_SCANLINE = 456;
  const u32 CYCLES_PER_OAV_TRANSFER = 80;
  const u32 CYCLES_PER_OAV_VRAM_TRANSFER = 172;
  const u32 CYCLES_PER_DIVIDER_INCR = (CYCLES_PER_SECOND/DIVIDER_REGISTER_TICK);



  const u32 VBLANK_START_LINE = 144;
  const u32 VBLANK_END_LINE = 153;

  const u16 TILE_BYTES_SIZE = 16;
  const u16 TILE_WIDTH = 8;
  const u16 TILE_HEIGHT = 8;
  const u16 TILE_MAP_WIDTH = 32;
  const u16 TILE_MAP_HEIGHT = 32;

  const u16 TILE_DATA1 = 0x8000;
  const u16 TILE_DATA2 = 0x8800;

  const u16 TILE_MAP1 = 0x9800;
  const u16 TILE_MAP2 = 0x9C00;

  const u16 SPRITE_MAX_COUNT = 40;

  enum Key
  {
    VKEY_RIGHT = 0,
    VKEY_LEFT = 1,
    VKEY_UP = 2,
    VKEY_DOWN = 3,

    VKEY_A = 4,
    VKEY_B = 5,
    VKEY_SELECT = 6,
    VKEY_START = 7
  };

  struct EmuSpec {
    const u32 displayWidth;
    const u32 displayHeight;
  };
}


#endif