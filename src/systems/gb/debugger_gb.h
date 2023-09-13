#pragma once

#include "utils.h"

class Terminal;

namespace gb
{
  class Emulator;
  
  class Debugger
  {
  protected:
    Emulator* _emu;
    Terminal* _term;

    void drawRegs(coord_t x, coord_t y);

  public:
    Debugger();

    void setEmulator(Emulator* emu) { this->_emu = emu; }
    void refresh();
  };
}