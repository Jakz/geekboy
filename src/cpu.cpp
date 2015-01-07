#include "cpu.h"

#include "emulator.h"

//#define GB_Z80

using namespace gb;

CpuGB::CpuGB(Emulator* emu) : emu(emu)
{

}

void CpuGB::reset()
{
  r.rr = (u8**)calloc(8,sizeof(u8**));
	r.rrrsp = (u16**)calloc(4,sizeof(u16**));
  r.rrraf = (u16**)calloc(4,sizeof(u16**));
	
	r.BC.B = 0;
	r.BC.C = 0;
	r.DE.D = 0;
	r.DE.E = 0;
	r.HL.H = 0;
	r.HL.L = 0;
	r.AF.A = 0;
	
	r.PC = 0;
  r.SP = 0x0;
	
	r.rr[0] = &r.BC.B;
	r.rr[1] = &r.BC.C;
	r.rr[2] = &r.DE.D;
	r.rr[3] = &r.DE.E;
	r.rr[4] = &r.HL.H;
	r.rr[5] = &r.HL.L;
	
	r.rr[7] = &r.AF.A;
	
	r.rrrsp[0] = &r.BC.BC;
	r.rrrsp[1] = &r.DE.DE;
	r.rrrsp[2] = &r.HL.HL;
	r.rrrsp[3] = &r.SP;
  
  r.rrraf[0] = &r.BC.BC;
	r.rrraf[1] = &r.DE.DE;
	r.rrraf[2] = &r.HL.HL;
	r.rrraf[3] = &r.AF.AF;
  
  s.running = true;
  
  halted = false;

	//print_regs();
}

Registers *CpuGB::regs()
{
  return &r;
}

Status *CpuGB::status()
{
  return &s;
}

void CpuGB::halt()
{
  s.running = false;
}

void CpuGB::adc(u8 b)
{
  u8 carry = isFlagSet(FLAG_C);
  u8 a = r.AF.A;
  u8 carryOut, res, halfCarry;

  if (carry)
  {
    carryOut = (a >= 0xFF - b);
    res = a + b + 1;
    halfCarry = (a & 0x0F) + (b & 0x0F) + 1 > 0x0F;
  }
  else
  {
    carryOut = (a > 0xFF - b);
    res = a + b;
    halfCarry = (a & 0x0F) + (b & 0x0F) > 0x0F;
  }

  r.AF.A = res;
  
  setFlag(FLAG_S, res & 0x80);
  setFlag(FLAG_Z, res == 0x00);
  setFlag(FLAG_H, halfCarry);
  setFlag(FLAG_C, carryOut);
}


void CpuGB::sbc(u8 b)
{
  u8 carry = isFlagSet(FLAG_C);
  u8 a = r.AF.A;
  u8 carryOut, res, halfCarry;
  
  if (carry)
  {
    carryOut = a <= b;
    halfCarry = ((a & 0x0F) <= (b & 0x0F));
    res = a - b - 1;
  }
  else
  {
    carryOut = a < b;
    halfCarry = ((a & 0x0F) < (b & 0x0F));
    res = a - b;
  }
  
  r.AF.A = res;
  
  setFlag(FLAG_S, res & 0x80);
  setFlag(FLAG_Z, res == 0x00);
  setFlag(FLAG_H, halfCarry);
  setFlag(FLAG_C, carryOut);
}

void CpuGB::add(u8 value)
{
  setFlag(FLAG_C, 0);
  adc(value);
}

void CpuGB::sub(u8 value)
{
  setFlag(FLAG_C, 0);
  sbc(value);
}

void CpuGB::daa()
{
  //r.AF.AF = Opcodes::daaTable[r.AF.AF>>4];
  
  u8 c = isFlagSet(FLAG_C) ? 0x60 : 0x00;
  bool cy = false;
  
  if (isFlagSet(FLAG_H))
    c |= 0x06;
  
  if (!isFlagSet(FLAG_N))
  {
    if ((r.AF.A & 0x0F) > 0x09)
      c |= 0x06;
    
    if (r.AF.A > 0x99)
      c |= 0x60;

    r.AF.A += c;
  }
  else
  {    
    r.AF.A -= c;
  }
  
  if (isFlagSet(FLAG_C) || c >= 0x60)
    cy = true;
  
  setFlag(FLAG_C, cy);
  setFlag(FLAG_Z, r.AF.A == 0);
  setFlag(FLAG_H, 0);
}

inline bool CpuGB::parity(u8 x)
{
  u8 y = x ^ (x >> 1);
  y = y ^ (y >> 2);
  y = y ^ (y >> 4);
  return (y & 1) == 0;
}


void CpuGB::enableInterrupt(u8 interrupt)
{
  // set the corresponding bit in the interrupt request register to 1
  mem->memoryMap()->ports_table[PORT_IF - 0xFF00] |= (1 << interrupt);
  halted = false;
}

void CpuGB::manageInterrupts()
{
  if (s.interruptsEnabled)
  {
    u8 ifreg = mem->memoryMap()->ports_table[PORT_IF - 0xFF00];
    
    // if there is at least one interrupt to handle
    if (ifreg)
    {
      u8 efreg = mem->memoryMap()->ports_table[PORT_EF - 0xFF00];

      for (int i = 0; i < 5; ++i)
      {
        // if the ith interrupt is both set and enabled
        if (Utils::bit(ifreg, i) && Utils::bit(efreg, i))
        {
          // disable interrupts
          s.interruptsEnabled = false;

          // reset the managed interrupt bit
          ifreg = Utils::res(ifreg, i);
          
          // push current program counter on stack
          pushDoubleSP(r.PC);
          
          r.PC = 0x40 + 0x08*i;
          
          mem->write(PORT_IF, ifreg);
          
          break;
        }
      }
    }
  }
}

inline bool CpuGB::isFlagSet(u8 flag)
{
  return r.AF.F & flag;
}
      
inline void CpuGB::setFlag(u8 flag, u8 value)
{
  if (flag == FLAG_PV || flag == FLAG_S)
    return;
  
  if (value)
    r.AF.F |= flag;
  else
    r.AF.F &= ~flag;
}

inline bool CpuGB::isConditionTrue(u8 cond)
{
  switch (cond)
  {
    case COND_NZ: return !isFlagSet(FLAG_Z);
    case COND_Z: return isFlagSet(FLAG_Z);
    case COND_NC: return !isFlagSet(FLAG_C);
    case COND_C: return isFlagSet(FLAG_C);
    case COND_PO: return !isFlagSet(FLAG_PV);
    case COND_PE: return isFlagSet(FLAG_PV);
    case COND_SP: return !isFlagSet(FLAG_S);
    case COND_SN: return isFlagSet(FLAG_S);
    default: return 0;
  }
}

inline void CpuGB::resetFlag(u8 flag)
{
  r.AF.F ^= flag;
}

inline void CpuGB::storeSingle(u8 reg, u8 value)
{
  if (reg == REGS_HL)
    mem->write(r.HL.HL, value);
  else
    *r.rr[reg] = value;
}

inline u8 CpuGB::loadSingle(u8 reg)
{
  if (reg == REGS_HL)
    return mem->read(r.HL.HL);
  else
    return *r.rr[reg];
}

inline void CpuGB::storeDoubleSP(u8 reg, u16 value)
{
  *r.rrrsp[reg] = value;
}

inline u16 CpuGB::loadDoubleSP(u8 reg)
{
  return *r.rrrsp[reg];
}

inline void CpuGB::storeDoubleAF(u8 reg, u16 value)
{
  if (reg == REG_AF)
    value &= 0xFFF0;
  
  *r.rrraf[reg] = value;
}

inline u16 CpuGB::loadDoubleAF(u8 reg)
{
  u16 value = *r.rrraf[reg];
  
  if (reg == REG_AF)
    value &= 0xFFF0;
  
  return value;
}

inline u16 CpuGB::popDoubleSP()
{
  u8 l = mem->read(r.SP++);
  u8 h = mem->read(r.SP++);
  return (h << 8) | l;
}

inline void CpuGB::pushDoubleSP(u16 value)
{
  mem->write(--r.SP, value >> 8);
  mem->write(--r.SP, value & 0xFF);
}

inline u16 CpuGB::loadDoublePC()
{
  u8 l = mem->read(r.PC++);
  u8 h = mem->read(r.PC++);
  return (h << 8) | l;
}

u8 CpuGB::executeInstruction(u8 opcode)
{	
  u8 op = opcode, op2 = -1;
  bool branchTaken = true;
  
  /* HALT */
  if (opcode == OPCODE_HALT)
  {
    halted = true;
  }
  /* LD r, r' */
  else if ((opcode & 0xC0) == OPCODE_LD_R_R)
  {
    u8 s = opcode & 0x07;
    u8 d = (opcode & 0x38) >> 3;

    storeSingle(d, loadSingle(s));
  }
  /* LD r, n */
  else if ((opcode & 0xC7) == OPCODE_LD_R_N)
  {
    u8 value = mem->read(r.PC++);
    u8 d = (opcode & 0x38) >> 3;
    
    storeSingle(d, value);
  }
  /* LD rr, nn */
  else if ((opcode & 0xCF) == OPCODE_LD_RR_NN)
  {
    u8 d = (opcode & 0x30) >> 4;
    
    u8 l = mem->read(r.PC++);
    u8 h = mem->read(r.PC++);
    
    u16 value = h << 8 | l;
    
    storeDoubleSP(d, value);
  }
  /* LD (BC), A */
  else if (opcode == OPCODE_LD_BC_A)
  {
    mem->write(r.BC.BC, r.AF.A);
  }
  /* LD (DE), A */
  else if (opcode == OPCODE_LD_DE_A)
  {
    mem->write(r.DE.DE, r.AF.A);
  }
  /* LD (nn), A - LDD (HL), A*/
  else if (opcode == OPCODE_LD_NN_A)
  {
    mem->write(r.HL.HL, r.AF.A);
    --r.HL.HL;
  }
  /* LD A, (BC) */
  else if (opcode == OPCODE_LD_A_BC)
  {
    r.AF.A = mem->read(r.BC.BC);
  }
  /* LD A, (DE) */
  else if (opcode == OPCODE_LD_A_DE)
  {
    r.AF.A = mem->read(r.DE.DE);
  }
  /* LD A, (nn) - LDD A, (HL) */
  else if (opcode == OPCODE_LD_A_NN)
  {
    r.AF.A = mem->read(r.HL.HL);
    --r.HL.HL;
  }
  /* LD (nn), HL - LDI (HL), A */
  else if (opcode == OPCODE_LD_NN_HL)
  {
    mem->write(r.HL.HL, r.AF.A);
    ++r.HL.HL;
  }
  /* LD HL, (nn) - LDI A, (HL) */
  else if (opcode == OPCODE_LD_HL_NN)
  {
    r.AF.A = mem->read(r.HL.HL);
    ++r.HL.HL;
  }
  /* LD SP, HL */
  else if (opcode == OPCODE_LD_SP_HL)
  {
    r.SP = r.HL.HL;
  }
  
  /* INC rr */
  else if ((opcode & 0xCF) == OPCODE_INC_RR)
  {
    u8 d = (opcode & 0x30) >> 4;
    
    storeDoubleSP(d, loadDoubleSP(d)+1);
    
  }
  /* INC r */
  else if ((opcode & 0xC7) == OPCODE_INC_R)
  {
    u8 d = (opcode & 0x38) >> 3;
    
    u8 value = loadSingle(d);
    setFlag(FLAG_H, (value & 0x0F) == 0x0F);
    storeSingle(d, ++value);
    
    /* TODO: in official manual it states that C flag is not modified
     but it should be implemented as an ADD 1 */

    setFlag(FLAG_S, value & 0x80);
    setFlag(FLAG_Z, value == 0x00);
    setFlag(FLAG_PV, value == 0x80);
    setFlag(FLAG_N, 0);
  }
  /* DEC rr */
  else if ((opcode & 0xCF) == OPCODE_DEC_RR)
  {
    u8 d = (opcode & 0x30) >> 4;
    storeDoubleSP(d, loadDoubleSP(d)-1);
    
  }
  /* DEC r */
  else if ((opcode & 0xC7) == OPCODE_DEC_R)
  {
    u8 d = (opcode & 0x38) >> 3;
    
    u8 value = loadSingle(d);
    setFlag(FLAG_H, (value & 0x0F) == 0x00);
    storeSingle(d, --value);
    
    /* TODO: in official manual it states that C flag is not modified
     but it should be implemented as an ADD 1 */
    
    setFlag(FLAG_S, value & 0x80);
    setFlag(FLAG_Z, value == 0x00);
    setFlag(FLAG_PV, value == 0x7F);
    setFlag(FLAG_N, 1);
  }
  
  /*** ARITHMETIC REGISTER ***/
  /* ADD A, r */
  else if ((opcode & 0xF8) == OPCODE_ADD_R)
  {
    u8 s = (opcode & 0x07);
    u8 value = loadSingle(s);
    
    add(value);
    
    setFlag(FLAG_N, 0);
  }
  /* ADC A, r */
  else if ((opcode & 0xF8) == OPCODE_ADC_R)
  {
    u8 s = (opcode & 0x07);
    u8 value = loadSingle(s);
    
    adc(value);
    
    setFlag(FLAG_N, 0);
  }
  /* SUB A, r */
  else if ((opcode & 0xF8) == OPCODE_SUB_R)
  {
    u8 s = (opcode & 0x07);
    u8 value = loadSingle(s);
    
    sub(value);
    
    setFlag(FLAG_N, 1);
  }
  /* SBC A, r */
  else if ((opcode & 0xF8) == OPCODE_SBC_R)
  {
    u8 s = (opcode & 0x07);
    u8 value = loadSingle(s);
    
    sbc(value);
    
    setFlag(FLAG_N, 1);
  }
  /* DAA */
  else if (opcode == 0x27)
  {
    daa();
  }
  /* AND A, r */
  else if ((opcode & 0xF8) == OPCODE_AND_R)
  {
    u8 s = (opcode & 0x07);
    u8 value = loadSingle(s);
    
    r.AF.A &= value;
    
    setFlag(FLAG_S, r.AF.A & 0x80);
    setFlag(FLAG_Z, r.AF.A == 0);
    setFlag(FLAG_H, 1);
    setFlag(FLAG_PV, parity(r.AF.A) ? 1 : 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_C, 0);
  }
  /* XOR A, r */
  else if ((opcode & 0xF8) == OPCODE_XOR_R)
  {
    u8 s = (opcode & 0x07);
    u8 value = loadSingle(s);
    
    r.AF.A ^= value;
    
    setFlag(FLAG_S, r.AF.A & 0x80);
    setFlag(FLAG_Z, r.AF.A == 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_PV, parity(r.AF.A) ? 1 : 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_C, 0);
  }
  /* OR A, r */
  else if ((opcode & 0xF8) == OPCODE_OR_R)
  {
    u8 s = (opcode & 0x07);
    u8 value = loadSingle(s);
    
    r.AF.A |= value;
    
    setFlag(FLAG_S, r.AF.A & 0x80);
    setFlag(FLAG_Z, r.AF.A == 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_PV, parity(r.AF.A) ? 1 : 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_C, 0);
  }
  /* CP A, r */
  else if ((opcode & 0xF8) == OPCODE_CP_R)
  {
    u8 s = (opcode & 0x07);
    u8 back = r.AF.A;
    u8 value = loadSingle(s);
    
    sub(value);
    
    r.AF.A = back;
    
    setFlag(FLAG_N, 1);
  }
  else if ((opcode & 0xCF) == OPCODE_ADD_HL_RR)
  {
    u8 s = (opcode & 0x30) >> 4;
    u16 b = loadDoubleSP(s);
    u16 a = r.HL.HL;
    
    u8 carryOut, halfCarry;
    u16 res;

    carryOut = (a > 0xFFFF - b);
    res = a + b;
    halfCarry = (a&0x0FFF) + (b&0xFFF) > 0xFFF;

    r.HL.HL = res;
    
    setFlag(FLAG_C, carryOut);
    setFlag(FLAG_H, halfCarry);
    setFlag(FLAG_N, 0);
  }
  
  /*** ARITHMETIC IMMEDIATE ***/
  /* ADD A, n */
  else if (opcode == OPCODE_ADD_N)
  {
    u8 value = mem->read(r.PC++);
    
    add(value);
    
    setFlag(FLAG_N, 0);
  }
  /* ADC A, n */
  else if (opcode == OPCODE_ADC_N)
  {
    u8 value = mem->read(r.PC++);
    
    adc(value);
    
    setFlag(FLAG_N, 0);
  }
  /* SUB A, n */
  else if (opcode == OPCODE_SUB_N)
  {
    u8 value = mem->read(r.PC++);
    
    sub(value);
    
    setFlag(FLAG_N, 1);
  }
  /* SBC A, n */
  else if (opcode == OPCODE_SBC_N)
  {
    u8 value = mem->read(r.PC++);
    
    sbc(value);
    
    setFlag(FLAG_N, 1);
  }
  /* AND A, n */
  else if (opcode == OPCODE_AND_N)
  {
    u8 value = mem->read(r.PC++);
    
    r.AF.A &= value;
    
    setFlag(FLAG_S, r.AF.A & 0x80);
    setFlag(FLAG_Z, r.AF.A == 0);
    setFlag(FLAG_H, 1);
    setFlag(FLAG_PV, parity(r.AF.A) ? 1 : 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_C, 0);
  }
  /* XOR A, n */
  else if (opcode == OPCODE_XOR_N)
  {
    u8 value = mem->read(r.PC++);
    
    r.AF.A ^= value;
    
    setFlag(FLAG_S, r.AF.A & 0x80);
    setFlag(FLAG_Z, r.AF.A == 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_PV, parity(r.AF.A) ? 1 : 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_C, 0);
  }
  /* OR A, n */
  else if (opcode == OPCODE_OR_N)
  {
    u8 value = mem->read(r.PC++);
    
    r.AF.A |= value;
    
    setFlag(FLAG_S, r.AF.A & 0x80);
    setFlag(FLAG_Z, r.AF.A == 0);
    setFlag(FLAG_H, 0);
    setFlag(FLAG_PV, parity(r.AF.A) ? 1 : 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_C, 0);
  }
  /* CP A, n */
  else if (opcode == OPCODE_CP_N)
  {
    u8 back = r.AF.A;
    u8 value = mem->read(r.PC++);
    
    sub(value);
    
    r.AF.A = back;
    
    setFlag(FLAG_N, 1);
  }
    
  /* MISC */
  else if (opcode == OPCODE_CPL)
  {
    r.AF.A = ~r.AF.A;
    
    setFlag(FLAG_H, 1);
    setFlag(FLAG_N, 1);
  }
  else if (opcode == OPCODE_SCF)
  {
    setFlag(FLAG_H, 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_C, 1);
  }
  else if (opcode == OPCODE_CCF)
  {
    setFlag(FLAG_H, 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_C, isFlagSet(FLAG_C) ? 0 : 1);
  }
  
  
  /* JUMPS */
  /* DJNZ n - STOP */
  else if (opcode == OPCODE_DJNZ_N)
  {
    // if a speed switch was requested
    u8 speed = mem->rawPortRead(PORT_KEY1);
    
    if (Utils::bit(speed, 0))
    {
      // if CPU was in double mode
      if (Utils::bit(speed, 7))
      {
        emu->toggleDoubleSpeed(false);
        mem->rawPortWrite(PORT_KEY1, 0x00);
      }
      else
      {
        emu->toggleDoubleSpeed(true);
        mem->rawPortWrite(PORT_KEY1, 0x80);
      }
      
      //s.interruptsEnabled = true;
      //mem->write(PORT_IF, 0x1F);
    }
    
    halted = true;
  }
  /* JR n */
  else if (opcode == OPCODE_JR_N)
  {
    s8 value = mem->read(r.PC++);
    r.PC += value;
  }
  else if (opcode == OPCODE_JRNZ_N)
  {
    if (!isFlagSet(FLAG_Z))
    {    
      s8 value = mem->read(r.PC++);
      r.PC += value;
    }
    else
    {
      ++r.PC;
      branchTaken = false;
    }
  }
  else if (opcode == OPCODE_JRZ_N)
  {
    if (isFlagSet(FLAG_Z))
    {    
      s8 value = mem->read(r.PC++);
      r.PC += value;
    }
    else
    {
      ++r.PC;
      branchTaken = false;
    }
  }
  else if (opcode == OPCODE_JRNC_N)
  {
    if (!isFlagSet(FLAG_C))
    {    
      s8 value = mem->read(r.PC++);
      r.PC += value;
    }
    else
    {
      ++r.PC;
      branchTaken = false;
    }
  }
  else if (opcode == OPCODE_JRC_N)
  {
    if (isFlagSet(FLAG_C))
    {    
      s8 value = mem->read(r.PC++);
      r.PC += value;
    }
    else
    {
      ++r.PC;
      branchTaken = false;
    }
  }
  else if (opcode == OPCODE_JP_HL)
  {
    r.PC = r.HL.HL;
  }
  else if (opcode == OPCODE_JP_NN)
  {    
    r.PC = loadDoublePC();
  }
  else if ((opcode & 0xC7) == OPCODE_JP_CC_NN)
  {
    u8 cond = (opcode >> 3) & 0x07;
    
    if (cond >= 4)
    {
      switch (cond) {
        /* LD (FF00+C), A */
        case COND_PO: {
          mem->write(0xFF00|r.BC.C, r.AF.A);
          break;
        }
        /* LD (nn), A */
        case COND_PE: {
          mem->write(loadDoublePC(), r.AF.A);
          break;
        }
        /* LD A, (FF00+C) */
        case COND_SP: {
          r.AF.A = mem->read(0xFF00|r.BC.C);
          break;
        }
        /* LD A, (nn) */
        case COND_SN: {
          r.AF.A = mem->read(loadDoublePC());
          break;
        }
      }
    }
    else
    {    
      if (isConditionTrue(cond))
      {
        r.PC = loadDoublePC();
      }
      else
      {
        r.PC += 2;
        branchTaken = false;
      }
    }
  }
  
  /*** CALLS ***/
  /* CALL nn */
  else if (opcode == OPCODE_CALL_NN)
  {
    u16 address = loadDoublePC();
    pushDoubleSP(r.PC);
    r.PC = address;
  }
  /* CALL cc nn */
  else if ((opcode & 0xC7) == OPCODE_CALL_CC_NN)
  {
    u8 cond = (opcode >> 3) & 0x07;
    
    if (cond >= 4)
    {
      halt();
    }
    else
    {    
      if (isConditionTrue(cond))
      {
        u16 address = loadDoublePC();
        pushDoubleSP(r.PC);
        r.PC = address;
      }
      else
      {
        r.PC += 2;
        branchTaken = false;
      }
    }
  }
  /* RST */
  else if ((opcode & 0xC7) == 0xC7)
  {
    u8 address = ((opcode & 0x38) >> 3) * 0x08;
    pushDoubleSP(r.PC);
    r.PC = address;
    
  }
  else if (opcode == OPCODE_RET)
  {
    r.PC = popDoubleSP();
  }
  else if ((opcode & 0xC7) == OPCODE_RET_CC)
  {
    u8 cond = (opcode >> 3) & 0x07;
    
    if (cond >= 4)
    {
      switch (cond) {
        /* LD (FF00+n), A */
        case COND_PO: {
          u8 p = mem->read(r.PC++);
          mem->write(0xFF00|p, r.AF.A);
          break;
        }
        /* ADD SP, dd */
        case COND_PE: {
          s8 p = mem->read(r.PC++);
          u8 b = (u8)p;
          u8 a = r.SP;
          
          bool carryOut = ((a&0x00FF) > 0xFF - (b&0x00FF));
          bool halfCarry = (a&0x000F) + (b&0x000F) > 0x000F;
          
          setFlag(FLAG_C, carryOut);
          setFlag(FLAG_H, halfCarry);

          setFlag(FLAG_Z, 0);
          setFlag(FLAG_N, 0);
          
          r.SP += p;
          break;
        }
        /* LD A, (FF00+n) */
        case COND_SP: {
          u8 p = mem->read(r.PC++);
          r.AF.A = mem->read(0xFF00|p);
          break;
        }
        /* LD HL, SP+dd*/
        case COND_SN: {
          s8 p = mem->read(r.PC++);
          u8 b = (u8)p;
          u8 a = r.SP;
          
          bool carryOut = ((a&0x00FF) > 0xFF - (b&0x00FF));
          bool halfCarry = (a&0x000F) + (b&0x000F) > 0x000F;

          setFlag(FLAG_C, carryOut);
          setFlag(FLAG_H, halfCarry);
          setFlag(FLAG_Z, 0);
          setFlag(FLAG_N, 0);
          
          r.HL.HL = r.SP + p;
          break;
        }
      }
    }
    else
    {
      if (isConditionTrue(cond))
      {
        r.PC = popDoubleSP();
      }
      else
      {
        branchTaken = false;
      }
    }
  }
  else if ((opcode & 0xCF) == OPCODE_POP)
  {
    u8 d = (opcode >> 4) & 0x03;
    storeDoubleAF(d, popDoubleSP());
  }
  else if ((opcode & 0xCF) == OPCODE_PUSH)
  {
    u8 d = (opcode >> 4) & 0x03;
    pushDoubleSP(loadDoubleAF(d));

  }
  
  
  /* ROTATE AND SHIFT */
  else if (opcode == OPCODE_RLCA)
  {
    u8 value = r.AF.A;
    
    setFlag(FLAG_H, 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_Z, 0);
    setFlag(FLAG_C, value & 0x80); 
    
    r.AF.A = ((u8)(value << 1)) | (value >> 7);
  }
  else if (opcode == OPCODE_RLA)
  {
    u8 value = r.AF.A;
    
    setFlag(FLAG_H, 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_Z, 0);
    
    r.AF.A = ((u8)(value << 1)) | (isFlagSet(FLAG_C) ? 1 : 0);
    
    setFlag(FLAG_C, value & 0x80); 
  }
  else if (opcode == OPCODE_RRCA)
  {
    u8 value = r.AF.A;
    
    setFlag(FLAG_H, 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_Z, 0);
    setFlag(FLAG_C, value & 0x01);
    
    r.AF.A = ((u8)(value >> 1)) | ((u8)(value << 7));
  }
  else if (opcode == OPCODE_RRA)
  {
    u8 value = r.AF.A;
    
    setFlag(FLAG_H, 0);
    setFlag(FLAG_N, 0);
    setFlag(FLAG_Z, 0);
    
    r.AF.A = ((u8)(value >> 1)) | (isFlagSet(FLAG_C) ? 0x80 : 0);
    
    setFlag(FLAG_C, value & 0x01); 
  }
  
  /* CB BITS OPERATIONS */
  else if (opcode == OPCODE_BITS)
  {
    opcode = mem->read(r.PC++);
    op2 = opcode;
    
    u8 b = (opcode & 0x38) >> 3;
    u8 r = opcode & 0x07;
    u8 v = loadSingle(r);
    
    u8 sopcode = opcode & 0xC0;
    
    if (sopcode == OPCODE_BIT)
    {
      setFlag(FLAG_Z, (v & (1 << b)) == 0);
      setFlag(FLAG_H, 1);
      setFlag(FLAG_N, 0);
    }
    else if (sopcode == OPCODE_RES)
    {
      storeSingle(r, v & ~(1 << b));
    }
    else if (sopcode == OPCODE_SET)
    {
      storeSingle(r, v | (1 << b));
    }
    else
    {
      u8 sopcode = opcode & 0xF8;
      
      switch (sopcode) {
        case OPCODE_RLC: {
          
          setFlag(FLAG_H, 0);
          setFlag(FLAG_N, 0);
          setFlag(FLAG_C, v & 0x80);
                  
          v = ((u8)(v << 1)) | (v >> 7);
          
          storeSingle(r, v);
                  
          setFlag(FLAG_S, v & 0x80); 
          setFlag(FLAG_Z, v == 0x00);
          setFlag(FLAG_PV, parity(v) ? 1 : 0);
          
          break;
        }
        case OPCODE_RRC: {

          setFlag(FLAG_H, 0);
          setFlag(FLAG_N, 0);
          setFlag(FLAG_C, v & 0x01);
          
          v = ((u8)(v >> 1)) | ((u8)(v << 7));
          storeSingle(r, v);
          
          setFlag(FLAG_S, v & 0x80);
          setFlag(FLAG_Z, v == 0x00);
          setFlag(FLAG_PV, parity(v) ? 1 : 0);
        
          break;
        }
        case OPCODE_RL: {
          
          setFlag(FLAG_H, 0);
          setFlag(FLAG_N, 0);
          bool wasCarry = isFlagSet(FLAG_C);
          setFlag(FLAG_C, v & 0x80);

          v = ((u8)(v << 1)) | (wasCarry ? 1 : 0);
          storeSingle(r, v);
          
          setFlag(FLAG_S, v & 0x80);
          setFlag(FLAG_Z, v == 0x00);
          setFlag(FLAG_PV, parity(v) ? 1 : 0);
          
          break;
        }
        case OPCODE_RR: {
          
          setFlag(FLAG_H, 0);
          setFlag(FLAG_N, 0);
          bool wasCarry = isFlagSet(FLAG_C);
          setFlag(FLAG_C, v & 0x01);
          
          v = ((u8)(v >> 1)) | (wasCarry ? 0x80 : 0);
          storeSingle(r, v);
          
          setFlag(FLAG_S, v & 0x80);
          setFlag(FLAG_Z, v == 0x00);
          setFlag(FLAG_PV, parity(v) ? 1 : 0);
          
          break;
        }
        case OPCODE_SLA: {
          
          setFlag(FLAG_H, 0);
          setFlag(FLAG_N, 0);
          setFlag(FLAG_C, v & 0x80);
          
          v = (u8)(v << 1);
          storeSingle(r, v);
          
          setFlag(FLAG_S, v & 0x80);
          setFlag(FLAG_Z, v == 0x00);
          setFlag(FLAG_PV, parity(v) ? 1 : 0);
          
          break;
        }
        case OPCODE_SRA: {
          
          setFlag(FLAG_H, 0);
          setFlag(FLAG_N, 0);
          setFlag(FLAG_C, v & 0x01);
          
          v = (u8)(v >> 1 | (v & 0x80));
          storeSingle(r, v);
          
          setFlag(FLAG_S, v & 0x80);
          setFlag(FLAG_Z, v == 0x00);
          setFlag(FLAG_PV, parity(v) ? 1 : 0);
          
          break;
        }
        /* SLL r - SWAP r */
        case OPCODE_SLL: {
          
          setFlag(FLAG_H, 0);
          setFlag(FLAG_N, 0);
          setFlag(FLAG_C, 0);
        
          v = (u8)((v >> 4) | (v << 4));
          storeSingle(r, v);
        
          setFlag(FLAG_Z, v == 0x00);
          
          break;
        }
        case OPCODE_SRL: {
          
          setFlag(FLAG_H, 0);
          setFlag(FLAG_N, 0);
          setFlag(FLAG_C, v & 0x01);
          
          v = (u8)(v >> 1);
          storeSingle(r, v);
          
          setFlag(FLAG_S, v & 0x80);
          setFlag(FLAG_Z, v == 0x00);
          setFlag(FLAG_PV, parity(v) ? 1 : 0);
          
          break;
        }
      }
    }
  }
  
  
  else if (opcode == OPCODE_EI)
  {
    s.interruptsEnabled = true;
  }
  else if (opcode == OPCODE_DI)
  {
    s.interruptsEnabled = false;
  }
  
  else if (opcode == OPCODE_OUT_N_A)
  {
    halt();
  }
  else if (opcode == OPCODE_IN_N_A)
  {
    halt();
  }
  /* EX AF, AF' - LD (nn), SP */
  else if (opcode == OPCODE_EX_AF_AF)
  {
    u8 l = mem->read(r.PC++);
    u8 h = mem->read(r.PC++);
    u16 address = (h << 8) | l;
  
    mem->write(address, r.SP & 0xFF);
    mem->write(address+1, r.SP >> 8);
  }
  else if (opcode == OPCODE_EX_SP_HL)
  {
    halt();
  }
  else if (opcode == OPCODE_EX_DE_HL)
  {
    halt();   
  }
  /* EXX - RETI */
  else if (opcode == OPCODE_EXX)
  {
    r.PC = popDoubleSP();
    s.interruptsEnabled = true;
  }
  
  else if (opcode == OPCODE_NOP)
	{
		/* idleing */
	}
  
  return Opcodes::cpuCycles(op, op2, branchTaken);
}

u8 CpuGB::executeSingle()
{
	if (s.running)
  {  
    /* read a byte to get opcode */
    u8 opcode = mem->read(r.PC);
    
    ++r.PC;
    
    return executeInstruction(opcode);
  }
  else return 0;
}





