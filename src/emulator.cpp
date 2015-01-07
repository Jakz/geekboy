#include "emulator.h"

#include "cpu.h"

using namespace gb;

constexpr u32 Emulator::timerFrequencies[4];

Emulator::Emulator() : cpu(new CpuGB(this)), mem(new Memory(this)), sound(GBSound())
{
  this->timerCounter = 1024;
  this->cycles = 0;
  this->mode = MODE_GB;
  
  this->display = new Display<PixelFormat::ARGB565>(cpu,mem,this);
  
  cpu->setMemory(mem);
  
  keysState = 0xFF;
  doubleSpeed = false;
  cyclesAdjust = 0;
}

void Emulator::setupSound(int sampleRate)
{
  sound.start(sampleRate);
}

u8 Emulator::step()
{
  u8 cycles;
  
  if (!cpu->halted)
    cycles = cpu->executeSingle();
  else
    cycles = 4;
  
  this->cycles += cycles;
  
  updateTimers(cycles);
  display->update(cycles);
  cpu->manageInterrupts();
  
  return cycles;
}

bool Emulator::run(u32 maxCycles)
{
  maxCycles -= cyclesAdjust;
  
  u32 cyclesTotal = 0;
  
  if (doubleSpeed) maxCycles *= 2;

  while (cyclesTotal < maxCycles)
  {
    u8 cycles;

    if (!cpu->halted)
      cycles = cpu->executeSingle();
    else
      cycles = 4;

    cyclesTotal += cycles;
    
    updateTimers(cycles);
    
    if (doubleSpeed)
    {
      display->update(cycles/2);
    }
    else
    {
      display->update(cycles);
    }
    

    cpu->manageInterrupts();
  }
  
  sound.update();
  
  cyclesAdjust = cyclesTotal - maxCycles;
  
  cycles += cyclesTotal;
  
  /*for (int i = 0; i < 128; ++i)
    printf("%.2X", mem->memoryMap()->color_palette_ram[i]);
  printf("\n");*/
  
  return true;
}

void Emulator::init()
{
  cpu->reset();
  
  Registers *regs = cpu->regs();
  
  regs->PC = 0x0100;
  
  if (mode == MODE_GB)
    regs->AF.AF = 0x01B0;
  else
    regs->AF.AF = 0x11B0;

  regs->BC.BC = 0x0013;
  regs->DE.DE = 0x00D8;
  regs->HL.HL = 0x014D;
  regs->SP = 0xFFFE;

  mem->rawPortWrite(0xFF05, 0x00);
  mem->rawPortWrite(0xFF06, 0x00);
  mem->rawPortWrite(0xFF07, 0x00);
  mem->rawPortWrite(0xFF10, 0x80);
  mem->rawPortWrite(0xFF11, 0xBF);
  mem->rawPortWrite(0xFF12, 0xF3);
  mem->rawPortWrite(0xFF14, 0xBF);
  mem->rawPortWrite(0xFF16, 0x3F);
  mem->rawPortWrite(0xFF17, 0x00);
  mem->rawPortWrite(0xFF19, 0xBF);
  mem->rawPortWrite(0xFF1A, 0x7F);
  mem->rawPortWrite(0xFF1B, 0xFF);
  mem->rawPortWrite(0xFF1C, 0x9F);
  mem->rawPortWrite(0xFF1E, 0xBF);
  mem->rawPortWrite(0xFF20, 0xFF);
  mem->rawPortWrite(0xFF21, 0x00);
  mem->rawPortWrite(0xFF22, 0x00);
  mem->rawPortWrite(0xFF23, 0xBF);
  mem->rawPortWrite(0xFF24, 0x77);
  mem->rawPortWrite(0xFF25, 0xF3);
  mem->rawPortWrite(0xFF26, 0xF1);
  mem->rawPortWrite(0xFF40, 0x91);
  mem->rawPortWrite(0xFF42, 0x00);
  mem->rawPortWrite(0xFF43, 0x00);
  mem->rawPortWrite(0xFF45, 0x00);
  mem->rawPortWrite(0xFF47, 0xFC);
  mem->rawPortWrite(0xFF48, 0xFF);
  mem->rawPortWrite(0xFF49, 0xFF);
  mem->rawPortWrite(0xFF4A, 0x00);
  mem->rawPortWrite(0xFF4B, 0x00);
  mem->rawPortWrite(0xFFFF, 0x00);
  
  dividerCounter = CYCLES_PER_DIVIDER_INCR;
  resetTimerCounter();
  
  doubleSpeed = false;
  
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
      u8 counter = mem->read(PORT_TIMA);
      
      // if we reached overflow of timer then request an interrupt
      // and reset it according to TMA register
      if (counter == 0xFF)
      {
        mem->rawPortWrite(PORT_TIMA, mem->read(PORT_TMA));
        requestInterrupt(INT_TIMER);
      }
      // just increment it
      else
        mem->rawPortWrite(PORT_TIMA, counter + 1);
      
      timerCounter += timerTicks();
    }
  }

  dividerCounter -= cycles;
  
  // if divider register should be incremented
  if (dividerCounter <= 0)
  {
    // read current value and increment it by one
    u8 t = mem->read(PORT_DIV);
    
    // increase it or make it wrap
    if (t == 255) t = 0;
    else ++t;
    
    // write updated value on address by skipping normal procedure
    mem->rawPortWrite(PORT_DIV, t);
    
    // reset counter for next divider increment
    dividerCounter = CYCLES_PER_DIVIDER_INCR + dividerCounter;
  }
}

void Emulator::requestInterrupt(u8 interrupt)
{
  cpu->enableInterrupt(interrupt);
}

void Emulator::resetTimerCounter()
{
  timerCounter = timerTicks();
}

u32 Emulator::timerTicks()
{
  u32 frequency = timerFrequencies[mem->read(PORT_TAC) & 0x03];
  
  return CYCLES_PER_SECOND / frequency;
}

bool Emulator::isTimerEnabled()
{
  return Utils::bit(mem->read(PORT_TAC), 2);
}

void Emulator::keyPressed(Key key)
{
  // check if key was unpressed to it's changing
  bool isChanging = Utils::bit(keysState, key);
  
  // set button bit to 0 (that is ACTIVE)
  keysState = Utils::res(keysState, key);
  
  bool isDirectional = key < 4;
  
  u8 joyp = mem->rawPortRead(PORT_JOYP);
  
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
