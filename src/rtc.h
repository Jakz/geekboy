#ifndef _GB_RTC_H_
#define _GB_RTC_H_

#include "utils.h"

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
    
    u8 read() const { return latched[selectedReg]; }
    
    void writeData(u8 value)
    {
      latched[selectedReg] = value;
      
      printf("RTC Write at %02x: %02x\n", BASE_REG+selectedReg, value);
      
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