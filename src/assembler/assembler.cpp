#include "assembler.h"

#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;
using namespace assembler;

constexpr BinaryCode Assembler::INVALID;

void Assembler::error(const location& l, const std::string& m)
{
  cerr << "Error at " << file << ": " << (l.begin.line+1) << "," << l.begin.column << " : " << m << endl;
}

void Assembler::warning(const location& l, const std::string& m)
{
  cerr << "Warning at " << file << ": " << (l.begin.line+1) << "," << l.begin.column << " : " << m << endl;
}

void Assembler::error(const std::string& m)
{
  cerr << "Error: " << m << endl;
}

void Assembler::init(int size)
{
  if (buffer)
    free(buffer);
  
  buffer = (u8*)calloc(size, sizeof(u8));
  position = 0;
}

void Assembler::assemble(int opcode, int opcode2, int opcode3)
{
  buffer[position++] = opcode;
  
  if (opcode2 != -1)
    buffer[position++] = opcode2;
  
  if (opcode3 != -1)
    buffer[position++] = opcode3;
}

bool Assembler::assembleFile(const std::string &filename)
{
  file = filename;
  
  ifstream is;
  is.open(filename);
  
  bool shouldGenerateTrace = false;
  
  assembler::Lexer lexer(*this, &is);
  assembler::Parser parser(lexer, *this);
  parser.set_debug_level(shouldGenerateTrace);
  int res = parser.parse();
  return res == 0;
}

bool Assembler::assembleLine(const std::string &text)
{
  file = "none";
  
  bool shouldGenerateTrace = false;
  
  istringstream ss(text);
  
  assembler::Lexer lexer(*this, &ss);
  assembler::Parser parser(lexer, *this);
  parser.set_debug_level(shouldGenerateTrace);
  return parser.parse() == 0;
}

BinaryCode Assembler::consolidate()
{
  u8 *code = (u8*)calloc(position, sizeof(u8));
  memcpy(code, buffer, position);
  
  BinaryCode pack;
  pack.code = code;
  pack.length = position;

  return pack;
}

void Assembler::aassert(bool value, const char *message)
{
  if (!value)
    fprintf(stderr, "[ASSEMBLER] Error: %s\n", message);
}