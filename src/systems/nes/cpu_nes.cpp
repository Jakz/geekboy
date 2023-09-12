#include "cpu_nes.h"

using namespace nes;

cycle_count_t CpuNES::cyclesForInstruction(nes_opcode_t opcode)
{
  static cycle_count_t data[256] = {

  };

  return 0;
}

u8 CpuNES::memRead(u16 address)
{
  return 0;
}

void CpuNES::memWrite(u16 address, u8 value)
{
  
}

void CpuNES::setFlag(CpuFlag flag, u8 value)
{
  if (value)
    regs.P |= decltype(regs.P)(flag);
  else
    regs.P &= ~decltype(regs.P)(flag);
}

void CpuNES::setZeroAndNegativeFlags(u8 value)
{
  setFlag(CpuFlag::Zero, value == 0);
  setFlag(CpuFlag::Negative, value & NEGATIVE_BIT);
}

inline cycle_count_t CpuNES::mov_R_R_IMM(u8& dst, u8 src, bool flags)
{
  dst = src;
  
  if (flags)
    setZeroAndNegativeFlags(src);
  return 2;
}

inline cycle_count_t CpuNES::mov_R_PTR_NN(u8& dst)
{
  u8 addr = memRead(regs.PC++);
  dst = memRead(addr);
  setZeroAndNegativeFlags(dst);
  return 3;
}

cycle_count_t CpuNES::executeInstruction(nes_opcode_t opcode)
{
  using op = nes_opcode_t;
  
  cycle_count_t cycles = 0;
  
  switch (opcode)
  {
    /* MOV R, R */
    case op::MOV_Y_A:
      cycles = mov_R_R_IMM(regs.Y, regs.A);
      break;
    case op::MOV_X_A:
      cycles = mov_R_R_IMM(regs.X, regs.A);
      break;
    case op::MOV_X_S:
      cycles = mov_R_R_IMM(regs.X, regs.S);
      break;
    case op::MOV_A_Y:
      cycles = mov_R_R_IMM(regs.A, regs.Y);
      break;
    case op::MOV_A_X:
      cycles = mov_R_R_IMM(regs.A, regs.X);
      break;
    case op::MOV_S_X:
      cycles = mov_R_R_IMM(regs.S, regs.X, false);
      break;

    /* MOV R, NN */
    case op::MOV_A_NN:
      cycles = mov_R_R_IMM(regs.A, memRead(regs.PC++));
      break;
    case op::MOV_X_NN:
      cycles = mov_R_R_IMM(regs.X, memRead(regs.PC++));
      break;
    case op::MOV_Y_NN:
      cycles = mov_R_R_IMM(regs.Y, memRead(regs.PC++));
      break;

    /* MOV R, [NN] */
    case op::MOV_A_PTR_NN:
    {
      cycles = mov_R_PTR_NN(regs.A);
      break;
    }
    case op::MOV_X_PTR_NN:
    {
      cycles = mov_R_PTR_NN(regs.X);
      break;
    }
    case op::MOV_Y_PTR_NN:
    {
      cycles = mov_R_PTR_NN(regs.Y);
      break;
    }

    /* PUSH / PULL */
    case op::PUSH_A:
    {
      memWrite(STACK_BASE + regs.S--, regs.A);
      cycles = 3;
      break;
    }
    case op::PUSH_P:
    {
      memWrite(STACK_BASE + regs.S--, regs.P);
      cycles = 3;
      break;
    } 
    case op::POP_A:
    {
      regs.A = memRead(STACK_BASE + ++regs.S);
      setZeroAndNegativeFlags(regs.A);
      cycles = 4;
      break;
    }
    case op::POP_P:
    {
      regs.P = memRead(STACK_BASE + ++regs.S);
      cycles = 4;
      break;
    }

    default:
    {
      return 0;
    }
  }
}
