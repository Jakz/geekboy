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


#ifdef VRAM_DEBUG

struct Surface
{
  std::unique_ptr<pixel_type[]> _data;
  const GLsizei width, height;
  
  Surface(Surface&& other) : width(other.width), height(other.height), _data(std::move(other._data)) { }
  Surface& operator=(Surface&& other)
  {
    _data = std::move(other._data);
    return *this;
  }
  
  Surface(const Surface& other) = delete;
  Surface& operator=(Surface& other) = delete;
  
  Surface(GLsizei width, GLsizei height) : _data(new pixel_type[width*height]), width(width), height(height) { }
  
  
  void set(GLsizei x, GLsizei y, pixel_type p) { _data[x+y*width] = p; }
  void fill(pixel_type p) { std::fill(_data.get(), _data.get()+width*height, p); }
  
  pixel_type* data() { return _data.get(); }
  const pixel_type* data() const { return _data.get(); }
};

constexpr size_t SPRITE_SIZE = 8;
constexpr size_t SPRITE_MARGIN = 4;
constexpr size_t TILE_SIZE = 8;

#endif

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
  struct TileInfo
  {
    u8 index;
    bool vram1 : 1;
    bool hflip : 1;
    bool vflip : 1;
    u8 palette : 3;
  };
  
  using TileMapData = std::array<std::array<TileInfo, 32>, 32>;
  std::array<s8[384], 2> guessedPalettes;
  
  std::array<TileMapData, 2> tileMaps;

  pixel_type tileData1[128*192*sizeof(pixel_type)];
  pixel_type tileData2[128*192*sizeof(pixel_type)];
  
  Surface maps[2] = { Surface(256, 256), Surface(256, 256) };
  Surface sprites = Surface((SPRITE_SIZE+SPRITE_MARGIN)*SPRITE_MAX_COUNT, SPRITE_SIZE*2);
  
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
  void draw(int x, int y, const Surface& surface, float scale);
  
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
  
  void computeTileMaps();
  
  void renderTileData(pixel_type *dest, u8 *tileData, int index);
  void renderTileMap(Surface& surface, const TileMapData& tileMap, int index);
  void renderSprites(const u8* oam, u8 *vram);
  
  void renderRect(Surface& surface, int w, int h, int x, int y, pixel_type color);
  void renderCurrentScanline();
  
  void renderSpriteInfo(int x, int y);

  void renderGbPalette();
  void renderCgbPalette();
#endif

  static Screen* i();
};

#endif