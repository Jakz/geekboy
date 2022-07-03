#ifndef _GB_DEBUGGER_H_
#define _GB_DEBUGGER_H_

#include <set>
#include <vector>
#include "utils.h"

#include "emulator.h"

struct DebuggerPort
{
  u16 address;
  const char *name;
};

enum DataWidth : u16
{
  WIDTH_U8 = 2,
  WIDTH_U16 = 4,
  WIDTH_U24 = 6,
  WIDTH_U32 = 8
};

struct DebuggerReg
{
  DataWidth type;
  u16 x;
  u16 y;
  const char *name;
};
  

class Debugger
{
  private:
    std::set<u16> breakPoints;
  
  public:
    Debugger(const char *cpuName, DataWidth widthAddress, DataWidth widthData, DataWidth widthMaxInstruction, std::vector<DebuggerPort> ports) :
    cpuName(cpuName),
    widthAddress(widthAddress), widthData(widthData), widthMaxInstruction(widthMaxInstruction),
    ports(ports)
    {}
  
    virtual void step() = 0;
    virtual void run() = 0;
    virtual void run(u32 cycles) = 0;
  
    virtual u16 PC() = 0;
    virtual u16 SP() = 0;
    virtual u8 read(u16 address) = 0;
    virtual u16 read16(u16 address) = 0;
  
    void toggleBreakPoint(u16 address);
    bool hasBreakPoint(u16 address);
  
    virtual u64 cycles() = 0;
  
    virtual u16 instructionLength(u8 opcode) = 0;
    virtual void instructionVisual(char *buffer, u8 d1 = 0, u8 d2 = 0, u8 d3 = 0, u8 d4 = 0) = 0;
    virtual void registerVisual(char *buffer, u8 line) = 0;
  
    const char* cpuName;
    const DataWidth widthAddress;
    const DataWidth widthData;
    const DataWidth widthMaxInstruction;
    std::vector<DebuggerPort> ports;
};
  
  
class DebuggerGB : public Debugger
{
private:
  gb::Emulator *emu;

public:
  DebuggerGB(gb::Emulator* emu);
  virtual u16 instructionLength(u8 opcode) override;
  virtual void instructionVisual(char *buffer, u8 d1 = 0, u8 d2 = 0, u8 d3 = 0, u8 d4 = 0) override;
  virtual void registerVisual(char *buffer, u8 line) override;
  
  void step() { emu->step(); }
  void run() { while (!hasBreakPoint(PC())) emu->step(); }
  void run(u32 cycles) { emu->run(cycles); }

  u64 cycles() { return emu->cycles; }
  u16 PC() { return emu->cpu.regs()->PC; }
  u16 SP() { return emu->cpu.regs()->SP; }
  u8 read(u16 address) {
    return emu->mem.read(address);
  }
  
  u16 read16(u16 address) {
    if (widthData == WIDTH_U8)
      return emu->mem.read(address);
    else if (widthData == WIDTH_U16)
      return emu->mem.read(address) || (emu->mem.read(address+1) << 8);
    
    return 0;
  }
};
  
#endif