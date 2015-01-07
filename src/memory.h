#ifndef _GB_MEMORY_H_
#define _GB_MEMORY_H_

#include <cstring>
#include <cstdlib>
#include "gbspec.h"
#include "cartridge.h"

#define HEADER_CGB_FLAG (0x143)

#define HEADER_CGB_FLAG_CGB_GB (0x80)
#define HEADER_CGB_FLAG_CGB_ONLY (0xC0)

namespace gb {
  class Emulator;
  
/*
	COME INDIRIZZA LO Z80 SUL GAMEBOY
	
	0000-3FFF*   16KB ROM Bank 00     (in cartridge, fixed at bank 00) (cartridge.h)
	4000-7FFF*   16KB ROM Bank 01..NN (in cartridge, switchable bank number) (cartridge.h)
	8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
	A000-BFFF*   8KB External RAM     (in cartridge, switchable bank, if any) (cartridge.h)
	C000-CFFF*   4KB Work RAM Bank 0 (WRAM) (memory.h inevitabilmente, tanto è solo zona di lavoro, non si interfaccia a niente)
	D000-DFFF*   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode) (memory.h)
	E000-FDFF*   Same as C000-DDFF (ECHO)    (typically not used) (memory.h)
	FE00-FE9F   Sprite Attribute Table (OAM)
	FEA0-FEFF   Not Usable
	FF00-FF7F   I/O Ports
	FF80-FFFE   High RAM (HRAM)
	FFFF        Interrupt Enable Register
	
	in effetti non so se conviene suddividere in più file, per ora c'è il controllore della cart, magari serve controllore per LCD e per l'I/O generico

*/


class Cartridge;

struct MemoryMap
{
	u8 *vram_bank; // 0x8000-0x9FFF (switchabile 2 banchi in CGB)
	u8 *wram_bank_0; // 0xC000-0xCFFF - 4kb working RAM
	u8 *wram_bank_1; // 0xD000-0xDFFF - 4kb working RAM (switchabile 8 banchi in CGB)
	u8 *oam_table;  // 0xFE00-0xFE9F - sprite attribute table	
  u8 *ports_table;
  
  u8 *vram;
  u8 *color_palette_ram;
  u8 *wram;
  
  bool cgbPaletteAutoIncr[2];
};

struct HDMA
{
  u16 src, dest;
  u16 length;
  bool active;
  
  HDMA()
  {
    active = false;
  }
};

class Memory
{
  private:
    MemoryMap memory;
    
    Emulator* emu;
  
    HDMA hdma;
  
    // this function is used to intercept writes to the port addresses that may need custom behavior
    // this is the function as seen by the GB
    inline void trapPortWrite(u16 address, u8 value);
    inline u8 trapPortRead(u16 address);
  
    Memory& operator=(const Memory& other) = delete;
    Memory(const Memory& other) = delete;

  public:
    Memory(Emulator* emu);
    ~Memory();
  
    u8 read(u16 address);
    void write(u16 address, u8 value);
  
    // this write overrides the normal write function to ports address space to skip any side effect
    void rawPortWrite(u16 address, u8 value);
    u8 rawPortRead(u16 address) const;
    
    void init();
    
    void setCode(u8 *code, u16 len);
  
    Cartridge *cart;
  
    u8 readVram0(u16 address);
    u8 readVram1(u16 address);
    u8 paletteRam(u8 index);
    u8 *oam();
    
    MemoryMap *memoryMap() { return &memory; }
    HDMA *hdmaInfo() { return &hdma; }
};

}


#endif