%{
	#include "gbparser.hpp"
  #include "gblexer.h"
  #include "assembler.h"
  #include "../opcodes.h"
  #include "../utils.h"
  #include <string>
  
  typedef assembler::Parser::token token;
  
  #define yyterminate() assembler::Parser::make_END(loc);
  
  
  //
  
  static std::string buffer;
  static assembler::location loc;
  using namespace assembler;
%}

%x sstring

%option noyywrap
%option c++
%option yyclass="Lexer"
%option prefix="gb"


%{
  # define YY_USER_ACTION  loc.columns((int)yyleng);
%}


%%

%{
  loc.step();
%}

":" { return Parser::make_T_COLON(loc); }
"," { return Parser::make_T_COMMA(loc); }
"'" { return Parser::make_T_QUOTE(loc); }

"NOP"|"nop" { return Parser::make_OP_NOP(loc); }
"HALT"|"halt" { return Parser::make_OP_HALT(loc); }
"STOP"|"stop" { return Parser::make_OP_STOP(loc); } // GB

"LD"|"ld" { return Parser::make_OP_LD(loc); }
"LDI"|"ldi" { return Parser::make_OP_LDI(loc); } // GB
"LDD"|"ldd" { return Parser::make_OP_LDD(loc); } // GB

"ADD"|"add" { return Parser::make_OP_ADD(loc); }
"ADC"|"adc" { return Parser::make_OP_ADC(loc); }
"SUB"|"sub" { return Parser::make_OP_SUB(loc); }
"SBC"|"sbc" { return Parser::make_OP_SBC(loc); }
"DAA"|"daa" { return Parser::make_OP_DAA(loc); }

"AND"|"and" { return Parser::make_OP_AND(loc); }
"XOR"|"xor" { return Parser::make_OP_XOR(loc); }
"OR"|"or" { return Parser::make_OP_OR(loc); }
"CP"|"cp" { return Parser::make_OP_CP(loc); }

"INC"|"inc" { return Parser::make_OP_INC(loc); }
"DEC"|"dec" { return Parser::make_OP_DEC(loc); }

"CPL"|"cpl" { return Parser::make_OP_CPL(loc); }
"SCF"|"scf" { return Parser::make_OP_SCF(loc); }
"CCF"|"ccf" { return Parser::make_OP_CCF(loc); }

" NZ"|" nz" { return Parser::make_CC_COND(COND_NZ,loc); }
" Z"|" z" { return Parser::make_CC_COND(COND_Z,loc); }
" NCY"|" ncy" { return Parser::make_CC_COND(COND_NC,loc); }
" CY"|" cy" { return Parser::make_CC_COND(COND_C,loc); }
" PO"|" po" { return Parser::make_CC_COND(COND_PO,loc); }
" PE"|" pe" { return Parser::make_CC_COND(COND_PE,loc); }
" P"|" p" { return Parser::make_CC_COND(COND_SP,loc); }
" M"|" m" { return Parser::make_CC_COND(COND_SN,loc); }


"JR"|"jr" { return Parser::make_OP_JR(loc); }
"JR NZ"|"jr nz" { return Parser::make_OP_JRNZ(loc); }
"JR Z"|"jr z" { return Parser::make_OP_JRZ(loc); }
"JR NC"|"jr nc" { return Parser::make_OP_JRNC(loc); }
"JR C"|"jr c" { return Parser::make_OP_JRC(loc); }
"DJNZ"|"djnz" { return Parser::make_OP_DJNZ(loc); }

"JP"|"jp" { return Parser::make_OP_JP(loc); }
"CALL"|"call" { return Parser::make_OP_CALL(loc); }
"RST"|"rst" { return Parser::make_OP_RST(loc); }
"RET"|"ret" { return Parser::make_OP_RET(loc); }
"RETI"|"reti" { return Parser::make_OP_RETI(loc); }
"PUSH"|"push" { return Parser::make_OP_PUSH(loc); }
"POP"|"pop" { return Parser::make_OP_POP(loc); }

"BIT"|"bit" { return Parser::make_OP_BIT(loc); }
"RES"|"res" { return Parser::make_OP_RES(loc); }
"SET"|"set" { return Parser::make_OP_SET(loc); }

"RLCA"|"rlca" { return Parser::make_OP_RLCA(loc); }
"RLA"|"rla" { return Parser::make_OP_RLA(loc); }
"RRCA"|"rrca" { return Parser::make_OP_RRCA(loc); }
"RRA"|"rra" { return Parser::make_OP_RRA(loc); }

"RLC"|"rlc" { return Parser::make_OP_RLC(loc); }
"RL"|"rl" { return Parser::make_OP_RL(loc); }
"RRC"|"rrc" { return Parser::make_OP_RRC(loc); }
"RR"|"rr" { return Parser::make_OP_RR(loc); }
"SLA"|"sla" { return Parser::make_OP_SLA(loc); }
"SRA"|"sra" { return Parser::make_OP_SRA(loc); }
"SLL"|"sll" { return Parser::make_OP_SLL(loc); }
"SRL"|"srl" { return Parser::make_OP_SRL(loc); }
"SWAP"|"swap" { return Parser::make_OP_SWAP(loc); } // GB

"EI"|"ei" { return Parser::make_OP_EI(loc); }
"DI"|"di" { return Parser::make_OP_DI(loc); }


"OUT"|"out" { return Parser::make_OP_OUT(loc); }
"IN"|"in" { return Parser::make_OP_IN(loc); }

"EX"|"ex" { return Parser::make_OP_EX(loc); }
"EXX"|"exx" { return Parser::make_OP_EXX(loc); }

"(BC)"|"(bc)" { return Parser::make_RDP_BC(loc); }
"(DE)"|"(de)" { return Parser::make_RDP_DE(loc); }
"(SP)"|"(sp)" { return Parser::make_RDP_SP(loc); }

"BC"|"bc" { return Parser::make_RD_BC(0, loc); }
"DE"|"de" { return Parser::make_RD_DE(1, loc); }
"HL"|"hl" { return Parser::make_RD_HL(2, loc); }
"SP"|"sp" { return Parser::make_RD_SP(3, loc); }
"AF"|"af" { return Parser::make_RD_AF(3, loc); }

"B"|"b" { return Parser::make_RS_B(0, loc); }
"C"|"c" { return Parser::make_RS_C(1, loc); }
"D"|"d" { return Parser::make_RS_D(2, loc); }
"E"|"e" { return Parser::make_RS_E(3, loc); }
"H"|"h" { return Parser::make_RS_H(4, loc); }
"L"|"l" { return Parser::make_RS_L(5, loc); }
"(HL)"|"(hl)" { return Parser::make_RS_HL(6, loc); }
"A"|"a" { return Parser::make_RS_A(7, loc); }

"(" { return Parser::make_T_LPAREN(loc); }
")" { return Parser::make_T_RPAREN(loc); }

"0x"[a-fA-F0-9]+ { return Parser::make_U16(strtol( &yytext[2], NULL, 16), loc); }
[a-fA-F0-9]+"H" { return Parser::make_U16(strtol( yytext, NULL, 16), loc); }
[a-fA-F0-9]+"h" { return Parser::make_U16(strtol( yytext, NULL, 16), loc); }
"0b"[0-1]+ { return Parser::make_U16(strtol( &yytext[2], NULL, 2), loc); }
[0-1]+"B" { return Parser::make_U16(strtol( yytext, NULL, 2), loc); }
[0-1]+"b" { return Parser::make_U16(strtol( yytext, NULL, 2), loc); }
[-]?[0-9]+ { return Parser::make_U16(atoi(yytext), loc);}

[0-9]+\.[0-9]*"f"? { return Parser::make_FLOAT(atof(yytext), loc); }

<INITIAL>[\"'] { buffer.clear(); BEGIN(sstring); }

<sstring>[\"'] { BEGIN(INITIAL); return Parser::make_LITERAL(buffer.c_str(), loc); }
<sstring>\\n { buffer += '\n'; }
<sstring>\\0 { buffer += '\0'; }
<sstring>\\(.|\n) { buffer += yytext[1]; }
<sstring>[^\\\n\"']+ { char *ptr = yytext; while (*ptr) buffer += *ptr++; }
[a-zA-Z_][a-zA-Z0-9_]* { return Parser::make_IDENTIFIER(yytext,loc); }

"#"[^\n]*\n { loc.lines(1); return Parser::make_EOL(loc); }


\n|"\r\n" { loc.lines((int)yyleng); return Parser::make_EOL(loc); }
[ \t] { /* ignore whitespace */ }
. { assembler.error(loc, "Unrecognized character."); }

<<EOF>> { return yyterminate(); }


%%

