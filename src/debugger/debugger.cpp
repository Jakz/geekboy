#include "debugger.h"

#include "opcodes.h"
#include "cpu.h"
#include "memory.h"
#include "emulator.h"

using namespace std;
using namespace gb;

void Debugger::toggleBreakPoint(u16 address)
{
  set<u16>::iterator it = breakPoints.find(address);
  
  if (it != breakPoints.end())
    breakPoints.erase(it);
  else
    breakPoints.insert(address);
}

bool Debugger::hasBreakPoint(u16 address)
{
  return breakPoints.find(address) != breakPoints.end();
}

#pragma mark GAME BOY

DebuggerGB::DebuggerGB(gb::Emulator *emu) : emu(emu), Debugger{
  "Z80GB",
  WIDTH_U16,
  WIDTH_U8,
  WIDTH_U24,
  {
    {PORT_DIV, "DIV"},
    {PORT_TIMA, "TIMA"},
    {PORT_TMA, "TMA"},
    {PORT_TAC, "TAC"},
    {0xFF0F, "IF"},
    {0xFFFF, "IE"},
    {PORT_LCDC, "LCDC"},
    {PORT_STAT, "STAT"},
    {PORT_SCY, "SCY"},
    {PORT_SCX, "SCX"},
    {PORT_LY, "LY"},
    {0xFF45, "LCY"},
    {PORT_WY, "WY"},
    {PORT_WX, "WX"},
    {PORT_BGP, "BGP"},
    {PORT_OBP0, "OBP0"},
    {PORT_OBP1, "OBP1"}
  }
}
{}

u16 DebuggerGB::instructionLength(u8 opcode)
{
  if (opcode != gb::OPCODE_BITS)
    return gb::Opcodes::opcodesSpecs[opcode].length;
  else
    return 2;
}

void DebuggerGB::instructionVisual(char *buffer, u8 d1, u8 d2, u8 d3, u8 d4)
{
  if (d1 != gb::OPCODE_BITS)
  {
    gb::OpcodeGB params = gb::Opcodes::opcodesSpecs[d1];
    int length = params.length;
    
    if (length == 1)
      sprintf(buffer, "%s", params.name);
    else if (length == 2)
      sprintf(buffer, params.name, params.paramsSign ? (s8)d2 : d2);
    else if (length == 3)
      sprintf(buffer, params.name, (d3 << 8) | d2);
  }
  else
  {
    sprintf(buffer, "%s", gb::Opcodes::cbMnemonics[d2]);
  }
}

void DebuggerGB::registerVisual(char *buffer, u8 line)
{
  gb::Registers *r = emu->cpu.regs();
  
  if (line == 0)
  {
    sprintf(buffer, "AF: %.4X    DE: %.4X    PC: %.4X        Z%u N%u H%u C%u",
            r->AF.AF,
            r->DE.DE,
            r->PC,
            r->AF.F & gb::FLAG_Z ? 1 : 0,
            r->AF.F & gb::FLAG_N ? 1 : 0,
            r->AF.F & gb::FLAG_H ? 1 : 0,
            r->AF.F & gb::FLAG_C ? 1 : 0
    );
  }
  else if (line == 1)
  {
    sprintf(buffer, "BC: %.4X    HL: %.4X    SP: %.4X        IME%u",
            r->BC.BC,
            r->HL.HL,
            r->SP,
            emu->cpu.status()->interruptsEnabled ? 1 : 0
            );
  }
}
