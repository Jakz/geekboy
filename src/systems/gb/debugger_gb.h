#pragma once

#include "utils.h"

class Terminal;

namespace debug
{
  struct InstructionInfo
  {
    size_t length;
    std::string mnemonic;
  };

  class Machine
  {
  public:
    static constexpr size_t MAX_INSTRUCTION_LENGTH = 4;

    using instr_buffer_t = std::array<u8, MAX_INSTRUCTION_LENGTH>;

  public:
    virtual InstructionInfo decode(const instr_buffer_t& data) = 0;
  };

}


namespace gb
{
  class Emulator;
  
  class DebuggerMachine : public debug::Machine
  {
  public:
    debug::InstructionInfo decode(const instr_buffer_t& data) override;
  };

  class Debugger
  {
  protected:
    debug::Machine* _machine = new gb::DebuggerMachine();
    Emulator* _emu;
    Terminal* _term;

    void drawRegs(coord_t x, coord_t y);
    void drawRom(coord_t x, coord_t y);

  public:
    Debugger();

    void setEmulator(Emulator* emu) { this->_emu = emu; }
    void refresh();
  };
}