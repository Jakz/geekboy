#ifndef _UTILS_H_
#define _UTILS_H_

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#define strdup _strdup
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <unistd.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef uint64_t u64;

typedef signed char s8;
typedef signed short s16;
typedef signed int s32;

#define KB2 (2048)
#define KB4 (4096)
#define KB8 (8192)
#define KB16 (16384)
#define KB32 (32768)

#define KB131 (131072)

#define MB4 (4194304)

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