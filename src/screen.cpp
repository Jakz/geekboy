#include "screen.h"



#include "time.h"
#include "sound.h"

#if __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>
#else
#include <GL/gl.h>
//#include <GL/glut.h>
#endif
#include <thread>
#include <string>
#include <array>

using namespace std;
using namespace std::chrono;

void Timer::setFrameRate(float rate)
{
  totalFrames = 0;
  this->rate = rate;
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

void Surface::init(SDL_Renderer* renderer)
{
  this->renderer = renderer;
  surface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
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

bool Screen::init(const EmuSpec& spec)
{
  emuSpec = spec;
  
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  /*SDL_EnableUNICODE(true);
  SDL_EnableKeyRepeat(500, 10);*/

  width = spec.displayWidth*scaleFactor;
  height = spec.displayHeight*scaleFactor;

  #if VRAM_DEBUG
    width = 1440;
    height = 800;
    Font::init();
    consoleMode = false;
  #endif

  if ((_window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0)) == nullptr)
    return false;

  if ((renderer = SDL_CreateRenderer(_window, -1, 0)) == nullptr)
    return false;

  display = SDL_CreateRGBSurface(0, spec.displayWidth, spec.displayHeight, 32, 0, 0, 0, 0);
  displayTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, display->w, display->h);

  tileDatas[0].init(renderer);
  tileDatas[1].init(renderer);

  maps[0].init(renderer);
  maps[1].init(renderer);

  sprites.init(renderer);
  palette.init(renderer);

  screenBuffer = new u16[spec.displayWidth * spec.displayHeight];
  
  return true;
}

float x(int xx) { return (xx - width/2) / (float)(width/2); }
float y(int yy) { return ((height - yy) / (float)(height/2)) - 1.0f; }

void Screen::load(const std::string& fileName)
{
  if (emu)
    delete emu;

  emu = new Emulator(emuSpec);
  emu->setupSound(48000);
  emu->display->setBuffer((uint32_t*)display->pixels);

  emu->loadCartridge(fileName);
}

int Screen::execute()
{
  timer.setFrameRate(59.73f);
  //timer.setFrameRate(10.00);

  while (running)
  {
    SDL_Event event;

    while(SDL_PollEvent(&event))
      handleEvent(&event);

    if (emu)
    {
      if (!paused)
        loop();
      render();
    }

    timer.frameRateDelay();
  }

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

  if (emu->mem.cart)
    emu->mem.cart->dumpSave();

  SDL_FreeSurface(display);
  SDL_DestroyTexture(displayTexture);

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
#if VRAM_DEBUG
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
          console += event->key.keysym.sym;
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

        case SDLK_KP_PLUS:
        case SDLK_i:
        { if (speed != speeds.begin()) --speed; break; }
        case SDLK_KP_MINUS:
        case SDLK_k:
        { if (speed != speeds.end()-1) ++speed; break; }

        case SDLK_KP_MULTIPLY:
        case SDLK_o:
        { if (timer.frameRate() < 59.73f) timer.setFrameRate(std::min(59.73f, timer.frameRate()+10.0f)); break; }
        case SDLK_KP_DIVIDE:
        case SDLK_l:
        { if (timer.frameRate() > 1.0f) timer.setFrameRate(std::max(1.0f, timer.frameRate()-10.0f)); break; }

        case SDLK_n: { if (paused) emu->step(); break; }

#if VRAM_DEBUG
        //case SDLK_WORLD_0: { consoleMode = !consoleMode; console = ">"; break; }
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

void Screen::drawString(const std::string& txt, int x, int y, float scale)
{
  int sx = x;
  static pixel_type buffer[Font::WIDTH*Font::HEIGHT];
  static const pixel_type color = gb::GpuGB<Emulator::PIXEL_TYPE>::ccc(31, 31, 31);

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

    //draw(x, y, scale, buffer, Font::WIDTH, Font::HEIGHT);

    x += (Font::WIDTH+1)*scale;
  }
}

void Screen::render()
{
  SDL_RenderClear(renderer);
#if VRAM_DEBUG
  SDL_SetRenderDrawColor(renderer, 0.3f * 255, 0.3f * 255, 0.3f * 255, 255);
  SDL_RenderFillRect(renderer, nullptr);
#endif

  SDL_UpdateTexture(displayTexture, nullptr, display->pixels, display->pitch);

  SDL_Rect dest = SDL_Rect{ 0, 0, (uint16_t)(display->w * scaleFactor), (uint16_t)(display->h * scaleFactor) };
  SDL_RenderCopy(renderer, displayTexture, nullptr, &dest);

  #if VRAM_DEBUG
  renderVRAM();
  renderRegs();
 /*

  if (consoleMode)
    drawString(console, 1100, 900, 1);
    */
  #endif
  

  SDL_RenderPresent(renderer);
}

#if VRAM_DEBUG

void Screen::computeTileMaps()
{
  u8 lcdc = emu->mem.read(PORT_LCDC);
  bool isUnsigned = Utils::bit(lcdc, 4);

  for (int i = 0; i < 2; ++i)
  {
    std::fill(guessedPalettes[i], guessedPalettes[i]+384, -1);

    constexpr ptrdiff_t BASE_FROM_VRAM = 0x1800;
    constexpr size_t TILE_MAP_SIZE_IN_BYTES = 0x400;

    u8* base = emu->mem.memoryMap()->vram + BASE_FROM_VRAM + i*TILE_MAP_SIZE_IN_BYTES;
    u8* attrs = base + KB8;

    for (int x = 0; x < TILE_MAP_WIDTH; ++x)
    {
      for (int y = 0; y < TILE_MAP_HEIGHT; ++y)
      {
        u8 index = base[x + y*TILE_MAP_WIDTH];

        tileMaps[i][y][x].index = index;
        u8 attribs = attrs[x+y*TILE_MAP_WIDTH];

        tileMaps[i][y][x].vram1 = Utils::bit(attribs, 3);
        tileMaps[i][y][x].hflip = Utils::bit(attribs, 5);
        tileMaps[i][y][x].vflip = Utils::bit(attribs, 6);
        tileMaps[i][y][x].palette = attribs & 0x07;

        guessedPalettes[i][isUnsigned ? index : (256 + (s8)index)] = tileMaps[i][y][x].palette;
      }
    }
  }
}

void Screen::renderVRAM()
{
  computeTileMaps();

  constexpr float TILE_DATA_SCALE = 2.0f;
  constexpr float TILE_MAP_SCALE = 1.0f;

  auto width = emuSpec.displayWidth;
  auto height = emuSpec.displayHeight;

  renderTileData(tileDatas[0], emu->mem.memoryMap()->vram, 0);
  tileDatas[0].render(width * scaleFactor + 20, 20, TILE_DATA_SCALE);

  renderTileData(tileDatas[1], &emu->mem.memoryMap()->vram[KB8], 1);
  tileDatas[1].render(width * scaleFactor + 20 + 10 + tileDatas[0].width * TILE_DATA_SCALE, 20, TILE_DATA_SCALE);

  
  renderTileMap(maps[0], tileMaps[0], 0);
  maps[0].render(20, height * scaleFactor + 10, TILE_MAP_SCALE);

  renderTileMap(maps[1], tileMaps[0], 0);
  maps[1].render(20 + maps[0].width * TILE_MAP_SCALE + 10, height * scaleFactor + 10, TILE_MAP_SCALE);

  renderSpriteInfo(20, height * scaleFactor + maps[0].height * TILE_MAP_SCALE + 40);

  
  if (emu->mode == MODE_GB)
    renderGbPalette();
  else
    renderCgbPalette();

  //renderCurrentScanline();
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

  constexpr int BASE_Y = 50;

  Opcodes::visualOpcode(buffer, mem.read(regs.PC), mem.read(regs.PC+1), mem.read(regs.PC+2));
  drawString(buffer, 1100, BASE_Y, 1);

  sprintf(buffer, "SPEED %u (%2.2f)", *speed, timer.frameRate());
  drawString(buffer, 1100, BASE_Y+10, 1);

  sprintf(buffer, "SCANLINE %d (%d)\n", emu->display->getScanlineCounter(), emu->mem.rawPortRead(PORT_STAT) & 0x03);
  drawString(buffer, 1100, BASE_Y+20, 1);

  sprintf(buffer, "PC %04xh Z%d N%d H%d C%d", regs.PC, (regs.AF.F & FLAG_Z) != 0, (regs.AF.F & FLAG_N) != 0, (regs.AF.F & FLAG_H) != 0, (regs.AF.F & FLAG_C) != 0);
  drawString(buffer, 1100, BASE_Y+50, 1);

  sprintf(buffer, "AF %02xh BC %04xh", regs.AF.A, regs.BC.BC);
  drawString(buffer, 1100, BASE_Y+60, 1);

  sprintf(buffer, "DE %04xh HL %04xh", regs.DE.DE, regs.HL.HL);
  drawString(buffer, 1100, BASE_Y+70, 1);

  sprintf(buffer, "SP %04xh IF %02xh IE %02xh", regs.SP, mem.read(PORT_IF), mem.read(PORT_EF));
  drawString(buffer, 1100, BASE_Y+80, 1);

  std::array<PortSpec, 5> specst = { { {PORT_DIV, "DIV"}, {PORT_TIMA, "TIMA"}, {PORT_TMA, "TMA"}, {PORT_TAC, "TAC"}, {PORT_JOYP, "JOYP"} } };
  renderPorts(specst, 1100, BASE_Y+100);

  std::array<PortSpec, 8> specsd = { { {PORT_LCDC, "LCDC"}, {PORT_STAT, "STAT"}, {PORT_SCY, "SCY"}, {PORT_SCX, "SCX"}, {PORT_LY, "LY"}, {PORT_LYC, "LYC"}, {PORT_WY, "WY"}, {PORT_WX, "WX"} } };
  renderPorts(specsd, 1100, BASE_Y+160);

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
  drawString(buffer, 1200, BASE_Y+160, 1);

}

void Screen::renderCurrentScanline()
{
  //if (speed > speeds.begin())
  {
    static const pixel_type color = gb::GpuGB<Emulator::PIXEL_TYPE>::ccc(31, 0, 0);

    u8 scanline = emu->mem.rawPortRead(PORT_LY);

    //draw(emu->spec.displayWidth*scaleFactor, scanline*scaleFactor, scaleFactor, &color, 1, 1);
  }
}

void Screen::renderRect(Surface &surface, int w, int h, int x, int y, pixel_type color)
{
  for (int i = 0; i < w; ++i)
  {
    surface.set((x+i) % surface.width, y, color);
    surface.set((x+i) % surface.width, (y + h) % surface.height, color);
  }

  for (int i = 0; i < h; ++i)
  {
    surface.set(x, (y+i) % surface.height, color);
    surface.set((x + w) % surface.width , (y+i) % surface.height, color);
  }
}


void Screen::renderTileData(Surface& dest, u8 *data, int index)
{
  GpuGB<Emulator::PIXEL_TYPE>::Pixel::type colors[4];
  u16 address;

  for (int i = 0; i < (0x9800 - 0x8000) / 16; ++i)
  {
    s8 palette = guessedPalettes[index][i];

    if (palette == -1)
      emu->display->colorsForPalette(LAYER_BACKGROUND, 0, colors);
    else
      emu->display->colorsForPalette(LAYER_BACKGROUND, palette, colors);

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

        dest.set(fx, fy, color);
      }
    }
  }

  dest.update();
}


void Screen::renderTileMap(Surface& surface, const TileMapData& tileMap, int index)
{
  u8 lcdc = emu->mem.read(PORT_LCDC);
  bool isUnsigned = Utils::bit(lcdc, 4);
  bool isCGB = emu->mode == MODE_CGB;

  GpuGB<Emulator::PIXEL_TYPE>::Pixel::type colors[4];

  for (int i = 0; i < TILE_MAP_HEIGHT; ++i)
    for (int j = 0; j < TILE_MAP_WIDTH; ++j)
    {
      const TileInfo& ti = tileMap[i][j];

      s16 index = isUnsigned ? ti.index : ((s8)ti.index + 256);
      emu->display->colorsForPalette(LAYER_BACKGROUND, isCGB ? ti.palette : 0, colors);

      u8* address = emu->mem.memoryMap()->vram + (ti.vram1 && isCGB ? KB8 : 0) + TILE_BYTES_SIZE*index;

      bool flipX = isCGB && ti.hflip;
      bool flipY = isCGB && ti.vflip;

      for (int y = 0; y < 8; ++y)
      {
        int ry = flipY ? (8 - 1 - y) : y;

        u8 byte1 = address[ry*2];
        u8 byte2 = address[ry*2 + 1];

        for (int x = 0; x < 8; ++x)
        {
          int rx = flipX ? (8 - 1 - x) : x;

          u8 index = ((byte2 >> (7 - rx)) & 0x01) << 1 | ((byte1 >> (7 - rx)) & 0x01);
          const pixel_type& color = colors[index];
          surface.set(j*TILE_SIZE + x, i*TILE_SIZE + y, color);
        }
      }
      //SDL_BlitSurface(tileData,&src,total,&dest);
    }

  if (!(Utils::bit(lcdc, 3) ^ (index == 1)))
  {
    pixel_type edge = gb::GpuGB<Emulator::PIXEL_TYPE>::ccc(31, 0, 0);

    u8 scx = emu->mem.read(PORT_SCX);
    u8 scy = emu->mem.read(PORT_SCY);

    renderRect(surface, 160, 144, scx, scy, edge);
  }

  if (!(Utils::bit(lcdc, 6) ^ (index == 1)) && Utils::bit(lcdc, 5))
  {
    pixel_type edge = gb::GpuGB<Emulator::PIXEL_TYPE>::ccc(0, 31, 0);

    int wx = emu->mem.read(PORT_WX) - 7;
    int wy = emu->mem.read(PORT_WY);

    renderRect(surface, 160, 144, wx, wy, edge);
  }

  surface.update();
}

void Screen::renderSpriteInfo(int x, int y)
{
  const u8* oam = emu->mem.oam();
  constexpr float SCALE = 2;

  renderSprites(oam, emu->mem.memoryMap()->vram);
  sprites.update();
  sprites.render(x, y, SCALE);
  
  for (int i = 0; i < SPRITE_MAX_COUNT; ++i)
  {
    const u8* soam = &oam[i*4];

    u8 yy = soam[0];
    u8 xx = soam[1];

    sprintf(buffer, "%u\n%u", xx, yy);

    drawString(buffer, x + i*(SPRITE_SIZE+SPRITE_MARGIN)*SCALE, y-25, 1);
  }
}

void Screen::renderSprites(const u8* oams, u8* vram_total)
{
  static const pixel_type black = gb::GpuGB<Emulator::PIXEL_TYPE>::ccc(0, 0, 0);

  sprites.fill(black);

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

        sprites.set(xx, yy, colors[colorIndex]);
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

          sprites.set(xx, yy, colors[colorIndex]);
        }
      }
    }
  }
}

void Screen::renderGbPalette()
{
  pixel_type colors[4];

  /*emu->display->colorsForPalette(LAYER_BACKGROUND, 0, colors);
  memcpy(gbpal, &colors, sizeof(pixel_type)*4);

  emu->display->colorsForPalette(LAYER_SPRITE, 0, colors);
  memcpy(&gbpal[8*4], &colors, sizeof(pixel_type)*4);

  emu->display->colorsForPalette(LAYER_SPRITE, 1, colors);
  memcpy(&gbpal[9*4], &colors, sizeof(pixel_type)*4);*/

  /*glRasterPos2f(-0.3, 1);
	glPixelZoom(5, -5);
 	glDrawPixels(32, 2, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, gbpal);*/
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

  /*pixel_type colors[4];

  for (int i = 0; i < 8; ++i)
  {
    emu->display->colorsForPalette(LAYER_BACKGROUND, i, colors);
    memcpy(&gbpal[i*4], &colors, sizeof(pixel_type)*4);
  }

  for (int i = 0; i < 8; ++i)
  {
    emu->display->colorsForPalette(LAYER_SPRITE, i, colors);
    memcpy(&gbpal[(8+i)*4], &colors, sizeof(pixel_type)*4);
  }*/

  /*glRasterPos2f(-0.3, 1);
	glPixelZoom(6, -6);
 	glDrawPixels(32, 2, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, gbpal);*/

}

#endif
