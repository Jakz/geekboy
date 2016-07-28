#ifndef _GB_RTC_H_
#define _GB_RTC_H_

#include "utils.h"

#include "display.h"
#include "cpu.h"

#include <array>

namespace gb
{
  class RTC
  {
    static constexpr u8 BASE_REG = 0x08;
    
  private:
    using Regs = std::array<u8, 5>;
    
    Regs data;
    Regs latched;
    u8 selectedReg;
    bool preparedToLatch;
    
  public:
    RTC() : data({0,0,0,0,0}), latched({0,0,0,0,0}), selectedReg(0) { }
    
    
    void select(u8 value)
    {
      selectedReg = value - BASE_REG;
    }
    
    u8 read() { return latched[selectedReg]; }
    
    void writeData(u8 value)
    {
      
    }
    
    void writeLatch(u8 v)
    {
      if (v == 0x00 && !preparedToLatch)
        preparedToLatch = true;
      else if (v == 0x01 && preparedToLatch)
        std::copy(data.begin(), data.end(), data.begin());
    }

    void run(u32 cycles);
    
    
  };

}

#endif