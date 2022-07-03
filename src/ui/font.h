#ifndef _FONT_H_
#define _FONT_H_

#include <cstdlib>

class Font
{
public:
  constexpr static size_t GLYPH_COUNT = 128;
  constexpr static size_t WIDTH = 5;
  constexpr static size_t HEIGHT = 8;
  
private:
  static bool* glyphData[GLYPH_COUNT];
  
public:
  static bool* glyph(char c) { return glyphData[c]; }
  static void init();
};



#endif