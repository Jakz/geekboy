#include "utils.h"

#ifndef _GB_SCREEN_H_
#define _GB_SCREEN_H_

#include <array>
#include <string>
#include <chrono>
#include <OpenGL/OpenGL.h>
#include "emulator.h"
#include "font.h"

using pixel_type = gb::Display<gb::PixelFormat::ARGB51>::Pixel::type;

#define FPS (60)

#define VRAM_DEBUG true

constexpr size_t SPRITE_SIZE = 8;
constexpr size_t SPRITE_MARGIN = 4;


using namespace gb;

class Timer
{
  const float DEFAULT_FPS = 60.0f;
  
  std::chrono::steady_clock clock;
  std::chrono::microseconds ticksForFrame;
  
  u32 totalFrames;
  std::chrono::time_point<std::chrono::steady_clock> base;
  
public:
  Timer() : ticksForFrame(static_cast<u32>(1000000 / DEFAULT_FPS)), totalFrames(0) { }
  
  void setFrameRate(float rate);
  void frameRateDelay();
};

class Screen
{
  static Screen instance;
  std::array<u32, 7> speeds;
  std::array<u32, 7>::iterator speed;

  Timer timer;

  Emulator *emu;

  SDL_Surface *total;
  const u32 scaleFactor;

  u16 *screenBuffer;

#if VRAM_DEBUG
  pixel_type tileData1[128*192*sizeof(pixel_type)];
  pixel_type tileData2[128*192*sizeof(pixel_type)];
  pixel_type tileMap1[256*256*sizeof(pixel_type)];
  pixel_type tileMap2[256*256*sizeof(pixel_type)];
  pixel_type sprites[(SPRITE_SIZE+SPRITE_MARGIN)*SPRITE_SIZE*SPRITE_MAX_COUNT*2*sizeof(pixel_type)];

  pixel_type gbpal[32*2*sizeof(pixel_type)];
  
  bool consoleMode;
  std::string console;
  
  struct PortSpec
  {
    u16 address;
    const char* name;
  };
#endif


  bool running;
  bool fpsCap;
  bool paused;

  clock_t crender, cloop;

  void draw(int x, int y, float scale, const void* data, int width, int height);
  void drawString(const std::string& txt, int x, int y, float scale);

public:
  Screen();

  bool init();

  int execute(const std::string& fileName);

  void loop();
  void render();
  void capFPS(u32 start);

  void handleEvent(SDL_Event *event);

  void cleanup();

#if VRAM_DEBUG
  void renderVRAM();
  void renderRegs();
  template<size_t SIZE> void renderPorts(const std::array<PortSpec, SIZE>& ports, int x, int y);
  
  void renderTileData(pixel_type *dest, u8 *tileData);
  void renderTileMap(pixel_type *dest, u16 address);
  void renderSprites(pixel_type* dest, const u8* oam, u8 *vram);
  
  void renderCurrentScanline();
  
  void renderSpriteInfo(int x, int y);

  void renderGbPalette();
  void renderCgbPalette();
#endif

  static Screen* i();
};

#endif