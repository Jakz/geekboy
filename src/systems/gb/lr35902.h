#pragma once

#include "cpu.h"

namespace gb
{
  class LR35902 : public CpuGB
  {
  protected:
    Emulator& emu;

  public:
    LR35902(Emulator& emu);

  public:
    void djnzn();
  };
}
