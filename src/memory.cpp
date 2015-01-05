#include "memory.h"

#include "emulator.h"


using namespace gb;

//static u8 code[] = { (u8) 0x2E, (u8) 0x06, (u8) 0x26, (u8) 0x80, 0x36, 0x0A, (u8)0x06, (u8) 0x40, (u8)0x70, (u8)0x56, 0x3A, 0x06, 0x80};

Memory::Memory(Emulator& emu) : emu(emu)
{
  init();
  cart = new Cartridge(emu);
}

/* dealloca tutto e rialloca nuova fiammante memoria */
void Memory::init()
{
	/*free(memory.vram_bank);
   free(memory.wram_bank_0);
   free(memory.wram_bank_1);
   free(memory.oam_table);
   
   
   memory.vram_bank = NULL;
   memory.wram_bank_0 = NULL;
   memory.wram_bank_1 = NULL;
   memory.oam_table = NULL;
   */
  
  memory.vram = new u8[KB16];
  memory.vram_bank = memory.vram;
  
  memory.wram = new u8[KB32];
  memory.wram_bank_0 = memory.wram;
  memory.wram_bank_1 = &memory.wram[KB4];
  
	memory.oam_table = new u8[160];
  
  memory.ports_table = new u8[256];
  
  memory.color_palette_ram = new u8[128];
  
  memory.cgbPaletteAutoIncr[0] = false;
  memory.cgbPaletteAutoIncr[1] = false;
}

Memory::~Memory()
{
  delete [] memory.vram;
  delete [] memory.wram;
  delete [] memory.oam_table;
  delete [] memory.ports_table;
  delete [] memory.color_palette_ram;
}

void Memory::setCode(u8 *c, u16 len)
{
  //memcpy(code,c,len);
}

u8 Memory::paletteRam(u8 index)
{
  return memory.color_palette_ram[index];
}

u8 *Memory::oam()
{
  return memory.oam_table;
}

u8 Memory::readVram0(u16 address)
{
  return memory.vram[address - 0x8000];
}

u8 Memory::readVram1(u16 address)
{
  return memory.vram[address - 0x8000 + 0x2000];
}

u8 Memory::read(u16 address)
{		
	/* GB VERO */
	
	/* if address is for the ROM or ext RAM just forward it to the cartridge manager */
	if (address <= 0x7FFF || (address >= 0xA000 && address <= 0xBFFF))
		return cart->read(address);
  /* vram (switchable 0-1 CGB) */
  else if (address >= 0x8000 && address <= 0x9FFF)
    return memory.vram_bank[address - 0x8000];
	/* wram bank 0 */
	else if (address >= 0xC000 && address <= 0xCFFF)
		return memory.wram_bank_0[address - 0xC000];
	/* wram bank 1 (switchable 1-7 in CGB) */
	else if (address >= 0xD000 && address <= 0xDFFF)
		return memory.wram_bank_1[address - 0xD000];
	/* mirror working ram banco 0 */
	else if (address >= 0xE000 && address <= 0xFDFF)
		return memory.wram_bank_0[address - 0xE000];
  // oam table
  else if (address >= 0xFE00 && address <= 0xFE9F)
    return memory.oam_table[address - 0xFE00];
  // not usable
  else if (address >= 0xFEA0 && address <= 0xFEFF)
    return -1;
  // ports + HRAM
  else if (address >= 0xFF00)
    return trapPortRead(address);
	
	return 0;
		
}

void Memory::write(u16 address, u8 value)
{
	/* GB VERO */
	
	/* if address is for the ROM or ext RAM just forward it to the cartridge manager */
	if (address <= 0x7FFF || (address >= 0xA000 && address <= 0xBFFF))
		cart->write(address, value);
  /* vram */
  else if (address >= 0x8000 && address <= 0x9FFF)
    memory.vram_bank[address - 0x8000] = value;
	/* wram bank 0 */
	else if (address >= 0xC000 && address <= 0xCFFF)	
		memory.wram_bank_0[address - 0xC000] = value;
	/* wram bank 1 */
	else if (address >= 0xD000 && address <= 0xDFFF)
		memory.wram_bank_1[address - 0xD000] = value;
	/* mirror wram bank 0 */
	else if (address >= 0xE000 && address <= 0xFDFF)	
		memory.wram_bank_0[address - 0xE000] = value;
  // oam table
  else if (address >= 0xFE00 && address <= 0xFE9F)
    memory.oam_table[address - 0xFE00] = value;
  // ports + HRAM
  else if (address >= 0xFF00)
    trapPortWrite(address, value);
  
  // not usable
  //else if (address >= 0xFEA0 && address <= 0xFEFF)
}

u8 Memory::trapPortRead(u16 address)
{
  switch (address)
  {
    case PORT_JOYP:
    {
      u8 joyp = emu.keyPadState(rawPortRead(address));
      rawPortWrite(address, joyp);
      return joyp;
      break;
    }
  }
  
  return rawPortRead(address);
}


void Memory::trapPortWrite(u16 address, u8 value)
{
  if (address >= PORT_NR10 && address <= 0xFF3F)
    emu.sound->write(address, value);
  
  switch (address)
  {
    // writing on the divider register will reset it
    //case PORT_LY:
    case PORT_DIV: { 
      value = 0;
      break;
    }
    // writing on the TAC register will start/stop the timer or change its frequency
    case PORT_TAC:
    {
      //u8 oldValue = read(PORT_TAC);
      rawPortWrite(address, value);
      
      // if frequency of the timer has just to change
      emu.resetTimerCounter();
      
      return;
    }
    // switch vram bank in CGB
    case PORT_VBK:
    {
      if (Utils::bit(value, 0) && memory.vram_bank == memory.vram)
        memory.vram_bank = &memory.vram[KB8];
      else if (!Utils::bit(value, 0) && memory.vram_bank != memory.vram)
        memory.vram_bank = memory.vram;
      
      break;
    }
    // switch wram slot 1 in CGB  
    case PORT_SVBK:
    {
      u8 bank = value & 0x07;
      if (bank == 0) bank = 1;
      
      memory.wram_bank_1 = &memory.wram[bank*KB4];
      
      break;
    }
    case PORT_KEY1:
    {
      // if we're asking for a speed switch
      if (Utils::bit(value,0))
      {
        printf("SPEED SWITCH!");
        // set bit in the speed switch port to be managed by STOP instruction
        rawPortWrite(PORT_KEY1, rawPortRead(PORT_KEY1) | 0x01);
      }
      break;
    }
    // DMA transfer of 160 bytes 
    case PORT_DMA:
    {
      // multiply value by 0x100 to obtain high address
      u16 address = value << 8;
      
      for (int i = 0; i < 160; ++i)
        write(0xFE00+i, read(address+i));
      
      return;
    }
    case PORT_SB:
    {
      //printf("%c", value);
      return;
    }
    case PORT_BGPI:
    {
      // if bit 7 of background palette index is 1 then
      // it should autoincrement its value after a write
      memory.cgbPaletteAutoIncr[0] = (value & 0x80) != 0;
      break;
    }
    case PORT_BGPD:
    {
      u8 paletteByte = rawPortRead(PORT_BGPI) & 0x3F;
      
      memory.color_palette_ram[paletteByte] = value;
      
      // TODO maybe index should wrap?
      if (memory.cgbPaletteAutoIncr[0] && paletteByte < 0x40)
      {
        rawPortWrite(PORT_BGPI, paletteByte+1);
      }
      
      break;
    }
    case PORT_OBPI:
    {
      // if bit 7 of object palette index is 1 then
      // it should autoincrement its value after a write
      memory.cgbPaletteAutoIncr[1] = (value & 0x80) != 0;
      break;
    }
    case PORT_OBPD:
    {
      u8 paletteByte = 64 + (rawPortRead(PORT_OBPI) & 0x3F);
      
      memory.color_palette_ram[paletteByte] = value;
      
      // TODO maybe index should wrap?
      if (memory.cgbPaletteAutoIncr[1] && paletteByte < 0x80)
      {
        rawPortWrite(PORT_OBPI, paletteByte+1);
      }
      
      break;
    }
    /*case PORT_HDMA1:
    case PORT_HDMA2:
    case PORT_HDMA3:
    case PORT_HDMA4:*/
    case PORT_HDMA5:
    {    
      // compose source address from the two source hdma ports
      u16 source = (rawPortRead(PORT_HDMA1)<<8) | rawPortRead(PORT_HDMA2);
      // clamp address, lower 4 bits are ignored (0000-7FF0 or A000-DFF0)
      source &= 0xFFF0;
      
      // compose destination address from the two dest hdma ports
      u16 dest = (rawPortRead(PORT_HDMA3)<<8) | rawPortRead(PORT_HDMA4);
      // clamp address, lower 4 bits are ignored, 3 higher bits are ignored since destination is always VRAM (8000-9FF0)
      dest = (dest & 0x7FF0) | 0x8000;
      
      // length is lower 7 bit of this register + 1 multiplied by 10
      u16 length = ((value & 0x7F) + 1) * 10;
      
      // hblank DMA (16 bytes for every HBLANK)
      if (Utils::bit(value,7))
      {
        hdma.active = true;
        hdma.src = source;
        hdma.dest = dest;
        hdma.length = length;
        
        // we need to set bit 7 to 0 to warn that HDMA transfer is active
        value &= 0x7F;
      }
      // general purpose HDMA, everything is copied at once
      else
      {
        // if bit 7 is not set but HDMA transfer was active
        // force disable it and set bit 7 to 1 to warn that it is finished
        if (hdma.active)
        {
          hdma.active = false;
          value |= 0x80;
        }
        else
        {
        
          for (int i = 0; i < length; ++i)
            write(dest+i, read(source+i));
        
          value = 0xFF;
        }
      }
      break;
    }  
  }

  rawPortWrite(address, value);
}


void Memory::rawPortWrite(u16 address, u8 value)
{
  memory.ports_table[address - 0xFF00] = value;
}

u8 Memory::rawPortRead(u16 address) const
{
  if (address >= 0xFF10 && address <= 0xFF3F)
    return emu.sound->read(address);
  
  return memory.ports_table[address - 0xFF00];
}

