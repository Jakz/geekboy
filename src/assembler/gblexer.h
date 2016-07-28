#ifndef __J80_SCANNER_H__
#define __J80_SCANNER_H__

#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer gbFlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL assembler::Parser::symbol_type assembler::Lexer::get_next_token()

#include "gbparser.hpp"

namespace assembler
{
  class Assembler;
  
  class Lexer : public yyFlexLexer
  {
  public:
    
    Lexer(Assembler &assembler, std::istream *in) : yyFlexLexer(in), assembler(assembler) {}
    
    virtual assembler::Parser::symbol_type get_next_token();
    virtual ~Lexer() { }
    
  private:
    
    Assembler &assembler;
  };
  
}

#endif