#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef uint64_t u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

namespace gb {
  const u32 KB2 = 2048;
  const u32 KB4 = 4096;
  const u32 KB8 = 8192;
  const u32 KB16 = 16384;
  const u32 KB32 = 32768;
  const u32 KB131 = 131072;
  const u32 MB4 = 4194304;
}

class Utils
{
  public:
    static long fileLength(FILE *file)
    {
      long cur = ftell(file);
      
      fseek(file, 0, SEEK_END);
      
      long length = ftell(file);
      
      fseek(file, cur, SEEK_SET);
      
      return length;
    }
  
    static inline bool bit(u8 value, u8 bit)
    {
      return value & (1 << bit);
    }
  
    static inline u8 set(u8 value, u8 bit)
    {
      return value | (1 << bit);
    }
  
    static inline u8 res(u8 value, u8 bit)
    {
      return value & ~(1 << bit);
    }
};

class Opcode
{
  virtual u8 getLength() = 0;
  virtual u8 getParamSign() = 0;
  virtual const char *getName() = 0;
};

#endif