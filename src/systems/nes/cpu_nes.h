#pragma once

#include "utils.h"

#include "opcodes_nes.h"

namespace nes
{  
  struct Registers
  {
    u8 A;
    u8 X;
    u8 Y;
    u8 S;
    u8 P;
    u16 PC;

  };

  static constexpr u8 NEGATIVE_BIT = 0x80;
  static constexpr u16 STACK_BASE = 0x100;

  enum class CpuFlag
  {
    Carry      = 0b00000001,
    Zero       = 0b00000010,
    IrqDisable = 0b00000100,
    Decimal    = 0b00001000,
    Break      = 0b00010000,
    Unused     = 0b00100000,
    Overflow   = 0b01000000,
    Negative   = 0b10000000,
  };

  enum class nes_opcode_t : u8;
  
  class CpuNES
  {
  protected:
    Registers _regs;

    static cycle_count_t cyclesForInstruction(nes_opcode_t opcode);

    inline void setZeroAndNegativeFlags(u8 value);
    inline void setFlag(CpuFlag flag, u8 value);
  
    inline cycle_count_t mov_R_R_IMM(u8& dst, u8 src, bool flags = true);
    inline cycle_count_t mov_R_PTR(u8& dst, addr16_t src);

    u8 memRead8(addr16_t address);
    u16 memRead16(addr16_t address);
    void memWrite(addr16_t address, u8 value);


  public:
    cycle_count_t executeInstruction(nes_opcode_t opcode);

    void reset();

    Registers& regs() { return _regs; }
  };



}