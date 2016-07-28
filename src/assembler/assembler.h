#ifndef _GB_ASSEMBLER_H_
#define _GB_ASSEMBLER_H_

#include "../utils.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include "location.hh"

#include "gblexer.h"
#include "gbparser.hpp"

struct BinaryCode
{
  u8 *code;
  u32 length;
};

namespace assembler
{
  class Assembler
  {
    private:
    u8 *buffer;
    u16 position;
    
    public:
    
    std::string file;
    
    void init(int size);
    void assemble(int opcode, int opcode2 = -1, int opcode3 = -1);
    
    bool assembleLine(const std::string& text);
    bool assembleFile(const std::string& filename);
    
    BinaryCode consolidate();
    
    void warning(const location& l, const std::string& m);
    void error(const location& l, const std::string& m);
    void error(const std::string& m);
    
    void aassert(bool value, const char *message);
    
    bool correctRSTAddress(u16 val)
    {
      return (val % 8 == 0) && (val / 8 >= 0 && val / 8 <= 7);
    }
    
    constexpr static const BinaryCode INVALID = BinaryCode{nullptr, 0};

  };
}

#endif