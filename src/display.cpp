#include "display.h"

#include "emulator.h"

using namespace gb;

template<PixelFormat T>
Display<T>::Display(CpuGB* cpu, Memory* memory, Emulator* emu) : emu(emu), cpu(cpu), mem(memory), width(emu->spec.displayWidth), height(emu->spec.displayHeight),
bcolors{ccc(28, 31, 26),ccc(17, 24, 14),ccc(4, 13, 11),ccc(1,3,4)}
{
  priorityMap = new PriorityType[width*height];
  
  scanlineCounter = CYCLES_PER_SCANLINE;
  
  ports.lcdc = &memory->memoryMap()->ports_table[PORT_LCDC - 0xFF00];
  ports.stat = &memory->memoryMap()->ports_table[PORT_STAT - 0xFF00];
  ports.ly = &memory->memoryMap()->ports_table[PORT_LY - 0xFF00];
  ports.lyc = &memory->memoryMap()->ports_table[PORT_LYC - 0xFF00];
  ports.scx = &memory->memoryMap()->ports_table[PORT_SCX - 0xFF00];
  ports.scy = &memory->memoryMap()->ports_table[PORT_SCY - 0xFF00];
  ports.wx = &memory->memoryMap()->ports_table[PORT_WX - 0xFF00];
  ports.wy = &memory->memoryMap()->ports_table[PORT_WY - 0xFF00];
  
  init();
}

template<PixelFormat T>
Display<T>::~Display()
{
  delete [] buffer;
  delete [] priorityMap;
}

namespace gb {

template<>
Display<PixelFormat::ARGB8>::Pixel::type gb::Display<PixelFormat::ARGB8>::ccc(u8 r, u8 g, u8 b)
{
  return (r*8) << 24 | (g*8) << 16 | (b*8) << 8 | 0xFF;
}

template<>
Display<PixelFormat::ARGB51>::Pixel::type gb::Display<PixelFormat::ARGB51>::ccc(u8 r, u8 g, u8 b) 
{
  return ((r) << 11) | ((g) << 6) | ((b) << 1) | 0x1;
}

template<>
Display<PixelFormat::ARGB565>::Pixel::type gb::Display<PixelFormat::ARGB565>::ccc(u8 r, u8 g, u8 b)
{
  return ((r) << 11) | ((g << 1) << 5) | ((b) << 0);
}

};

template<PixelFormat T>
typename Display<T>::Pixel::type Display<T>::ccc(u8 r, u8 g, u8 b) { return 0; }

template<PixelFormat T>
void Display<T>::colorsForPalette(DrawLayer layer, u8 index, typename Pixel::type (&palette)[4])
{
  if (emu->mode == MODE_GB)
  {
    u8 indices;

    // if layer is monochrome bg or window then we have just a palette to choose from
    // and index passed is ignored
    if (layer == LAYER_BACKGROUND)
      indices = mem->read(PORT_BGP);
    else
    {
      if (index == 0)
        indices = mem->read(PORT_OBP0);
      else
        indices = mem->read(PORT_OBP1);
    }
    
    for (int i = 0; i < 4; ++i)
      palette[i] = bcolors[(indices >> (i*2)) & 0x03];
    
  }
  else if (emu->mode == MODE_CGB)
  {
    // color palette is made by 2 bytes per color, 4 colors so 8 bytes per palette
    // bg color palettes are stored starting at 0x00 of palette ram
    // sprite color palettes are stored starting at 0x40
    // since it's little endian we first fetch lower byte, then higher one and compose together to form the specific color
    u8 offset = (layer == LAYER_BACKGROUND ? 0x00 : 0x40) + index*4*2;
    
    u16 colors16[4];
    
    for (int i = 0; i < 4; ++i)
      colors16[i] = (mem->paletteRam(offset + 2*i)) | (mem->paletteRam(offset + 2*i + 1)<<8);
    
    // color layout is XXBBBBBGG GGGRRRRR so 5 bits per component = 32*32*32 colors
    for (int i = 0; i < 4; ++i)
    {
      u8 r = colors16[i] & 0x1F;
      u8 g = (colors16[i] >> 5) & 0x1F;
      u8 b = (colors16[i] >> 10) & 0x1F;
                  
      palette[i] = ccc(r,g,b);
    }
  }
}

template<PixelFormat T>
void Display<T>::init()
{

}

template<PixelFormat T>
void Display<T>::reset()
{
  init();
}

template<PixelFormat T>
bool Display<T>::isEnabled()
{
  return Utils::bit(*ports.lcdc, 7);
}

template<PixelFormat T>
void Display<T>::update(u8 cycles)
{
  manageSTAT();
  
  if (!isEnabled())
    return;
  
  scanlineCounter -= cycles;
  
  // cycles for a scanline expired, move to next one
  if (scanlineCounter <= 0)
  {
    u8 line = *ports.ly + 1;
    
    *ports.ly = line;
    
    // reset scanlineCounter to beginning of next line, we subtract the excess cycles just to be more precise
    scanlineCounter = CYCLES_PER_SCANLINE + scanlineCounter;
    
    // if it's a normal line then just draw it
    if (line < VBLANK_START_LINE)
      drawScanline(line);
    // if we reached V-BLANK then raise the interrupt
    else if (line == VBLANK_START_LINE)
      cpu->enableInterrupt(INT_VBLANK);
    // if we got over V-BLANK then reset the counter
    else if (line > VBLANK_END_LINE)
    {
      *ports.ly = 0;
      memset(priorityMap, PRIORITY_NONE, width*height*sizeof(PriorityType));
      drawScanline(0);
    }
    
  }
}

template<PixelFormat T>
void Display<T>::manageSTAT()
{
  u8 status = *ports.stat;
  
  if (!isEnabled())
  {
    scanlineCounter = CYCLES_PER_SCANLINE;
    
    // reset current vertical line
    *ports.ly = 0;
    
    // clear current mode by clearing 2 lower bits and then set mode 1
    status &= ~0x03;
    status = Utils::set(status, 0);
    
    // write status back
    *ports.lcdc = status;
    
    return;
  }
  
  u8 currentLine = *ports.ly;
  u8 currentMode = status & 0x03;
  
  u8 mode = 0;
  bool willRequestInterrupt = false;
  
  // if we're over line 144 then V-BLANK has started, set mode 1
  if (currentLine >= VBLANK_START_LINE)
  {
    mode = 1;
    
    // update status port
    status = Utils::set(status, 0);
    status = Utils::res(status, 1);
    
    willRequestInterrupt = Utils::bit(status, 4);
  }
  else
  {
    const u32 boundToMode2 = CYCLES_PER_SCANLINE - CYCLES_PER_OAV_TRANSFER;
    const u32 boundToMode3 = boundToMode2 - CYCLES_PER_OAV_VRAM_TRANSFER;
    
    // we're in mode 2 (oam transfer)
    if (scanlineCounter > boundToMode2)
    {
      mode = 2;
      
      status = Utils::set(status, 1);
      status = Utils::res(status, 0);
      
      willRequestInterrupt = Utils::bit(status, 5);
    }
    // we're in mode 3 (oam/vram transfer), no interrupt here
    else if (scanlineCounter > boundToMode3)
    {
      mode = 3;
      
      status = Utils::set(status, 1);
      status = Utils::set(status, 0);

    }
    // we're in mode 0, which is H-BLANK
    else
    {
      mode = 0;
      
      status = Utils::res(status, 1);
      status = Utils::res(status, 0);
      
      willRequestInterrupt = Utils::bit(status, 3);
      
      // manage HDMA if it's active
      HDMA *hdma = mem->hdmaInfo();
      if (hdma->active)
      {
        hdma->length -= 0x10;
        
        // transfer 16 bytes
        for (int i = 0; i < 0x10; ++i)
        {
          mem->write(hdma->dest, mem->read(hdma->src));
          ++hdma->dest;
          ++hdma->src;
        }
        
        if (hdma->length == 0)
        {
          hdma->active = false;
          mem->rawPortWrite(PORT_HDMA5, 0xFF);
        }
      }
    }
    
    // if  we switched to a new mode and its interrupt was enabled
    if (willRequestInterrupt && currentMode != mode)
    {
      cpu->enableInterrupt(INT_STAT);
    }
    
    // if LY == LYC we should set coincidence bit and request interrupt if the bit is enabled
    if (currentLine == *ports.lyc)
    {
      status = Utils::set(status,2);
      
      if (Utils::bit(status, 6))
      {
        cpu->enableInterrupt(INT_STAT);
      }
    }
    else
    {
      status = Utils::res(status,2);
    }
    
    *ports.stat = status;
  }
}

template<PixelFormat T>
void Display<T>::drawScanline(u8 line)
{
  u8 lcdc = *ports.lcdc;
  
  // if background is enabled draw it
  if (Utils::bit(lcdc, 0))
    drawTiles(line);
  
  // if window is enabled draw it
  if (Utils::bit(lcdc, 5))
    drawWindow(line);
  
  // if sprites are enabled draw them
  if (Utils::bit(lcdc, 1))
    drawSprites(line);
}

template<PixelFormat T>
void Display<T>::drawTiles(u8 line)
{
  u8 lcdc = *ports.lcdc;
  
  u8 *vram = mem->memoryMap()->vram;
  
  u16 tileData;
  u16 tileMap;
  bool isUnsigned = true;
  PriorityType priority = PRIORITY_NONE;
  
  // choose tile data according to bit in lcd control register
  // since in CGB tile data can be in two different banks we just use deltas from 0x8000
  // and access vram directly
  if (Utils::bit(lcdc, 4))
    tileData = 0x0000;
  else
  {
    tileData = 0x0800;
    isUnsigned = false;
  }
  
  // if mode is GB then offset of VRAM will be always 0x0000 since there is only one bank of VRAM
  // (this operation is useless, is here just to be precise in behavior)
  if (emu->mode == MODE_GB)
    tileData += 0x0000;
  
  // choose tile map according to bit in lcd control register
  if (Utils::bit(lcdc, 3))
    tileMap = TILE_MAP2;
  else
    tileMap = TILE_MAP1;
  
  // let's get the scroll values for the background tilemap
  u8 scx = *ports.scx, scy = *ports.scy;

  u16 tileAddress;
  
  
  typename Pixel::type colors[4];
  
  // if we're in mono gb mode we have just a palette for the background
  if (emu->mode == MODE_GB)
    colorsForPalette(LAYER_BACKGROUND, 0, colors);
  
  // for every pixel of the current line
  for (int i = 0; i < width; ++i)
  {
    // compute the pixel position inside the tilemap and wrap it around edges if needed
    u8 y = (line + scy) % (TILE_MAP_HEIGHT*TILE_HEIGHT);
    u8 x = (i + scx) % (TILE_MAP_WIDTH*TILE_WIDTH);
    
    // with integer division we retrieve the tile coordinate inside the tile map
    u8 tx = x / TILE_WIDTH;
    u8 ty = y / TILE_HEIGHT;
    
    // with the modulo we get the pixel coordinate inside the specific tile
    u8 px = x % TILE_WIDTH;
    u8 py = y % TILE_HEIGHT;
    
    u8 byte1, byte2;
    bool flipX = false, flipY = false;
    
    // now we retrieve the tile address, first we lookup the index in the tile map
    // then we retrieve it from tile data address according to sign of the index identifier
    if (emu->mode == MODE_GB)
    {
      u8 index = mem->read(tileMap + TILE_MAP_WIDTH*ty + tx);
      
      if (isUnsigned)
        tileAddress = tileData + TILE_BYTES_SIZE*index;
      else
        tileAddress = tileData + TILE_BYTES_SIZE*(((s8)index)+128);
      
      // get the two bytes for the correct row
      byte1 = vram[tileAddress + py*2];
      byte2 = vram[tileAddress + py*2 + 1];
    }
    // in CGB mode we should read the tile map data from vram bank 1 to read additional tile attributes
    else
    {
      u8 index = mem->read(tileMap + TILE_MAP_WIDTH*ty + tx);
      u8 tileAttributes = mem->readVram1(tileMap + TILE_MAP_WIDTH*ty + tx);
      
      colorsForPalette(LAYER_BACKGROUND, tileAttributes & 0x07 , colors);
      
      u16 vramBank = 0x0000;
      
      // correct tileData according to which bank is set in bit 3
      if (Utils::bit(tileAttributes, 3))
        vramBank = KB8;
        

      if (isUnsigned)
        tileAddress = vramBank + tileData + TILE_BYTES_SIZE*index;
      else
        tileAddress = vramBank + tileData + TILE_BYTES_SIZE*(((s8)index)+128);

      flipX = Utils::bit(tileAttributes, 5);
      flipY = Utils::bit(tileAttributes, 6);
      
      if (!Utils::bit(tileAttributes,7))
        priority = PRIORITY_SPRITE;
      
      if (flipY)
        py = 7 - py;

      byte1 = vram[tileAddress + py*2];
      byte2 = vram[tileAddress + py*2 + 1];
    }
  
    // we can cache the current row and keep on until reaching the last pixel of the current line
    // or the end of the tile
    do {
      // shift them to get the correct bit for x in position 0 and build the palette index by
      // shifting lower bit to the left for the most significant bit of palette
      u8 index;
      if (!flipX)
        index = ((byte2 >> (7 - px)) & 0x01) << 1 | ((byte1 >> (7 - px)) & 0x01);
      else
        index = ((byte2 >> px) & 0x01) << 1 | ((byte1 >> px) & 0x01);
      
      if (priority == PRIORITY_NONE)
      {
        if (index == 0)
          priority = PRIORITY_MAYBE_SPRITE;
        else
          priority = PRIORITY_BG;
      }
      
      u32 color = colors[index];
      
      // place pixel on buffer at (i, line)
      buffer[line*width+i] = color;
      priorityMap[line*width+i] = priority;
      
      // increase current pixel (i), current pixel in tile (px)
      ++px;
      if (px >= TILE_WIDTH)
        break;
      
      ++i;
      if (i >= width)
        break;

    } while (true);
  }
}

template<PixelFormat T>
void Display<T>::drawWindow(u8 line)
{
  u8 lcdc = *ports.lcdc;
  
  u16 tileData;
  u16 tileMap;
  bool isUnsigned = true;
  PriorityType priority = PRIORITY_NONE;
  
  // choose tile data according to bit in lcd control register
  if (Utils::bit(lcdc, 4))
    tileData = TILE_DATA1;
  else
  {
    tileData = TILE_DATA2;
    isUnsigned = false;
  }
  
  // choose tile map according to bit in lcd control register
  if (Utils::bit(lcdc, 6))
    tileMap = TILE_MAP2;
  else
    tileMap = TILE_MAP1;
  
  // let's get the scroll values for the background tilemap
  s16 wx = *ports.wx - 7;
  s16 wy = *ports.wy;
  
  u16 tileAddress;
  
  
  typename Pixel::type colors[4];
  
  bool flipX = false, flipY = false;
  
  // if we're in mono gb mode we have just a palette for the background
  if (emu->mode == MODE_GB)
    colorsForPalette(LAYER_BACKGROUND, 0, colors);
  
  // for every pixel of the current line
  for (int i = 0; i < width; ++i)
  {
    if (line >= wy && i >= wx)
    {
      // compute the pixel position inside the tilemap and wrap it around edges if needed
      u8 y = line - wy;
      u8 x = i - wx;
      
      // with integer division we retrieve the tile coordinate inside the tile map
      u8 tx = x / TILE_WIDTH;
      u8 ty = y / TILE_HEIGHT;
      
      // with the modulo we get the pixel coordinate inside the specific tile
      u8 px = x % TILE_WIDTH;
      u8 py = y % TILE_HEIGHT;
      
      u8 byte1, byte2;
      
      // now we retrieve the tile address, first we lookup the index in the tile map
      // then we retrieve it from tile data address according to sign of the index identifier
      if (emu->mode == MODE_GB)
      {
        u8 index = mem->read(tileMap + TILE_MAP_WIDTH*ty + tx);
        
        if (isUnsigned)
          tileAddress = tileData + TILE_BYTES_SIZE*index;
        else
          tileAddress = tileData + TILE_BYTES_SIZE*(((s8)index)+128);
        
        // get the two bytes for the correct row
        byte1 = mem->readVram0(tileAddress + py*2);
        byte2 = mem->readVram0(tileAddress + py*2 + 1);
      }
      // in CGB mode we should read the tile map data from vram bank 1 to read additional tile attributes
      else
      {
        u8 index = mem->read(tileMap + TILE_MAP_WIDTH*ty + tx);
        u8 tileAttributes = mem->readVram1(tileMap + TILE_MAP_WIDTH*ty + tx);
        
        if (!Utils::bit(tileAttributes,7))
          priority = PRIORITY_SPRITE;
        
        colorsForPalette(LAYER_BACKGROUND, tileAttributes & 0x07 , colors);
        
        if (isUnsigned)
          tileAddress = tileData + TILE_BYTES_SIZE*index;
        else
          tileAddress = tileData + TILE_BYTES_SIZE*(((s8)index)+128);

        flipX = Utils::bit(tileAttributes, 5);
        flipY = Utils::bit(tileAttributes, 6);
        
        if (flipY)
          py = 7 - py;
        
        // TODO priority flag
        
        // tile is from vram bank 1
        if (Utils::bit(tileAttributes, 3))
        {
          byte1 = mem->readVram1(tileAddress + py*2);
          byte2 = mem->readVram1(tileAddress + py*2 + 1);
        }
        else
        {
          byte1 = mem->readVram0(tileAddress + py*2);
          byte2 = mem->readVram0(tileAddress + py*2 + 1);
        }
      }
      
      // we can cache the current row and keep on until reaching the last pixel of the current line
      // or the end of the tile
      do {
        // shift them to get the correct bit for x in position 0 and build the palette index by
        // shifting lower bit to the left for the most significant bit of palette
        u8 index;
        
        if (!flipX)
          index = ((byte2 >> (7 - px)) & 0x01) << 1 | ((byte1 >> (7 - px)) & 0x01);
        else
          index = ((byte2 >> px) & 0x01) << 1 | ((byte1 >> px) & 0x01);
        
        /*if (priority == PRIORITY_NONE)
        {
          if (index == 0)
            priority = PRIORITY_MAYBE_SPRITE;
          else
            priority = PRIORITY_BG;
        }*/
          
        u32 color = colors[index];
        
        // place pixel on buffer at (i, line)
        //priorityMap[line*width+i] = priority;
        buffer[line*width+i] = color;
        
        // increase current pixel (i), current pixel in tile (px)
        ++px;
        if (px >= TILE_WIDTH)
          break;
        
        ++i;
        if (i >= width)
          break;
        
      } while (true);
    }
  }
}

template<PixelFormat T>
void Display<T>::drawSprites(u8 line)
{
  u8 *oam = mem->oam();
  u8 *vram = mem->memoryMap()->vram;
  bool hasBgPriority = false;
  
  
  // if mode is GB then tile data is always 0x8000, so 0x0000 since we're reading directly from VRAM
  u16 tileData = 0x0000;

  // check if sprites are 8x16
  bool doubleSize = Utils::bit(*ports.lcdc, 2);
  u8 height = doubleSize ? TILE_HEIGHT*2 : TILE_HEIGHT;
  
  for (int i = 0; i < SPRITE_MAX_COUNT; ++i)
  {
    s16 y = oam[4*i];
    s16 x = oam[4*i + 1];
    u8 index = oam[4*i + 2];
    u8 flags = oam[4*i + 3];
    hasBgPriority = Utils::bit(flags,7);
    
    // if x or y is outside bounds the sprite is hidden
    if (x == 0 || x >= 168 || y == 0 || y >= 160)
      continue;

    y -= 16;
    x -= 8;
        
    bool flipY = Utils::bit(flags, 6);
    bool flipX = Utils::bit(flags, 5);
    
    
    if (emu->mode == MODE_CGB)
    {
      if (Utils::bit(flags,3))
        tileData = KB8;
      else
        tileData = 0;
    }
    
    // TODO: manage bit 7 OBJ-to-BG priority of flags
    
    // if the sprite resides on the line we're drawing
    if (line >= y && line < y+height)
    {
      typename Pixel::type colors[4];
      
      // if mode is gb mono then just a bit is used for sprite palette, otherwise
      // lower 3 bits are used
      if (emu->mode == MODE_GB)
        colorsForPalette(LAYER_SPRITE, Utils::bit(flags, 4) ? 1 : 0, colors);
      else
        colorsForPalette(LAYER_SPRITE, flags & 0x07, colors);
      
      u8 sy;
      u16 spriteAddress;

      // if sprite is 8x8 then handling is easier
      if (!doubleSize)
      {
        // sprites resides just in first tiledata set
        spriteAddress = tileData + TILE_BYTES_SIZE*index;
        
        // row of the sprite that should be drawn
        // if sprite is vertically flipped we then start from the bottom
        sy = flipY ? (TILE_HEIGHT - 1) - (line - y) : (line - y);
                
      }
      else
      {
        sy = flipY ? (TILE_HEIGHT*2 - 1) - (line - y) : (line - y);
        
        // if line is 0-7 then it's upper tile, otherwise it's lower tile
        if (sy < 8)
          spriteAddress = tileData + TILE_BYTES_SIZE*(index & 0xFE);
        else
        {
          spriteAddress = tileData + TILE_BYTES_SIZE*(index | 0x01);
          sy %= 8;
        }
      }
      
      // get the two bytes for the correct row
      u8 byte1 = vram[spriteAddress + sy*2];
      u8 byte2 = vram[spriteAddress + sy*2 + 1];
      
      int sx = 0;
      for ( ; sx < 8 /*&& sx+x < width*/; ++sx)
      {
        if (sx+x >= 0 && sx+x < width)
        {          
          u8 index;
          
          if (!flipX)
            index = ((byte2 >> (7 - sx)) & 0x01) << 1 | ((byte1 >> (7 - sx)) & 0x01);
          else
            index = ((byte2 >> sx) & 0x01) << 1 | ((byte1 >> sx) & 0x01);
          
          u32 color = colors[index];
          
          PriorityType priority = priorityMap[line*width+x+sx];
          if (priority == PRIORITY_BG && hasBgPriority)
            continue;
          
          //if (/*priorityMap[line*width+x+sx] == PRIORITY_FORCED ||*/ (priorityMap[line*width+x+sx] == PRIORITY_POSSIBLE))
          //  continue;
          
          if (index != 0)
            buffer[line*width+x+sx] = color;
        }
      }
    }
  }
}


template Display<PixelFormat::ARGB8>::Display(CpuGB* cpu, Memory* memory, Emulator* emu);
template Display<PixelFormat::ARGB51>::Display(CpuGB* cpu, Memory* memory, Emulator* emu);
template Display<PixelFormat::ARGB565>::Display(CpuGB* cpu, Memory* memory, Emulator* emu);

template void Display<PixelFormat::ARGB8>::update(u8 cycles);
template void Display<PixelFormat::ARGB51>::update(u8 cycles);
template void Display<PixelFormat::ARGB565>::update(u8 cycles);
