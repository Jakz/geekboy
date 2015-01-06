#include "utils.h"

#ifndef _GB_SCREEN_H_
#define _GB_SCREEN_H_

#include <chrono>
#include <OpenGL/OpenGL.h>
#include "emulator.h"

#define FPS (60)

#define VRAM_DEBUG false


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
  
    Timer timer;
  
    Emulator *emu;

    SDL_Surface *total;
    const u32 scaleFactor;
  
    u16 *screenBuffer;
  
#if VRAM_DEBUG
    u32 tileData1[128*192*sizeof(u32)];
    u32 tileData2[128*192*sizeof(u32)];
    u32 tileMap1[256*256*sizeof(u32)];
    u32 tileMap2[256*256*sizeof(u32)];
  
    u32 gbpal[16*4*sizeof(u32)];
#endif


    bool running;
    bool fpsCap;
  
    clock_t crender, cloop;

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
    void renderTileData(u32 *dest, u8 *tileData);
    void renderTileMap(u32 *dest, u16 address);
  
    void renderGbPalette();
    void renderCgbPalette();
#endif
  
    static Screen* i();
};

#endif