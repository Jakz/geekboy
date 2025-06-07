#include "lr35902.h"

#include "emulator.h"


using namespace gb;

LR35902::LR35902(Emulator& emu) : CpuGB(emu.mem), emu(emu)
{
  opcodes[OPCODE_DJNZ_N] = static_cast<void (CpuGB::*)()>(&LR35902::djnzn);
}

void LR35902::djnzn()
{
  // if a speed switch was requested
  u8 speed = mem.rawPortRead(PORT_KEY1);

  if (Utils::bit(speed, 0))
  {
    // if CPU was in double mode
    if (Utils::bit(speed, 7))
    {
      emu.toggleDoubleSpeed(false);
      mem.rawPortWrite(PORT_KEY1, speed & 0x7E);
    }
    else
    {
      emu.toggleDoubleSpeed(true);
      mem.rawPortWrite(PORT_KEY1, (speed | 0x80) & 0xFE);
    }

    //s.interruptsEnabled = true;
    //mem->write(PORT_IF, 0x1F);
  }
  else
    CpuGB::djnzn();
}