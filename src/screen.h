#include "utils.h"

#ifndef _GB_SCREEN_H_
#define _GB_SCREEN_H_

#include <array>
#include <string>
#include <chrono>
#if __APPLE__
#include <OpenGL/OpenGL.h>
#elif _WIN32
//#include <gl/glut.h>
#include <gl/GL.h>
#else
#include <GL/gl.h>
#endif
#include "emulator.h"
#include "ui/font.h"

using pixel_type = gb::GpuGB<gb::Emulator::PIXEL_TYPE>::Pixel::type;

#define FPS (60)

#define VRAM_DEBUG true


#ifdef VRAM_DEBUG

struct Surface
{
  size_t width, height;
  
  SDL_Renderer* renderer;
  SDL_Surface* surface;
  SDL_Texture* texture;

  Surface(size_t width, size_t height) : width(width), height(height)
  {

  }

  void init(SDL_Renderer* renderer);

  void render(s32 x, s32 y, float scale)
  {
    SDL_Rect dest = SDL_Rect{ (short)x, (short)y , (short)(width * scale), (short)(height * scale) };
    SDL_RenderCopy(renderer, texture, nullptr, &dest);
  }

  void update() { SDL_UpdateTexture(texture, nullptr, surface->pixels, surface->pitch); }

  void set(GLsizei x, GLsizei y, pixel_type p) { ((pixel_type*)surface->pixels)[x+y*width] = p; }
  void fill(pixel_type p) { std::fill((pixel_type*)surface->pixels, (pixel_type*)surface->pixels + width * height, p); }
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

  float rate;
  u32 totalFrames;
  std::chrono::time_point<std::chrono::steady_clock> base;

public:
  Timer() : rate(DEFAULT_FPS), ticksForFrame(static_cast<u32>(1000000 / DEFAULT_FPS)), totalFrames(0) { }

  float frameRate() const { return rate; }
  void setFrameRate(float rate);
  void frameRateDelay();
};

class Screen
{
  static Screen instance;
  std::array<u32, 7> speeds;
  std::array<u32, 7>::iterator speed;

  Timer timer;

  EmuSpec emuSpec;
  Emulator *emu;

  SDL_Window* _window;
  SDL_Renderer* renderer;

  SDL_Surface* display;
  SDL_Texture* displayTexture;

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

  Surface tileDatas[2] = { Surface(128,192), Surface(128, 192) };
  Surface maps[2] = { Surface(256, 256), Surface(256, 256) };
  Surface sprites = Surface((SPRITE_SIZE+SPRITE_MARGIN)*SPRITE_MAX_COUNT, SPRITE_SIZE*2);
  Surface console = Surface(Font::WIDTH * 50, Font::HEIGHT * 40);

  Surface palette = Surface(32, 2);

  std::string consoleBuffer;
  bool consoleMode;

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

  void drawString(const std::string& txt, int x, int y, float scale);

public:
  Screen();

  bool init(const EmuSpec& spec);

  int execute();

  void loop();
  void render();
  void capFPS(u32 start);

  void load(const std::string& fileName);

  void handleEvent(SDL_Event *event);

  void cleanup();

#if VRAM_DEBUG
  void renderVRAM();
  void renderRegs();
  template<size_t SIZE> void renderPorts(const std::array<PortSpec, SIZE>& ports, int x, int y);

  void computeTileMaps();

  void renderTileData(Surface& dest, u8 *tileData, int index);
  void renderTileMap(Surface& surface, const TileMapData& tileMap, int index);
  void renderSprites(const u8* oam, u8 *vram);

  void renderRect(Surface& surface, int w, int h, int x, int y, pixel_type color);
  void renderCurrentScanline();

  void renderSpriteInfo(int x, int y);

  void renderGbPalette();
  void renderCgbPalette();
#endif

  SDL_Window* window() { return _window; }
  Emulator* emulator() { return emu; }

  static Screen* i();
};

#endif
