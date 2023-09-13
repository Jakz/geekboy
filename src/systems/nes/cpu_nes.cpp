#include "cpu_nes.h"

#include "opcodes_nes.h"

using namespace nes;

cycle_count_t CpuNES::cyclesForInstruction(nes_opcode_t opcode)
{
  static cycle_count_t data[256] = {

  };

  return 0;
}

u8 CpuNES::memRead8(u16 address)
{
  return 0;
}

u16 CpuNES::memRead16(addr16_t address)
{
  return 0;
}

void CpuNES::memWrite(u16 address, u8 value)
{
  
}

void CpuNES::setFlag(CpuFlag flag, u8 value)
{
  if (value)
    _regs.P |= decltype(_regs.P)(flag);
  else
    _regs.P &= ~decltype(_regs.P)(flag);
}

void CpuNES::setZeroAndNegativeFlags(u8 value)
{
  setFlag(CpuFlag::Zero, value == 0);
  setFlag(CpuFlag::Negative, value & NEGATIVE_BIT);
}

void CpuNES::reset()
{
  _regs.P = 0x34;
  _regs.A = 0x00;
  _regs.X = 0x00;
  _regs.Y = 0x00;
  _regs.S = 0xFD;
  _regs.PC = 0x00;
}

inline cycle_count_t CpuNES::mov_R_R_IMM(u8& dst, u8 src, bool flags)
{
  dst = src;
  
  if (flags)
    setZeroAndNegativeFlags(src);
  return 2;
}

inline cycle_count_t CpuNES::mov_R_PTR(u8& dst, addr16_t addr)
{
  dst = memRead8(addr);
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
      cycles = mov_R_R_IMM(_regs.Y, _regs.A);
      break;
    case op::MOV_X_A:
      cycles = mov_R_R_IMM(_regs.X, _regs.A);
      break;
    case op::MOV_X_S:
      cycles = mov_R_R_IMM(_regs.X, _regs.S);
      break;
    case op::MOV_A_Y:
      cycles = mov_R_R_IMM(_regs.A, _regs.Y);
      break;
    case op::MOV_A_X:
      cycles = mov_R_R_IMM(_regs.A, _regs.X);
      break;
    case op::MOV_S_X:
      cycles = mov_R_R_IMM(_regs.S, _regs.X, false);
      break;

    /* MOV R, NN */
    case op::MOV_A_NN:
      cycles = mov_R_R_IMM(_regs.A, memRead8(_regs.PC++));
      break;
    case op::MOV_X_NN:
      cycles = mov_R_R_IMM(_regs.X, memRead8(_regs.PC++));
      break;
    case op::MOV_Y_NN:
      cycles = mov_R_R_IMM(_regs.Y, memRead8(_regs.PC++));
      break;

    /* MOV R, [NN] */
    case op::MOV_A_PTR_NN:
    {
      cycles = mov_R_PTR(_regs.A, memRead8(_regs.PC++));
      break;
    }
    case op::MOV_X_PTR_NN:
    {
      cycles = mov_R_PTR(_regs.X, memRead8(_regs.PC++));
      break;
    }
    case op::MOV_Y_PTR_NN:
    {
      cycles = mov_R_PTR(_regs.Y, memRead8(_regs.PC++));
      break;
    }

    /* MOV R, [NNNN] */
    case op::MOV_A_PTR_NNNN:
    {
      cycles = mov_R_PTR(_regs.A, memRead16(_regs.PC));
      _regs.PC += 2;
      break;
    }
    case op::MOV_X_PTR_NNNN:
    {
      cycles = mov_R_PTR(_regs.X, memRead16(_regs.PC));
      _regs.PC += 2;
      break;
    }
    case op::MOV_Y_PTR_NNNN:
    {
      cycles = mov_R_PTR(_regs.Y, memRead16(_regs.PC));
      _regs.PC += 2;
      break;
    }
    
    /* MOV R, [NN+R] */
    case op::MOV_A_PTR_NN_X:
    {
      mov_R_PTR(_regs.A, (memRead8(_regs.PC++) + _regs.X) & 0xff);
      cycles = Opcodes::cyclesFor(opcode);
      break;
    }
    case op::MOV_X_PTR_NN_Y:
    {
      mov_R_PTR(_regs.X, (memRead8(_regs.PC++) + _regs.Y) & 0xff);
      cycles = Opcodes::cyclesFor(opcode);
      break;
    }
    case op::MOV_Y_PTR_NN_X:
    {
      mov_R_PTR(_regs.Y, (memRead8(_regs.PC++) + _regs.X) & 0xff);
      cycles = Opcodes::cyclesFor(opcode);
      break;
    }

    /* PUSH / PULL */
    case op::PUSH_A:
    {
      memWrite(STACK_BASE + _regs.S--, _regs.A);
      cycles = 3;
      break;
    }
    case op::PUSH_P:
    {
      memWrite(STACK_BASE + _regs.S--, _regs.P);
      cycles = 3;
      break;
    } 
    case op::POP_A:
    {
      _regs.A = memRead8(STACK_BASE + ++_regs.S);
      setZeroAndNegativeFlags(_regs.A);
      cycles = 4;
      break;
    }
    case op::POP_P:
    {
      _regs.P = memRead8(STACK_BASE + ++_regs.S);
      cycles = 4;
      break;
    }

    default:
    {
      return 0;
    }
  }

  return cycles;
}
