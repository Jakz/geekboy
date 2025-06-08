#pragma once

#include "cpu.h"

namespace gb
{
  class LR35902 : public Mos6502
  {
  protected:
    Emulator& emu;

  public:
    LR35902(Emulator& emu);

  public:
    void djnzn();
  };
}
