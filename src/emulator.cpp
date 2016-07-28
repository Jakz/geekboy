#include "emulator.h"

#include "cpu.h"

using namespace gb;

constexpr u32 Emulator::timerFrequencies[4];

Emulator::Emulator() : mem(Memory(*this)), cpu(CpuGB(*this))
#ifndef DEBUGGER
, sound(GBSound())
#endif
{
  this->timerCounter = 1024;
  this->cycles = 0;
  this->mode = MODE_GB;
  
  this->display = new Display<PixelFormat::ARGB51>(cpu,mem,*this);
  
  keysState = 0xFF;
  doubleSpeed = false;
  cyclesAdjust = 0;
}

void Emulator::setupSound(int sampleRate)
{
#ifndef DEBUGGER
  sound.start(sampleRate);
#endif
}

u8 Emulator::step()
{
  static char buffer[128];
  
  u8 d1 = mem.read(cpu.regs()->PC);
  u8 d2 = mem.read(cpu.regs()->PC+1);
  u8 d3 = mem.read(cpu.regs()->PC+2);
  
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
  
  printf("%04X: %s\n", cpu.regs()->PC, buffer);
  
  u8 cycles;
  
  if (!cpu.halted)
    cycles = cpu.executeSingle();
  else
    cycles = 4;
  
  this->cycles += cycles;
  
  updateTimers(cycles);
  display->update(cycles);
  cpu.manageInterrupts();
  return cycles;
}


/*
 
 ++pc;
 cycles += 4;
 updateTimers(4);
 ++pc;
 cycles += 4;
 updateTimers(2);
 u8 v = mem.read(cpu.regs()->HL.HL);
 cycles += 4;
 updateTimers(4);
 updateTimers(2);
 u8 b = 0;
 cpu.setFlag(FLAG_Z, (v & (1 << b)) == 0);
 cpu.setFlag(FLAG_H, 1);
 cpu.setFlag(FLAG_N, 0);
 */

bool Emulator::run(u32 maxCycles)
{
  maxCycles -= cyclesAdjust;
  
  u32 cyclesTotal = 0;
  
  if (doubleSpeed)
    maxCycles *= 2;
  
  lcdChangedState = false;
  
  while (cyclesTotal < maxCycles && !lcdChangedState)
  {
    u8 cycles = 0;
    
    u16& pc = cpu.regs()->PC;
    
    u8 opcode = mem.read(pc);

    /*if (opcode == 0xF0)
    {
      //salcazzo
      cycles += 4;
      ++pc;
      
      updateTimers(4);

      u8 value = mem.read(pc);
      ++pc;
      cycles += 4;
      
      updateTimers(2);
      
      cpu.regs()->AF.A = mem.read(0xFF00 | value);

      cycles += 4;
      
      updateTimers(6);
    }
    else*/
    {
    
    
    if (cpu.manageInterrupts())
      cycles = 12;
    else
    {
      if (!cpu.halted)
        cycles += cpu.executeSingle();
      else
        cycles += 4;
    }

    cyclesTotal += cycles;
    
    updateTimers(cycles);
      
    }
    
    if (doubleSpeed)
    {
      display->update(cycles/2);
    }
    else
    {
      display->update(cycles);
    }

  }
  
  //sound.update();
  
  if (!lcdChangedState)
    cyclesAdjust = cyclesTotal - maxCycles;
  
  cycles += cyclesTotal;
  return true;
}

void Emulator::init()
{
  cpu.reset();
  
  Registers *regs = cpu.regs();
  
  regs->PC = 0x0100;
  
  if (mode == MODE_GB)
    regs->AF.AF = 0x01B0;
  else
    regs->AF.AF = 0x11B0;

  regs->BC.BC = 0x0013;
  regs->DE.DE = 0x00D8;
  regs->HL.HL = 0x014D;
  regs->SP = 0xFFFE;

  mem.rawPortWrite(0xFF05, 0x00);
  mem.rawPortWrite(0xFF06, 0x00);
  mem.rawPortWrite(0xFF07, 0x00);
  mem.rawPortWrite(0xFF10, 0x80);
  mem.rawPortWrite(0xFF11, 0xBF);
  mem.rawPortWrite(0xFF12, 0xF3);
  mem.rawPortWrite(0xFF14, 0xBF);
  mem.rawPortWrite(0xFF16, 0x3F);
  mem.rawPortWrite(0xFF17, 0x00);
  mem.rawPortWrite(0xFF19, 0xBF);
  mem.rawPortWrite(0xFF1A, 0x7F);
  mem.rawPortWrite(0xFF1B, 0xFF);
  mem.rawPortWrite(0xFF1C, 0x9F);
  mem.rawPortWrite(0xFF1E, 0xBF);
  mem.rawPortWrite(0xFF20, 0xFF);
  mem.rawPortWrite(0xFF21, 0x00);
  mem.rawPortWrite(0xFF22, 0x00);
  mem.rawPortWrite(0xFF23, 0xBF);
  mem.rawPortWrite(0xFF24, 0x77);
  mem.rawPortWrite(0xFF25, 0xF3);
  mem.rawPortWrite(0xFF26, 0xF1);
  mem.rawPortWrite(0xFF40, 0x91);
  mem.rawPortWrite(0xFF42, 0x00);
  mem.rawPortWrite(0xFF43, 0x00);
  mem.rawPortWrite(0xFF45, 0x00);
  mem.rawPortWrite(0xFF47, 0xFC);
  mem.rawPortWrite(0xFF48, 0xFF);
  mem.rawPortWrite(0xFF49, 0xFF);
  mem.rawPortWrite(0xFF4A, 0x00);
  mem.rawPortWrite(0xFF4B, 0x00);
  mem.rawPortWrite(0xFFFF, 0x00);
  
  dividerCounter = CYCLES_PER_DIVIDER_INCR;
  resetTimerCounter();
  
  doubleSpeed = false;
  
}

void Emulator::timerTrigger()
{
  /* set TIMA according to TMA */
  mem.rawPortWrite(PORT_TIMA, mem.read(PORT_TMA));
  /* request timer interrupt */
  requestInterrupt(INT_TIMER);
}

void Emulator::updateTimers(u16 cycles)
{
  // if timer is enabled
  if (isTimerEnabled())
  {
    // update its counter
    //printf("%d - %d = %d\n", timerCounter, cycles, timerCounter-cycles);
    timerCounter -= cycles;
        
    // while the counter is expired
    while (timerCounter <= 0)
    {
      u8 counter = mem.read(PORT_TIMA);
      
      // if we overflowed
      if (counter == 0xFF)
      {
        //mem.rawPortWrite(PORT_TIMA, 0);
        /* TODO: real behavior delays trigger by 4 clock cycles and value of TIMA is 0 meanwhile */
        timerTrigger();
      }
      // just increment it
      else
        mem.rawPortWrite(PORT_TIMA, counter + 1);
      
      timerCounter += timerTicks();
    }
  }

  dividerCounter -= cycles;
  
  // if divider register should be incremented
  if (dividerCounter <= 0)
  {
    // read current value and increment it by one
    u8 t = mem.read(PORT_DIV);
    
    // increase it or make it wrap
    if (t == 255) t = 0;
    else ++t;
    
    // write updated value on address by skipping normal procedure
    mem.rawPortWrite(PORT_DIV, t);
    
    // reset counter for next divider increment
    dividerCounter = CYCLES_PER_DIVIDER_INCR + dividerCounter;
  }
}

void Emulator::requestInterrupt(Interrupt interrupt)
{
  cpu.enableInterrupt(interrupt);
}

void Emulator::resetDivCounter()
{
  dividerCounter = CYCLES_PER_DIVIDER_INCR;
}

void Emulator::resetTimerCounter()
{
  timerCounter = timerTicks();
}

u32 Emulator::timerTicks()
{
  u32 frequency = timerFrequencies[mem.read(PORT_TAC) & 0x03];
  
  return CYCLES_PER_SECOND / frequency;
}

bool Emulator::isTimerEnabled()
{
  return Utils::bit(mem.read(PORT_TAC), 2);
}



void Emulator::keyPressed(Key key)
{
  // check if key was unpressed to it's changing
  bool isChanging = Utils::bit(keysState, key);
  
  // set button bit to 0 (that is ACTIVE)
  keysState = Utils::res(keysState, key);
  
  bool isDirectional = key < 4;
  
  u8 joyp = mem.rawPortRead(PORT_JOYP);
  
  if (isChanging && ((isDirectional && !Utils::bit(joyp, 4)) || (!isDirectional && !Utils::bit(joyp, 5))))
    requestInterrupt(INT_JOYPAD);
}

void Emulator::keyReleased(Key key)
{
  keysState = Utils::set(keysState, key);
}

u8 Emulator::keyPadState(u8 joyp) const
{
  // directional buttons
  if (!Utils::bit(joyp, 5))
  {
    joyp |= 0x2F;
    joyp &= (keysState & 0x0F) | 0x20;
  }
  // normal buttons
  else if (!Utils::bit(joyp, 4))
  {
    joyp |= 0x1F;
    joyp &= ((keysState >> 4) & 0x0F) | 0x10;
  }
  
  return joyp;
}
