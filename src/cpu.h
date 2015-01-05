#ifndef _GB_Z80_H_
#define _GB_Z80_H_

#include "memory.h"
#include "opcodes.h"

namespace gb {

typedef unsigned char u8;
typedef unsigned short u16;

typedef signed char s8;

/*#define FLAG_S 0x80
#define FLAG_Z 0x40
// 0x20 not used
#define FLAG_H 0x10
// 0x08 not used
#define FLAG_PV 0x04
#define FLAG_N 0x02
#define FLAG_C 0x01*/
  
  const u8 FLAG_Z = 0x80;
  const u8 FLAG_N = 0x40;
  const u8 FLAG_H = 0x20;
  const u8 FLAG_C = 0x10;
  const u8 FLAG_PV = 0x08;
  const u8 FLAG_S = 0x04;
  
  const u8 REGS_B = 0x00;
  const u8 REGS_C = 0x01;
  const u8 REGS_D = 0x02;
  const u8 REGS_E = 0x03;
  const u8 REGS_H = 0x04;
  const u8 REGS_L = 0x05;
  const u8 REGS_HL = 0x06;
  const u8 REGS_A = 0x07;

  const u8 REG_BC = 0x00;
  const u8 REG_DE = 0x01;
  const u8 REG_HL = 0x02;
  const u8 REG_SP = 0x03;
  const u8 REG_AF = 0x03;

class Memory;
class Emulator;

enum Conditions
{
  COND_NZ = 0x00,
  COND_Z = 0x01,
  COND_NC = 0x02,
  COND_C = 0x03,
  COND_PO = 0x04,
  COND_PE = 0x05,
  COND_SP = 0x06,
  COND_SN = 0x07
};

enum Interrupts
{
  INT_VBLANK = 0,
  INT_STAT = 1,
  INT_TIMER = 2,
  INT_SERIAL = 3,
  INT_JOYPAD = 4
};

/* si usano le union perché con lo z80 ci sono registri a 8bit che possono essere uniti per farne uno a
   16 bit (per indirizzamento, etc) */
union AF_UNION
{
	struct
	{
		u8 F;
		u8 A;
	};
	
	u16 AF;
};

union BC_UNION
{
	struct
	{
		u8 C;
		u8 B;
	};
	
	u16 BC;
};

union DE_UNION
{
	struct
	{
		u8 E;
		u8 D;		
	};
	
	u16 DE;
};

union HL_UNION
{
	struct
	{
		u8 L;
		u8 H;		
	};
	
	u16 HL;
};

/* registri */
struct Registers
{
	u8** rr;
	u16** rrrsp;
  u16** rrraf;
	
	AF_UNION AF;
	BC_UNION BC;
	DE_UNION DE;
	HL_UNION HL;
	u16 SP;
	u16 PC;
};

/* stato della VM */
struct Status
{
	/* ogni quanti cicli di clock si suppone ci possa essere una interrupt */
	u16 intPeriod;
  bool interruptsEnabled;
  bool running;
};

class CpuGB
{
  private:
    Memory& mem;
    Emulator& emu;
    
    Registers r;
    Status s;
  
    u8 executeInstruction(u8 opcode);
  
    void storeSingle(u8 reg, u8 value);
    u8 loadSingle(u8 reg);
  
    void storeDoubleSP(u8 reg, u16 value);
    u16 loadDoubleSP(u8 reg);
  
    void storeDoubleAF(u8 reg, u16 value);
    u16 loadDoubleAF(u8 reg);
  
    u16 popDoubleSP();
    void pushDoubleSP(u16 value);
  
    u16 loadDoublePC();
    
    bool isConditionTrue(u8 cond);
    void halt();
  
  public:
    CpuGB(Emulator& emu);

    void resetFlag(u8 flag);
    void setFlag(u8 flag, u8 value);
    bool isFlagSet(u8 flag);
    
    void add(u8 value);
    void sub(u8 value);
    void adc(u8 value);
    void sbc(u8 value);
    void daa();
  
    bool parity(u8 value);
    
    void reset();
    u8 executeSingle();
  
    void enableInterrupt(u8 interrupt);
    void manageInterrupts();
  
    Registers *regs();
    Status *status();
  
    bool halted;
};

}

#endif
