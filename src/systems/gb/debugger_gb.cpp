#include "debugger_gb.h"
#include "gbspec.h"

#include "emulator.h"

#include "BearLibTerminal.h"

class Terminal
{
public:
  void drawString(coord_t x, coord_t y, const char* str)
  {
    terminal_print(x, y, str);
  }

  void clear()
  {
    terminal_clear();
  }

  void refresh()
  {
    terminal_refresh();
  }

  void drawBox(coord_t x1, coord_t y1, coord_t x2, coord_t y2)
  {
    /* corners */
    terminal_put(x1, y1, U'┌');
    terminal_put(x2, y1, U'┐');
    terminal_put(x1, y2, U'└');
    terminal_put(x2, y2, U'┘');

    /* horizontal */
    for (auto x = x1 + 1; x < x2; ++x)
    {
      terminal_put(x, y1, U'─');
      terminal_put(x, y2, U'─');
    }

    /* vertical */
    for (auto y = y1 + 1; y < y2; ++y)
    {
      terminal_put(x1, y, U'│');
      terminal_put(x2, y, U'│');
    }
  }
};

using namespace gb;

struct Port
{
  addr16_t address;
  const char* name;
};

Port ports[] = {
  { PORT_DIV, "DIV" },
  { PORT_TIMA, "TIMA" },
};

static char buffer[256];

Debugger::Debugger()
{
  _term = new Terminal();
}

debug::InstructionInfo DebuggerMachine::decode(const debug::Machine::instr_buffer_t& data)
{
  debug::InstructionInfo info;
  
  if (data[0] != gb::OPCODE_BITS)
  {
    const gb::OpcodeGB& opcode = Opcodes::opcodesSpecs[data[0]];
    info.length = opcode.length;
  
    char buffer[256];

    if (info.length == 1)
      info.mnemonic = opcode.name;
    else if (info.length == 2)
    {
      sprintf(buffer, opcode.name, opcode.paramsSign ? (s8)data[2] : data[2]);
      info.mnemonic = buffer;
    }
    else if (info.length == 3)
    {
      sprintf(buffer, opcode.name, (data[2] << 8) | data[1]);
      info.mnemonic = buffer;
    }
  }
  else
  {
    info.length = 2;
    info.mnemonic = gb::Opcodes::cbMnemonics[data[1]];
  }
  
  return info;
}

void Debugger::drawRegs(coord_t x, coord_t y)
{
  _term->drawBox(x, y, x + 53, y + 3);
  _term->drawString(x + 2, y, "[Regs]");

  x += 2; 
  ++y;
  
  auto* r = _emu->cpu.regs();

  sprintf(buffer, "AF: %.4X    DE: %.4X    PC: %.4X        Z%u N%u H%u C%u",
    r->AF,
    r->DE,
    r->PC,
    r->F & gb::FLAG_Z ? 1 : 0,
    r->F & gb::FLAG_N ? 1 : 0,
    r->F & gb::FLAG_H ? 1 : 0,
    r->F & gb::FLAG_C ? 1 : 0
  );

  _term->drawString(x, y, buffer);

  sprintf(buffer, "BC: %.4X    HL: %.4X    SP: %.4X        IME%u",
    r->BC,
    r->HL,
    r->SP,
    _emu->cpu.status()->interruptsEnabled ? 1 : 0
  );

  _term->drawString(x, y + 1, buffer);

}

void Debugger::drawRom(coord_t x, coord_t y)
{
  constexpr size_t ROWS = 20;
  
  uint16_t addr = _emu->cpu.regs()->PC;

  for (size_t i = 0; i < ROWS; ++i)
  {
    debug::Machine::instr_buffer_t instruction;
    
    for (size_t j = 0; j < instruction.size(); ++j)
      instruction[j] = _emu->mem.read(addr + j);

    auto info = _machine->decode(instruction);

    _term->drawString(x, y, info.mnemonic.c_str());

    addr += info.length;
    ++y;
  }
}

void Debugger::refresh()
{
  _term->clear();

  drawRegs(0, 0);
  drawRom(0, 0);

  _term->refresh();
}