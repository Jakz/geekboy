#include "screen.h"

#include <GLUT/GLUT.h>


#include "time.h"
#include "sound.h"

#include <OpenGL/gl.h>
#include <thread>
#include <string>
#include <array>

using namespace std;
using namespace std::chrono;

void Timer::setFrameRate(float rate)
{
  totalFrames = 0;
  ticksForFrame = microseconds(static_cast<u32>(1000000 / rate));
  base = clock.now();
}

void Timer::frameRateDelay()
{
  totalFrames++;
  
  time_point<steady_clock> current = clock.now();
  time_point<steady_clock> target = base + (ticksForFrame * totalFrames);
  
  if (current <= target)
  {
    this_thread::sleep_for(target-current);
  }
  else
  {
    base = current;
    totalFrames = 0;
    // frame required more time than requested
  }
}


Screen Screen::instance;

Screen::Screen() : scaleFactor(3), speeds({CYCLES_PER_REFRESH, CYCLES_PER_REFRESH>>1, CYCLES_PER_REFRESH>>2, CYCLES_PER_REFRESH>>3, CYCLES_PER_SCANLINE, 64, 32}), speed(speeds.begin())
{
  running = true;
  fpsCap = true;
  paused = false;
  
  crender = 0;
  cloop = 0;
}

Screen *Screen::i()
{
  return &instance;
}

int width, height;

bool Screen::init()
{
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }
  
  SDL_EnableUNICODE(true);
  
  width = emu->spec.displayWidth*scaleFactor;
  height = emu->spec.displayHeight*scaleFactor;
  
  #if VRAM_DEBUG
    width = 1440;
    height = 1100;
    Font::init();
    consoleMode = false;
  #endif
  
  if((total = SDL_SetVideoMode(width, height, 32, SDL_OPENGL | SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
    return false;
  }


  glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
  //glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  glOrtho(0, width, 0, height, 0, 1.0);
  
  glClearColor(0, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_FLAT);
  
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DITHER);
	glDisable(GL_BLEND);
  
  glEnable(GL_ALPHA_TEST);
  glAlphaFunc(GL_GREATER, 0.5f);
  
  emu->init();
  
  return true;
}

float x(int xx) { return (xx - width/2) / (float)(width/2); }
float y(int yy) { return ((height - yy) / (float)(height/2)) - 1.0f; }


int Screen::execute(const string& fileName)
{
  SDL_Init(SDL_INIT_AUDIO);

  emu = new Emulator();
  emu->setupSound(48000);
  emu->mem.cart->load(fileName.c_str());
  
  screenBuffer = new u16[emu->spec.displayWidth*emu->spec.displayHeight];

  emu->display->setBuffer(screenBuffer);

  
  if (!init())
    return -1;
  
  timer.setFrameRate(59.73);
  //timer.setFrameRate(10.00);
  
  while(running)
  {
    SDL_Event event;
    
    while(SDL_PollEvent(&event))
      handleEvent(&event);
   
    if (!paused)
      loop();
    render();

    timer.frameRateDelay();
  }
  
  cleanup();
  
  return 0;
}

void Screen::capFPS(u32 start)
{
  u32 end = SDL_GetTicks();
  u32 delta = end - start;
  
  /*if (delta > 0)
  {
    char buffer[20];
    sprintf(buffer,"%d FPS",1000/delta); 
    SDL_WM_SetCaption( buffer,0 ); 
  }*/

  if (delta < 1000 / FPS )
  { 
    //Sleep the remaining frame time
    //printf("Sleeping: %d\n",( 1000 / FPS ) - delta );
    SDL_Delay( ( 1000 / FPS ) - delta); 
  } 
}

void Screen::cleanup()
{
  /*FILE *out = fopen("audio.txt", "wb");
  for (int i = 0; i < FREQUENCY; ++i)
  {
    fprintf(out, "%.2u:%.04u   %+d\n",i/BUFFER_SIZE, i%BUFFER_SIZE, emu->sound->checkBuffer[i]);
  }
  
  s32 v = 10000;
  u32 ctr = 0;
  s16 *buffer = emu->sound->checkBuffer;
  for (int i = 0; i < FREQUENCY; ++i)
  {
    if (i == 0)
    {
      ++ctr;
      v = buffer[i];
    }
    else
    {
      if ((buffer[i] > 0 && v < 0) || (buffer[i] < 0 && v > 0) || buffer[i] == -1)
      {
        fprintf(out, "STRAIN %c, %u\n",v > 0 ? '+' : '-',ctr);
        
        if (buffer[i] == -1)
          break;
        
        v = buffer[i];
        ctr = 0;

      }
      else
        ++ctr;
    }
  
  }
  
  fclose(out);*/
  
  emu->mem.cart->dumpSave();
  
  SDL_FreeSurface(total);
  SDL_Quit();
  
  printf("SECONDS LOOP: %f\n",cloop/(float)CLOCKS_PER_SEC);
  printf("SECONDS RENDER: %f\n",crender/(float)CLOCKS_PER_SEC);
}

void Screen::handleEvent(SDL_Event *event)
{
  switch (event->type)
  {
    case SDL_QUIT: { running = false; break; }
    case SDL_KEYDOWN:
    {
#ifdef VRAM_DEBUG
      auto sym = event->key.keysym.sym;
      
      if (consoleMode && sym < 0x80)
      {
        if (sym == SDLK_BACKSPACE)
        {
          if (console.length() > 1)
            console.pop_back();
        }
        else if (sym == SDLK_RETURN)
        {
          consoleMode = false;
          console = ">";
        }
        else
          console += event->key.keysym.unicode;
        return;
      }
#endif
      switch (event->key.keysym.sym)
      {
        case SDLK_LEFT: { emu->keyPressed(VKEY_LEFT); break; }
        case SDLK_RIGHT: { emu->keyPressed(VKEY_RIGHT); break; }
        case SDLK_UP: { emu->keyPressed(VKEY_UP); break; }
        case SDLK_DOWN: { emu->keyPressed(VKEY_DOWN); break; }
          
        case SDLK_a: { emu->keyPressed(VKEY_A); break; }
        case SDLK_s: { emu->keyPressed(VKEY_B); break; }
        case SDLK_q: { emu->keyPressed(VKEY_START); break; }
        case SDLK_w: { emu->keyPressed(VKEY_SELECT); break; }
          
        case SDLK_ESCAPE: { running = false; break; }
        case SDLK_SPACE: { fpsCap = false; break; }
        case SDLK_p: { paused = !paused; break; }
          
        case SDLK_KP_PLUS: { if (speed != speeds.begin()) --speed; break; }
        case SDLK_KP_MINUS: { if (speed != speeds.end()-1) ++speed; break; }
          
        case SDLK_n: { if (!paused) emu->step(); break; }
          
#ifdef VRAM_DEBUG
        case SDLK_WORLD_0: { consoleMode = !consoleMode; console = ">"; break; }
#endif
          
        default: break;
      }
      break;
    }
    case SDL_KEYUP:
    {
      switch (event->key.keysym.sym)
      {
        case SDLK_LEFT: { emu->keyReleased(VKEY_LEFT); break; }
        case SDLK_RIGHT: { emu->keyReleased(VKEY_RIGHT); break; }
        case SDLK_UP: { emu->keyReleased(VKEY_UP); break; }
        case SDLK_DOWN: { emu->keyReleased(VKEY_DOWN); break; }
          
        case SDLK_a: { emu->keyReleased(VKEY_A); break; }
        case SDLK_s: { emu->keyReleased(VKEY_B); break; }
        case SDLK_q: { emu->keyReleased(VKEY_START); break; }
        case SDLK_w: { emu->keyReleased(VKEY_SELECT); break; }
          
        case SDLK_SPACE: { fpsCap = true; break; }
          
        default: break;
      }
      break;
    }
  }
}

void Screen::loop()
{
  if (!emu->run(*speed))
    running = false;
}

void Screen::draw(int xx, int yy, float scale, const void* data, int width, int height)
{
  glRasterPos2f(x(xx), y(yy));
  glPixelZoom(scale, -scale);
  glPixelStoref(GL_UNPACK_ALIGNMENT, 1);
  glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data);
}

void Screen::drawString(const std::string& txt, int x, int y, float scale)
{
  int sx = x;
  static pixel_type buffer[Font::WIDTH*Font::HEIGHT];
  static const pixel_type color = gb::Display<gb::PixelFormat::ARGB51>::ccc(31, 31, 31);

  for (auto c : txt)
  {
    if (c == '\n')
    {
      x = sx;
      y += 10*scale;
      continue;
    }
    
    const bool* data = Font::glyph(c);
    
    for (size_t i = 0; i < Font::WIDTH*Font::HEIGHT; ++i)
      buffer[i] = data[i] ? color: 0;
    
    draw(x, y, scale, buffer, Font::WIDTH, Font::HEIGHT);
    
    x += (Font::WIDTH+1)*scale;
  }
}

void Screen::render()
{
  #if VRAM_DEBUG
  glClearColor(0.3, 0.3, 0.3, 1.0);
  #endif
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	glLoadIdentity();
  
  draw(0, 0, scaleFactor, screenBuffer, emu->spec.displayWidth, emu->spec.displayHeight);

  #if VRAM_DEBUG
  renderVRAM();
  renderRegs();
  
  if (consoleMode)
    drawString(console, 1100, 900, 1);
  
  #endif

	SDL_GL_SwapBuffers();
}

#if VRAM_DEBUG
void Screen::renderVRAM()
{
  renderTileData(tileData1, emu->mem.memoryMap()->vram);
  glRasterPos2f(0.0, 1);
	glPixelZoom(static_cast<float>(2), -static_cast<float>(2));
 	glDrawPixels(128, 192, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, tileData1);
  
  renderTileData(tileData2, &emu->mem.memoryMap()->vram[KB8]);
  glRasterPos2f(0.5, 1);
	glPixelZoom(static_cast<float>(2), -static_cast<float>(2));
 	glDrawPixels(128, 192, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, tileData2);

  renderTileMap(tileMap1, TILE_MAP1);
  glRasterPos2f(-1, 0.1);
	glPixelZoom(static_cast<float>(2), -static_cast<float>(2));
 	glDrawPixels(256, 256, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, tileMap1);
  
  renderTileMap(tileMap2, TILE_MAP2);
  glRasterPos2f(-0.25f, 0.1);
	glPixelZoom(static_cast<float>(2), -static_cast<float>(2));
 	glDrawPixels(256, 256, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, tileMap2);
  
  renderSpriteInfo(20, height - 50);

  if (emu->mode == MODE_GB)
    renderGbPalette();
  else
    renderCgbPalette();
  
  renderCurrentScanline();
}

static char buffer[256];

template<size_t SIZE> void Screen::renderPorts(const std::array<PortSpec, SIZE>& ports, int x, int y)
{
  auto& mem = emu->mem;

  for (const auto& spec : ports)
  {
    sprintf(buffer, "%04X %02Xh (%s)", spec.address, mem.rawPortRead(spec.address), spec.name);
    drawString(buffer, x, y, 1);
    y += 10;
  }
}

void Screen::renderRegs()
{
  const auto& regs = *emu->cpu.regs();
  auto& mem = emu->mem;
  
  Opcodes::visualOpcode(buffer, mem.read(regs.PC), mem.read(regs.PC+1), mem.read(regs.PC+2));
  drawString(buffer, 1100, 650, 1);

  sprintf(buffer, "SPEED %u", *speed);
  drawString(buffer, 1100, 660, 1);
  
  sprintf(buffer, "PC %04xh", regs.PC);
  drawString(buffer, 1100, 700, 1);
  
  sprintf(buffer, "AF %04xh BC %04xh", regs.AF.AF, regs.BC.BC);
  drawString(buffer, 1100, 710, 1);
  
  sprintf(buffer, "DE %04xh HL %04xh", regs.DE.DE, regs.HL.HL);
  drawString(buffer, 1100, 720, 1);
  
  sprintf(buffer, "SP %04xh IF %02xh IE %02xh", regs.SP, mem.read(PORT_IF), mem.read(PORT_EF));
  drawString(buffer, 1100, 730, 1);
  
  std::array<PortSpec, 5> specst = { { {PORT_DIV, "DIV"}, {PORT_TIMA, "TIMA"}, {PORT_TMA, "TMA"}, {PORT_TAC, "TAC"}, {PORT_JOYP, "JOYP"} } };
  renderPorts(specst, 1100, 750);
  
  std::array<PortSpec, 8> specsd = { { {PORT_LCDC, "LCDC"}, {PORT_STAT, "STAT"}, {PORT_SCY, "SCY"}, {PORT_SCX, "SCX"}, {PORT_LY, "LY"}, {PORT_LYC, "LYC"}, {PORT_WY, "WY"}, {PORT_WX, "WX"} } };
  renderPorts(specsd, 1100, 810);
  
  u8 lcdc = mem.rawPortRead(PORT_LCDC);
  
  sprintf(buffer, "LCD: %d\nWindow Tile Map: %d (%s)\nWindow: %s\nTile Data: %d (%s)\nBG Tile Map: %d (%s)\nSprite Size: %d (%s)\nSprites: %s\nBG Mode: %d",
          Utils::bit(lcdc, 7),
          Utils::bit(lcdc, 6), Utils::bit(lcdc, 6) ? "9C00h" : "9800h",
          Utils::bit(lcdc, 5) ? "on" : "off",
          Utils::bit(lcdc, 4), Utils::bit(lcdc, 4) ? "8000h" : "8800h",
          Utils::bit(lcdc, 3), Utils::bit(lcdc, 3) ? "9C00h" : "9800h",
          Utils::bit(lcdc, 2), Utils::bit(lcdc, 2) ? "8x16" : "8x8",
          Utils::bit(lcdc, 1) ? "on" : "off",
          Utils::bit(lcdc, 0) ? 1 : 0
  );
  drawString(buffer, 1200, 810, 1);
  
}

void Screen::renderCurrentScanline()
{
  //if (speed > speeds.begin())
  {
    static const pixel_type color = gb::Display<gb::PixelFormat::ARGB51>::ccc(31, 0, 0);
    
    u8 scanline = emu->mem.rawPortRead(PORT_LY);

    draw(emu->spec.displayWidth*scaleFactor, scanline*scaleFactor, scaleFactor, &color, 1, 1);
  }
}

void Screen::renderTileData(pixel_type *dest, u8 *data)
{
  Display<PixelFormat::ARGB51>::Pixel::type colors[4];
  u16 address;
  emu->display->colorsForPalette(LAYER_BACKGROUND, 0, colors);

  for (int i = 0; i < (0x9800 - 0x8000) / 16; ++i)
  {
    address = i*16;
    for (int y = 0; y < 8; ++y)
    {
      u8 byte1 = data[address + y*2];
      u8 byte2 = data[address + y*2 + 1];
      
      for (int x = 0; x < 8; ++x)
      {
        u8 index = ((byte2 >> (7 - x)) & 0x01) << 1 | ((byte1 >> (7 - x)) & 0x01);
        pixel_type color = colors[index];
        
        int fx = (i%16)*8 + x;
        int fy = (i/16)*8 + y;
        
        dest[(fy)*128 + fx] = color;
      }
    }
  }
}

void Screen::renderTileMap(pixel_type *dest, u16 address)
{
  u8 lcdc = emu->mem.read(PORT_LCDC);
  bool isUnsigned = Utils::bit(lcdc, 4);
  
  pixel_type* tileData = tileData1;//emu->mem.memoryMap()->vram_bank;
  
  for (int i = 0; i < 32; ++i)
    for (int j = 0; j < 32; ++j)
    {
      s16 index;
      if (isUnsigned) index = emu->mem.readVram0(address+32*i+j);
      else index = (s8)emu->mem.readVram0(address+32*i+j) + 256;
      
      for (int k = 0; k < 8; ++k)
      {
        int sp = ((index/16)*8+k)*128 + (index%16)*8;
        int dp = (i*8+k)*256 + j*8;
        
        memcpy(&dest[dp], &tileData[sp], sizeof(pixel_type)*8);
      }
      //SDL_BlitSurface(tileData,&src,total,&dest);
    }
  
  if (!(Utils::bit(lcdc, 3) ^ (address == TILE_MAP2)))
  {
    pixel_type edge = gb::Display<gb::PixelFormat::ARGB51>::ccc(31, 0, 0);
    
    u8 scx = emu->mem.read(PORT_SCX);
    u8 scy = emu->mem.read(PORT_SCY);
    
    for (int x = 0; x < 160; ++x)
    {
      int fx = (x + scx)%256;
      int fy = scy, sy = (scy+144)%256;

      dest[fy*256 + fx] = edge;
      dest[sy*256 + fx] = edge;
    }
    
    for (int y = 0; y < 144; ++y)
    {
      int fy = (y + scy)%256;
      int fx = scx, sx = (scx+160)%256;
      
      dest[fy*256 + fx] = edge;
      dest[fy*256 + sx] = edge;
    }
  }
  
  if (!(Utils::bit(lcdc, 6) ^ (address == TILE_MAP2)) && Utils::bit(lcdc, 5))
  {
    pixel_type edge = gb::Display<gb::PixelFormat::ARGB51>::ccc(0, 31, 0);

    
    int wx = emu->mem.read(PORT_WX) - 7;
    int wy = emu->mem.read(PORT_WY);
    
    for (int x = 0; x < 160; ++x)
    {
      int fx = (x + wx)%256;
      int fy = wy, sy = (wy+144)%256;
      
      dest[fy*256 + fx] = edge;
      dest[sy*256 + fx] = edge;
    }
    
    for (int y = 0; y < 144; ++y)
    {
      int fy = (y + wy)%256;
      int fx = wx, sx = (wx+160)%256;
      
      dest[fy*256 + fx] = edge;
      dest[fy*256 + sx] = edge;
    }
  }

  
}

void Screen::renderSpriteInfo(int x, int y)
{
  const u8* oam = emu->mem.oam();
  constexpr float SCALE = 2;
  
  renderSprites(sprites, oam, emu->mem.memoryMap()->vram);
  draw(x, y, SCALE, sprites, SPRITE_MAX_COUNT*(SPRITE_SIZE+SPRITE_MARGIN), SPRITE_SIZE*2);
  
  for (int i = 0; i < SPRITE_MAX_COUNT; ++i)
  {
    const u8* soam = &oam[i*4];
    
    u8 yy = soam[0];
    u8 xx = soam[1];
    
    sprintf(buffer, "%u\n%u", xx, yy);
    
    drawString(buffer, x + i*(SPRITE_SIZE+SPRITE_MARGIN)*SCALE, y-25, 1);
  }
}

void Screen::renderSprites(pixel_type* dest, const u8* oams, u8* vram_total)
{
  static const pixel_type black = gb::Display<gb::PixelFormat::ARGB51>::ccc(0, 0, 0);
  
  for (size_t i = 0; i < SPRITE_MAX_COUNT*SPRITE_SIZE*(SPRITE_SIZE+SPRITE_MARGIN)*2; ++i)
    dest[i] = black;
  
  
  pixel_type colors[4];
  
  bool doubleSize = Utils::bit(emu->mem.read(PORT_LCDC), 2);

  for (int i = 0; i < SPRITE_MAX_COUNT; ++i)
  {
    const u8* oam = &oams[i*4];
    
    /*u8 x = oam[0];
    u8 y = oam[1];*/
    u8 index = oam[2];
    u8 attrs = oam[3];

    bool flipY = Utils::bit(attrs, 6);
    bool flipX = Utils::bit(attrs, 5);
    
    u8* vram = vram_total;
    
    if (emu->mode == MODE_CGB)
    {
      if (Utils::bit(attrs, 3))
        vram = &vram[KB8];
      
      emu->display->colorsForPalette(LAYER_SPRITE, attrs & 0x07, colors);
    }
    else
      emu->display->colorsForPalette(LAYER_SPRITE, Utils::bit(attrs, 4) ? 1 : 0, colors);
    
    u8* spriteAddress;

    if (!doubleSize)
      spriteAddress = vram + TILE_BYTES_SIZE*index;
    else
      spriteAddress = vram + TILE_BYTES_SIZE*(index & 0xFE);
    
    for (int y = 0; y < 8; ++y)
    {
      u8 byte1, byte2;
      
      if (flipY)
      {
        byte1 = spriteAddress[2*(7-y)];
        byte2 = spriteAddress[2*(7-y)+1];
      }
      else
      {
        byte1 = spriteAddress[2*y];
        byte2 = spriteAddress[2*y+1];
      }
      
      
      for (int x = 0; x < 8; ++x)
      {
        u8 colorIndex = ((byte2 >> x) & 0x01) << 1 | ((byte1 >> x) & 0x01);
        
        int xx = i*(SPRITE_SIZE+SPRITE_MARGIN) + (!flipX ? (8 - x - 1) : x);
        int yy = y;
        int value = yy*(SPRITE_MAX_COUNT*(SPRITE_SIZE+SPRITE_MARGIN)) + xx;
        
        dest[value] = colors[colorIndex];
      }
    }
    
    if (doubleSize)
    {
      spriteAddress = vram + TILE_BYTES_SIZE * (index | 0x01);

      for (int y = 0; y < 8; ++y)
      {
        u8 byte1, byte2;
        
        if (flipY)
        {
          byte1 = spriteAddress[2*(7-y)];
          byte2 = spriteAddress[2*(7-y)+1];
        }
        else
        {
          byte1 = spriteAddress[2*y];
          byte2 = spriteAddress[2*y+1];
        }
        
        
        for (int x = 0; x < 8; ++x)
        {
          u8 colorIndex = ((byte2 >> x) & 0x01) << 1 | ((byte1 >> x) & 0x01);
          
          int xx = i*(SPRITE_SIZE+SPRITE_MARGIN) + (!flipX ? (8 - x - 1) : x);
          int yy = y+8;
          int value = yy*(SPRITE_MAX_COUNT*(SPRITE_SIZE+SPRITE_MARGIN)) + xx;
          
          dest[value] = colors[colorIndex];
        }
      }
    }
  }
}

void Screen::renderGbPalette()
{
  pixel_type colors[4];
  
  emu->display->colorsForPalette(LAYER_BACKGROUND, 0, colors);
  memcpy(gbpal, &colors, sizeof(pixel_type)*4);
  
  emu->display->colorsForPalette(LAYER_SPRITE, 0, colors);
  memcpy(&gbpal[8*4], &colors, sizeof(pixel_type)*4);
  
  emu->display->colorsForPalette(LAYER_SPRITE, 1, colors);
  memcpy(&gbpal[9*4], &colors, sizeof(pixel_type)*4);
  
  glRasterPos2f(-0.3, 1);
	glPixelZoom(5, -5);
 	glDrawPixels(32, 2, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, gbpal);
  
}

void Screen::renderCgbPalette()
{
  /*for (int i = 0; i < 8; ++i)
  {
    u32 colors[4];
    emu->display->colorsForPalette(LAYER_SPRITE, i, colors);
    printf("%u %u %u %u\n",colors[0],colors[1],colors[2],colors[3]);
    //printf("%.2X ",emu->mem->memoryMap()->color_palette_ram[64+i]);
  }
    
  printf("\n\n\n");*/
  
  pixel_type colors[4];
  
  for (int i = 0; i < 8; ++i)
  {
    emu->display->colorsForPalette(LAYER_BACKGROUND, i, colors);
    memcpy(&gbpal[i*4], &colors, sizeof(pixel_type)*4);
  }
  
  for (int i = 0; i < 8; ++i)
  {
    emu->display->colorsForPalette(LAYER_SPRITE, i, colors);
    memcpy(&gbpal[(8+i)*4], &colors, sizeof(pixel_type)*4);
  }

  glRasterPos2f(-0.3, 1);
	glPixelZoom(6, -6);
 	glDrawPixels(32, 2, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, gbpal);
  
}

#endif
