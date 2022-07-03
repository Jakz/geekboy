// A Bison parser, made by GNU Bison 3.7.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

// "%code top" blocks.
#line 40 "src/assembler/gbparser.ypp"

  #include "assembler.h"
  #include "gblexer.h"
  #include "gbparser.hpp"
  #include "../opcodes.h"
  #include "../utils.h"
  
  static assembler::Parser::symbol_type yylex(assembler::Lexer &scanner, assembler::Assembler &assembler) {
    return scanner.get_next_token();
  }

  using namespace assembler;

#line 53 "src/assembler/gbparser.cpp"




#include "gbparser.hpp"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "src/assembler/gbparser.ypp"
namespace assembler {
#line 153 "src/assembler/gbparser.cpp"

  /// Build a parser object.
  Parser::Parser (assembler::Lexer &lexer_yyarg, assembler::Assembler &assembler_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      lexer (lexer_yyarg),
      assembler (assembler_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_FLOAT: // FLOAT
        value.YY_MOVE_OR_COPY< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LITERAL: // LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U16: // U16
      case symbol_kind::S_RS_B: // RS_B
      case symbol_kind::S_RS_C: // RS_C
      case symbol_kind::S_RS_D: // RS_D
      case symbol_kind::S_RS_E: // RS_E
      case symbol_kind::S_RS_H: // RS_H
      case symbol_kind::S_RS_L: // RS_L
      case symbol_kind::S_RS_HL: // RS_HL
      case symbol_kind::S_RS_A: // RS_A
      case symbol_kind::S_RD_BC: // RD_BC
      case symbol_kind::S_RD_DE: // RD_DE
      case symbol_kind::S_RD_HL: // RD_HL
      case symbol_kind::S_RD_SP: // RD_SP
      case symbol_kind::S_RD_AF: // RD_AF
      case symbol_kind::S_CC_COND: // CC_COND
      case symbol_kind::S_instruction: // instruction
      case symbol_kind::S_sreg: // sreg
      case symbol_kind::S_dreg: // dreg
      case symbol_kind::S_dregaf: // dregaf
      case symbol_kind::S_snum: // snum
      case symbol_kind::S_pnum: // pnum
        value.YY_MOVE_OR_COPY< u16 > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_FLOAT: // FLOAT
        value.move< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LITERAL: // LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.move< std::string > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_U16: // U16
      case symbol_kind::S_RS_B: // RS_B
      case symbol_kind::S_RS_C: // RS_C
      case symbol_kind::S_RS_D: // RS_D
      case symbol_kind::S_RS_E: // RS_E
      case symbol_kind::S_RS_H: // RS_H
      case symbol_kind::S_RS_L: // RS_L
      case symbol_kind::S_RS_HL: // RS_HL
      case symbol_kind::S_RS_A: // RS_A
      case symbol_kind::S_RD_BC: // RD_BC
      case symbol_kind::S_RD_DE: // RD_DE
      case symbol_kind::S_RD_HL: // RD_HL
      case symbol_kind::S_RD_SP: // RD_SP
      case symbol_kind::S_RD_AF: // RD_AF
      case symbol_kind::S_CC_COND: // CC_COND
      case symbol_kind::S_instruction: // instruction
      case symbol_kind::S_sreg: // sreg
      case symbol_kind::S_dreg: // dreg
      case symbol_kind::S_dregaf: // dregaf
      case symbol_kind::S_snum: // snum
      case symbol_kind::S_pnum: // pnum
        value.move< u16 > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_FLOAT: // FLOAT
        value.copy< float > (that.value);
        break;

      case symbol_kind::S_LITERAL: // LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.copy< std::string > (that.value);
        break;

      case symbol_kind::S_U16: // U16
      case symbol_kind::S_RS_B: // RS_B
      case symbol_kind::S_RS_C: // RS_C
      case symbol_kind::S_RS_D: // RS_D
      case symbol_kind::S_RS_E: // RS_E
      case symbol_kind::S_RS_H: // RS_H
      case symbol_kind::S_RS_L: // RS_L
      case symbol_kind::S_RS_HL: // RS_HL
      case symbol_kind::S_RS_A: // RS_A
      case symbol_kind::S_RD_BC: // RD_BC
      case symbol_kind::S_RD_DE: // RD_DE
      case symbol_kind::S_RD_HL: // RD_HL
      case symbol_kind::S_RD_SP: // RD_SP
      case symbol_kind::S_RD_AF: // RD_AF
      case symbol_kind::S_CC_COND: // CC_COND
      case symbol_kind::S_instruction: // instruction
      case symbol_kind::S_sreg: // sreg
      case symbol_kind::S_dreg: // dreg
      case symbol_kind::S_dregaf: // dregaf
      case symbol_kind::S_snum: // snum
      case symbol_kind::S_pnum: // pnum
        value.copy< u16 > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_FLOAT: // FLOAT
        value.move< float > (that.value);
        break;

      case symbol_kind::S_LITERAL: // LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.move< std::string > (that.value);
        break;

      case symbol_kind::S_U16: // U16
      case symbol_kind::S_RS_B: // RS_B
      case symbol_kind::S_RS_C: // RS_C
      case symbol_kind::S_RS_D: // RS_D
      case symbol_kind::S_RS_E: // RS_E
      case symbol_kind::S_RS_H: // RS_H
      case symbol_kind::S_RS_L: // RS_L
      case symbol_kind::S_RS_HL: // RS_HL
      case symbol_kind::S_RS_A: // RS_A
      case symbol_kind::S_RD_BC: // RD_BC
      case symbol_kind::S_RD_DE: // RD_DE
      case symbol_kind::S_RD_HL: // RD_HL
      case symbol_kind::S_RD_SP: // RD_SP
      case symbol_kind::S_RD_AF: // RD_AF
      case symbol_kind::S_CC_COND: // CC_COND
      case symbol_kind::S_instruction: // instruction
      case symbol_kind::S_sreg: // sreg
      case symbol_kind::S_dreg: // dreg
      case symbol_kind::S_dregaf: // dregaf
      case symbol_kind::S_snum: // snum
      case symbol_kind::S_pnum: // pnum
        value.move< u16 > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        YYUSE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    // User initialization code.
#line 32 "src/assembler/gbparser.ypp"
{
  yyla.location.begin.filename = yyla.location.end.filename = &assembler.file;
}

#line 551 "src/assembler/gbparser.cpp"


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (lexer, assembler));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_FLOAT: // FLOAT
        yylhs.value.emplace< float > ();
        break;

      case symbol_kind::S_LITERAL: // LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        yylhs.value.emplace< std::string > ();
        break;

      case symbol_kind::S_U16: // U16
      case symbol_kind::S_RS_B: // RS_B
      case symbol_kind::S_RS_C: // RS_C
      case symbol_kind::S_RS_D: // RS_D
      case symbol_kind::S_RS_E: // RS_E
      case symbol_kind::S_RS_H: // RS_H
      case symbol_kind::S_RS_L: // RS_L
      case symbol_kind::S_RS_HL: // RS_HL
      case symbol_kind::S_RS_A: // RS_A
      case symbol_kind::S_RD_BC: // RD_BC
      case symbol_kind::S_RD_DE: // RD_DE
      case symbol_kind::S_RD_HL: // RD_HL
      case symbol_kind::S_RD_SP: // RD_SP
      case symbol_kind::S_RD_AF: // RD_AF
      case symbol_kind::S_CC_COND: // CC_COND
      case symbol_kind::S_instruction: // instruction
      case symbol_kind::S_sreg: // sreg
      case symbol_kind::S_dreg: // dreg
      case symbol_kind::S_dregaf: // dregaf
      case symbol_kind::S_snum: // snum
      case symbol_kind::S_pnum: // pnum
        yylhs.value.emplace< u16 > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // $@1: %empty
#line 106 "src/assembler/gbparser.ypp"
  { assembler.init(8192); }
#line 722 "src/assembler/gbparser.cpp"
    break;

  case 3: // start: $@1 instructions
#line 106 "src/assembler/gbparser.ypp"
                                         { }
#line 728 "src/assembler/gbparser.cpp"
    break;

  case 5: // instructions: instructions instruction
#line 110 "src/assembler/gbparser.ypp"
                             { }
#line 734 "src/assembler/gbparser.cpp"
    break;

  case 6: // instructions: instructions "\n"
#line 111 "src/assembler/gbparser.ypp"
                     { }
#line 740 "src/assembler/gbparser.cpp"
    break;

  case 7: // instruction: OP_NOP
#line 116 "src/assembler/gbparser.ypp"
         { assembler.assemble(OPCODE_NOP); }
#line 746 "src/assembler/gbparser.cpp"
    break;

  case 8: // instruction: OP_STOP
#line 117 "src/assembler/gbparser.ypp"
            { assembler.assemble(OPCODE_DJNZ_N); }
#line 752 "src/assembler/gbparser.cpp"
    break;

  case 9: // instruction: OP_LD sreg T_COMMA sreg
#line 120 "src/assembler/gbparser.ypp"
                            { assembler.assemble(OPCODE_LD_R_R | (yystack_[2].value.as < u16 > () << 3) | (yystack_[0].value.as < u16 > ())); }
#line 758 "src/assembler/gbparser.cpp"
    break;

  case 10: // instruction: OP_LD sreg T_COMMA snum
#line 121 "src/assembler/gbparser.ypp"
                            { assembler.assemble(OPCODE_LD_R_N | (yystack_[2].value.as < u16 > () << 3), (u8)yystack_[0].value.as < u16 > ()); }
#line 764 "src/assembler/gbparser.cpp"
    break;

  case 11: // instruction: OP_LD dreg T_COMMA snum
#line 122 "src/assembler/gbparser.ypp"
                            { assembler.assemble(OPCODE_LD_RR_NN | (yystack_[2].value.as < u16 > () << 4), (u8)(yystack_[0].value.as < u16 > () & 0xFF), (u8)((yystack_[0].value.as < u16 > () >> 8) & 0xFF) ); }
#line 770 "src/assembler/gbparser.cpp"
    break;

  case 12: // instruction: OP_LD RDP_BC T_COMMA RS_A
#line 124 "src/assembler/gbparser.ypp"
                              { assembler.assemble(OPCODE_LD_BC_A); }
#line 776 "src/assembler/gbparser.cpp"
    break;

  case 13: // instruction: OP_LD RDP_DE T_COMMA RS_A
#line 125 "src/assembler/gbparser.ypp"
                              { assembler.assemble(OPCODE_LD_DE_A); }
#line 782 "src/assembler/gbparser.cpp"
    break;

  case 14: // instruction: OP_LD sreg T_COMMA RDP_BC
#line 126 "src/assembler/gbparser.ypp"
                              { assembler.aassert(yystack_[2].value.as < u16 > () == 7, "LD A, (BC) requires A reg!"); assembler.assemble(OPCODE_LD_A_BC); }
#line 788 "src/assembler/gbparser.cpp"
    break;

  case 15: // instruction: OP_LD sreg T_COMMA RDP_DE
#line 127 "src/assembler/gbparser.ypp"
                              { assembler.aassert(yystack_[2].value.as < u16 > () == 7, "LD A, (DE) requires A reg!"); assembler.assemble(OPCODE_LD_A_DE); }
#line 794 "src/assembler/gbparser.cpp"
    break;

  case 16: // instruction: OP_LD dreg T_COMMA RD_HL
#line 128 "src/assembler/gbparser.ypp"
                             { assembler.assemble(OPCODE_LD_SP_HL); }
#line 800 "src/assembler/gbparser.cpp"
    break;

  case 17: // instruction: OP_LD T_LPAREN snum T_RPAREN T_COMMA RS_A
#line 129 "src/assembler/gbparser.ypp"
                                              { assembler.assemble(OPCODE_LD_NN_A, (u8)(yystack_[3].value.as < u16 > () & 0xFF), (u8)((yystack_[3].value.as < u16 > () >> 8) & 0xFF)); }
#line 806 "src/assembler/gbparser.cpp"
    break;

  case 18: // instruction: OP_LD sreg T_COMMA pnum
#line 130 "src/assembler/gbparser.ypp"
                            { assembler.aassert(yystack_[2].value.as < u16 > () == 7, "LD A, (nn) requires A reg!"); assembler.assemble(OPCODE_LD_A_NN, (u8)(yystack_[0].value.as < u16 > () & 0xFF), (u8)((yystack_[0].value.as < u16 > () >> 8) & 0xFF)); }
#line 812 "src/assembler/gbparser.cpp"
    break;

  case 19: // instruction: OP_LD dreg T_COMMA pnum
#line 132 "src/assembler/gbparser.ypp"
                            { assembler.assemble(OPCODE_LD_HL_NN, (u8)(yystack_[0].value.as < u16 > () & 0xFF), (u8)((yystack_[0].value.as < u16 > () >> 8) & 0xFF)); }
#line 818 "src/assembler/gbparser.cpp"
    break;

  case 20: // instruction: OP_LD T_LPAREN snum T_RPAREN T_COMMA RD_HL
#line 133 "src/assembler/gbparser.ypp"
                                               { assembler.assemble(OPCODE_LD_NN_HL, (u8)(yystack_[3].value.as < u16 > () & 0xFF), (u8)((yystack_[3].value.as < u16 > () >> 8) & 0xFF)); }
#line 824 "src/assembler/gbparser.cpp"
    break;

  case 21: // instruction: OP_LDI RS_HL T_COMMA RS_A
#line 135 "src/assembler/gbparser.ypp"
                              { assembler.assemble(OPCODE_LD_NN_HL); }
#line 830 "src/assembler/gbparser.cpp"
    break;

  case 22: // instruction: OP_LDI RS_A T_COMMA RS_HL
#line 136 "src/assembler/gbparser.ypp"
                              { assembler.assemble(OPCODE_LD_HL_NN); }
#line 836 "src/assembler/gbparser.cpp"
    break;

  case 23: // instruction: OP_LDD RS_HL T_COMMA RS_A
#line 137 "src/assembler/gbparser.ypp"
                              { assembler.assemble(OPCODE_LD_NN_A); }
#line 842 "src/assembler/gbparser.cpp"
    break;

  case 24: // instruction: OP_LDD RS_A T_COMMA RS_HL
#line 138 "src/assembler/gbparser.ypp"
                              { assembler.assemble(OPCODE_LD_A_NN); }
#line 848 "src/assembler/gbparser.cpp"
    break;

  case 25: // instruction: OP_LD T_LPAREN snum T_RPAREN T_COMMA RD_SP
#line 140 "src/assembler/gbparser.ypp"
                                               { assembler.assemble(OPCODE_EX_AF_AF, (u8)(yystack_[3].value.as < u16 > () & 0xFF), (u8)((yystack_[3].value.as < u16 > () >> 8) & 0xFF)); }
#line 854 "src/assembler/gbparser.cpp"
    break;

  case 26: // instruction: OP_ADD sreg
#line 142 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_ADD_R | yystack_[0].value.as < u16 > ()); }
#line 860 "src/assembler/gbparser.cpp"
    break;

  case 27: // instruction: OP_ADC sreg
#line 143 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_ADC_R | yystack_[0].value.as < u16 > ()); }
#line 866 "src/assembler/gbparser.cpp"
    break;

  case 28: // instruction: OP_SUB sreg
#line 144 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_SUB_R | yystack_[0].value.as < u16 > ()); }
#line 872 "src/assembler/gbparser.cpp"
    break;

  case 29: // instruction: OP_SBC sreg
#line 145 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_SBC_R | yystack_[0].value.as < u16 > ()); }
#line 878 "src/assembler/gbparser.cpp"
    break;

  case 30: // instruction: OP_DAA
#line 146 "src/assembler/gbparser.ypp"
           { assembler.assemble(OPCODE_DAA); }
#line 884 "src/assembler/gbparser.cpp"
    break;

  case 31: // instruction: OP_AND sreg
#line 148 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_AND_R | yystack_[0].value.as < u16 > ()); }
#line 890 "src/assembler/gbparser.cpp"
    break;

  case 32: // instruction: OP_XOR sreg
#line 149 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_XOR_R | yystack_[0].value.as < u16 > ()); }
#line 896 "src/assembler/gbparser.cpp"
    break;

  case 33: // instruction: OP_OR sreg
#line 150 "src/assembler/gbparser.ypp"
               { assembler.assemble(OPCODE_OR_R | yystack_[0].value.as < u16 > ()); }
#line 902 "src/assembler/gbparser.cpp"
    break;

  case 34: // instruction: OP_CP sreg
#line 151 "src/assembler/gbparser.ypp"
               { assembler.assemble(OPCODE_CP_R | yystack_[0].value.as < u16 > ()); }
#line 908 "src/assembler/gbparser.cpp"
    break;

  case 35: // instruction: OP_ADD snum
#line 153 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_ADD_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 914 "src/assembler/gbparser.cpp"
    break;

  case 36: // instruction: OP_ADC snum
#line 154 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_ADC_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 920 "src/assembler/gbparser.cpp"
    break;

  case 37: // instruction: OP_SUB snum
#line 155 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_SUB_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 926 "src/assembler/gbparser.cpp"
    break;

  case 38: // instruction: OP_SBC snum
#line 156 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_SBC_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 932 "src/assembler/gbparser.cpp"
    break;

  case 39: // instruction: OP_AND snum
#line 158 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_AND_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 938 "src/assembler/gbparser.cpp"
    break;

  case 40: // instruction: OP_XOR snum
#line 159 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_XOR_N | (u8)yystack_[0].value.as < u16 > ()); }
#line 944 "src/assembler/gbparser.cpp"
    break;

  case 41: // instruction: OP_OR snum
#line 160 "src/assembler/gbparser.ypp"
               { assembler.assemble(OPCODE_OR_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 950 "src/assembler/gbparser.cpp"
    break;

  case 42: // instruction: OP_CP snum
#line 161 "src/assembler/gbparser.ypp"
               { assembler.assemble(OPCODE_CP_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 956 "src/assembler/gbparser.cpp"
    break;

  case 43: // instruction: OP_RLCA
#line 163 "src/assembler/gbparser.ypp"
            { assembler.assemble(OPCODE_RLCA); }
#line 962 "src/assembler/gbparser.cpp"
    break;

  case 44: // instruction: OP_RLA
#line 164 "src/assembler/gbparser.ypp"
           { assembler.assemble(OPCODE_RLA); }
#line 968 "src/assembler/gbparser.cpp"
    break;

  case 45: // instruction: OP_RRCA
#line 165 "src/assembler/gbparser.ypp"
            { assembler.assemble(OPCODE_RRCA); }
#line 974 "src/assembler/gbparser.cpp"
    break;

  case 46: // instruction: OP_RRA
#line 166 "src/assembler/gbparser.ypp"
           { assembler.assemble(OPCODE_RRA); }
#line 980 "src/assembler/gbparser.cpp"
    break;

  case 47: // instruction: OP_RLC sreg
#line 168 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_BITS, OPCODE_RLC | yystack_[0].value.as < u16 > ()); }
#line 986 "src/assembler/gbparser.cpp"
    break;

  case 48: // instruction: OP_RL sreg
#line 169 "src/assembler/gbparser.ypp"
               { assembler.assemble(OPCODE_BITS, OPCODE_RL | yystack_[0].value.as < u16 > ()); }
#line 992 "src/assembler/gbparser.cpp"
    break;

  case 49: // instruction: OP_RRC sreg
#line 170 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_BITS, OPCODE_RRC | yystack_[0].value.as < u16 > ()); }
#line 998 "src/assembler/gbparser.cpp"
    break;

  case 50: // instruction: OP_RR sreg
#line 171 "src/assembler/gbparser.ypp"
               { assembler.assemble(OPCODE_BITS, OPCODE_RR | yystack_[0].value.as < u16 > ()); }
#line 1004 "src/assembler/gbparser.cpp"
    break;

  case 51: // instruction: OP_SLA sreg
#line 172 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_BITS, OPCODE_SLA | yystack_[0].value.as < u16 > ()); }
#line 1010 "src/assembler/gbparser.cpp"
    break;

  case 52: // instruction: OP_SRA sreg
#line 173 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_BITS, OPCODE_SRA | yystack_[0].value.as < u16 > ()); }
#line 1016 "src/assembler/gbparser.cpp"
    break;

  case 53: // instruction: OP_SLL sreg
#line 174 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_BITS, OPCODE_SLL | yystack_[0].value.as < u16 > ()); }
#line 1022 "src/assembler/gbparser.cpp"
    break;

  case 54: // instruction: OP_SRL sreg
#line 175 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_BITS, OPCODE_SRL | yystack_[0].value.as < u16 > ()); }
#line 1028 "src/assembler/gbparser.cpp"
    break;

  case 55: // instruction: OP_SWAP sreg
#line 176 "src/assembler/gbparser.ypp"
                 { assembler.assemble(OPCODE_BITS, OPCODE_SLL | yystack_[0].value.as < u16 > ()); }
#line 1034 "src/assembler/gbparser.cpp"
    break;

  case 56: // instruction: OP_BIT snum T_COMMA sreg
#line 178 "src/assembler/gbparser.ypp"
                             { assembler.aassert(yystack_[2].value.as < u16 > () <= 7, "BIT specifier over bounds!"); assembler.assemble(OPCODE_BITS, OPCODE_BIT | (yystack_[2].value.as < u16 > () << 3) | yystack_[0].value.as < u16 > ()); }
#line 1040 "src/assembler/gbparser.cpp"
    break;

  case 57: // instruction: OP_RES snum T_COMMA sreg
#line 179 "src/assembler/gbparser.ypp"
                             { assembler.aassert(yystack_[2].value.as < u16 > () <= 7, "RES specifier over bounds!"); assembler.assemble(OPCODE_BITS, OPCODE_RES | (yystack_[2].value.as < u16 > () << 3) | yystack_[0].value.as < u16 > ()); }
#line 1046 "src/assembler/gbparser.cpp"
    break;

  case 58: // instruction: OP_SET snum T_COMMA sreg
#line 180 "src/assembler/gbparser.ypp"
                             { assembler.aassert(yystack_[2].value.as < u16 > () <= 7, "SET specifier over bounds!"); assembler.assemble(OPCODE_BITS, OPCODE_SET | (yystack_[2].value.as < u16 > () << 3) | yystack_[0].value.as < u16 > ()); }
#line 1052 "src/assembler/gbparser.cpp"
    break;

  case 59: // instruction: OP_CPL
#line 182 "src/assembler/gbparser.ypp"
           { assembler.assemble(OPCODE_CPL); }
#line 1058 "src/assembler/gbparser.cpp"
    break;

  case 60: // instruction: OP_SCF
#line 183 "src/assembler/gbparser.ypp"
           { assembler.assemble(OPCODE_SCF); }
#line 1064 "src/assembler/gbparser.cpp"
    break;

  case 61: // instruction: OP_CCF
#line 184 "src/assembler/gbparser.ypp"
           { assembler.assemble(OPCODE_CCF); }
#line 1070 "src/assembler/gbparser.cpp"
    break;

  case 62: // instruction: OP_ADD RD_HL T_COMMA dreg
#line 186 "src/assembler/gbparser.ypp"
                              { assembler.assemble(OPCODE_ADD_HL_RR | yystack_[0].value.as < u16 > () << 4); }
#line 1076 "src/assembler/gbparser.cpp"
    break;

  case 63: // instruction: OP_DJNZ snum
#line 188 "src/assembler/gbparser.ypp"
                 { assembler.assemble(OPCODE_DJNZ_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 1082 "src/assembler/gbparser.cpp"
    break;

  case 64: // instruction: OP_JR snum
#line 189 "src/assembler/gbparser.ypp"
               { assembler.assemble(OPCODE_JR_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 1088 "src/assembler/gbparser.cpp"
    break;

  case 65: // instruction: OP_JRNZ snum
#line 190 "src/assembler/gbparser.ypp"
                 { assembler.assemble(OPCODE_JRNZ_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 1094 "src/assembler/gbparser.cpp"
    break;

  case 66: // instruction: OP_JRZ snum
#line 191 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_JRZ_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 1100 "src/assembler/gbparser.cpp"
    break;

  case 67: // instruction: OP_JRNC snum
#line 192 "src/assembler/gbparser.ypp"
                 { assembler.assemble(OPCODE_JRNC_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 1106 "src/assembler/gbparser.cpp"
    break;

  case 68: // instruction: OP_JRC snum
#line 193 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_JRC_N, (u8)yystack_[0].value.as < u16 > ()); }
#line 1112 "src/assembler/gbparser.cpp"
    break;

  case 69: // instruction: OP_JP snum
#line 195 "src/assembler/gbparser.ypp"
               { assembler.assemble(OPCODE_JP_NN, (u8)(yystack_[0].value.as < u16 > () & 0xFF), (u8)((yystack_[0].value.as < u16 > () >> 8) & 0xFF)); }
#line 1118 "src/assembler/gbparser.cpp"
    break;

  case 70: // instruction: OP_JP CC_COND snum
#line 196 "src/assembler/gbparser.ypp"
                       { assembler.assemble(OPCODE_JP_CC_NN | (yystack_[1].value.as < u16 > () << 3), (u8)(yystack_[0].value.as < u16 > () & 0xFF), (u8)((yystack_[0].value.as < u16 > () >> 8) & 0xFF)); }
#line 1124 "src/assembler/gbparser.cpp"
    break;

  case 71: // instruction: OP_JP RS_HL
#line 197 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_JP_HL); }
#line 1130 "src/assembler/gbparser.cpp"
    break;

  case 72: // instruction: OP_CALL snum
#line 199 "src/assembler/gbparser.ypp"
                 { assembler.assemble(OPCODE_CALL_NN, (u8)(yystack_[0].value.as < u16 > () & 0xFF), (u8)((yystack_[0].value.as < u16 > () >> 8) & 0xFF)); }
#line 1136 "src/assembler/gbparser.cpp"
    break;

  case 73: // instruction: OP_CALL CC_COND snum
#line 200 "src/assembler/gbparser.ypp"
                         { assembler.assemble(OPCODE_CALL_CC_NN | (yystack_[1].value.as < u16 > () << 3), (u8)(yystack_[0].value.as < u16 > () & 0xFF), (u8)((yystack_[0].value.as < u16 > () >> 8) & 0xFF)); }
#line 1142 "src/assembler/gbparser.cpp"
    break;

  case 74: // instruction: OP_RST snum
#line 202 "src/assembler/gbparser.ypp"
                { assembler.aassert(assembler.correctRSTAddress(yystack_[0].value.as < u16 > ()), "RST Address over bounds!"); assembler.assemble(OPCODE_RST | ((yystack_[0].value.as < u16 > ()/8) << 3)); }
#line 1148 "src/assembler/gbparser.cpp"
    break;

  case 75: // instruction: OP_RET
#line 204 "src/assembler/gbparser.ypp"
           { assembler.assemble(OPCODE_RET); }
#line 1154 "src/assembler/gbparser.cpp"
    break;

  case 76: // instruction: OP_RET CC_COND
#line 205 "src/assembler/gbparser.ypp"
                   { assembler.assemble(OPCODE_RET_CC | (yystack_[0].value.as < u16 > () << 3)); }
#line 1160 "src/assembler/gbparser.cpp"
    break;

  case 77: // instruction: OP_RETI
#line 206 "src/assembler/gbparser.ypp"
            { assembler.assemble(OPCODE_EXX); }
#line 1166 "src/assembler/gbparser.cpp"
    break;

  case 78: // instruction: OP_PUSH dregaf
#line 208 "src/assembler/gbparser.ypp"
                   { assembler.assemble(OPCODE_PUSH | (yystack_[0].value.as < u16 > () << 4)); }
#line 1172 "src/assembler/gbparser.cpp"
    break;

  case 79: // instruction: OP_POP dregaf
#line 209 "src/assembler/gbparser.ypp"
                  { assembler.assemble(OPCODE_POP | (yystack_[0].value.as < u16 > () << 4)); }
#line 1178 "src/assembler/gbparser.cpp"
    break;

  case 80: // instruction: OP_EI
#line 211 "src/assembler/gbparser.ypp"
          { assembler.assemble(OPCODE_EI); }
#line 1184 "src/assembler/gbparser.cpp"
    break;

  case 81: // instruction: OP_DI
#line 212 "src/assembler/gbparser.ypp"
          { assembler.assemble(OPCODE_DI); }
#line 1190 "src/assembler/gbparser.cpp"
    break;

  case 82: // instruction: OP_INC sreg
#line 214 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_INC_R | (yystack_[0].value.as < u16 > () << 3)); }
#line 1196 "src/assembler/gbparser.cpp"
    break;

  case 83: // instruction: OP_DEC sreg
#line 215 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_DEC_R | (yystack_[0].value.as < u16 > () << 3)); }
#line 1202 "src/assembler/gbparser.cpp"
    break;

  case 84: // instruction: OP_INC dreg
#line 217 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_INC_RR | (yystack_[0].value.as < u16 > () << 4)); }
#line 1208 "src/assembler/gbparser.cpp"
    break;

  case 85: // instruction: OP_DEC dreg
#line 218 "src/assembler/gbparser.ypp"
                { assembler.assemble(OPCODE_DEC_RR | (yystack_[0].value.as < u16 > () << 4)); }
#line 1214 "src/assembler/gbparser.cpp"
    break;

  case 86: // instruction: OP_OUT snum T_COMMA RS_A
#line 220 "src/assembler/gbparser.ypp"
                             { assembler.assemble(OPCODE_OUT_N_A, yystack_[2].value.as < u16 > ()); }
#line 1220 "src/assembler/gbparser.cpp"
    break;

  case 87: // instruction: OP_IN RS_A T_COMMA snum
#line 221 "src/assembler/gbparser.ypp"
                            { assembler.assemble(OPCODE_IN_N_A, yystack_[0].value.as < u16 > ()); }
#line 1226 "src/assembler/gbparser.cpp"
    break;

  case 88: // instruction: OP_EX RD_AF T_COMMA RD_AF T_QUOTE
#line 223 "src/assembler/gbparser.ypp"
                                      { assembler.assemble(OPCODE_EX_AF_AF); }
#line 1232 "src/assembler/gbparser.cpp"
    break;

  case 89: // instruction: OP_EXX
#line 224 "src/assembler/gbparser.ypp"
           { assembler.assemble(OPCODE_EXX); }
#line 1238 "src/assembler/gbparser.cpp"
    break;

  case 90: // instruction: OP_EX RDP_SP T_COMMA RD_HL
#line 225 "src/assembler/gbparser.ypp"
                               { assembler.assemble(OPCODE_EX_SP_HL); }
#line 1244 "src/assembler/gbparser.cpp"
    break;

  case 91: // instruction: OP_EX RD_DE T_COMMA RD_HL
#line 226 "src/assembler/gbparser.ypp"
                              { assembler.assemble(OPCODE_EX_DE_HL); }
#line 1250 "src/assembler/gbparser.cpp"
    break;

  case 92: // instruction: OP_HALT
#line 228 "src/assembler/gbparser.ypp"
            { assembler.assemble(OPCODE_HALT); }
#line 1256 "src/assembler/gbparser.cpp"
    break;

  case 93: // sreg: RS_B
#line 236 "src/assembler/gbparser.ypp"
       { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1262 "src/assembler/gbparser.cpp"
    break;

  case 94: // sreg: RS_C
#line 237 "src/assembler/gbparser.ypp"
       { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1268 "src/assembler/gbparser.cpp"
    break;

  case 95: // sreg: RS_D
#line 238 "src/assembler/gbparser.ypp"
       { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1274 "src/assembler/gbparser.cpp"
    break;

  case 96: // sreg: RS_E
#line 239 "src/assembler/gbparser.ypp"
       { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1280 "src/assembler/gbparser.cpp"
    break;

  case 97: // sreg: RS_H
#line 240 "src/assembler/gbparser.ypp"
       { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1286 "src/assembler/gbparser.cpp"
    break;

  case 98: // sreg: RS_L
#line 241 "src/assembler/gbparser.ypp"
       { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1292 "src/assembler/gbparser.cpp"
    break;

  case 99: // sreg: RS_HL
#line 242 "src/assembler/gbparser.ypp"
        { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1298 "src/assembler/gbparser.cpp"
    break;

  case 100: // sreg: RS_A
#line 243 "src/assembler/gbparser.ypp"
       { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1304 "src/assembler/gbparser.cpp"
    break;

  case 101: // dreg: RD_BC
#line 247 "src/assembler/gbparser.ypp"
        { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1310 "src/assembler/gbparser.cpp"
    break;

  case 102: // dreg: RD_DE
#line 248 "src/assembler/gbparser.ypp"
        { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1316 "src/assembler/gbparser.cpp"
    break;

  case 103: // dreg: RD_HL
#line 249 "src/assembler/gbparser.ypp"
        { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1322 "src/assembler/gbparser.cpp"
    break;

  case 104: // dreg: RD_SP
#line 250 "src/assembler/gbparser.ypp"
        { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1328 "src/assembler/gbparser.cpp"
    break;

  case 105: // dregaf: RD_BC
#line 254 "src/assembler/gbparser.ypp"
        { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1334 "src/assembler/gbparser.cpp"
    break;

  case 106: // dregaf: RD_DE
#line 255 "src/assembler/gbparser.ypp"
        { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1340 "src/assembler/gbparser.cpp"
    break;

  case 107: // dregaf: RD_HL
#line 256 "src/assembler/gbparser.ypp"
        { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1346 "src/assembler/gbparser.cpp"
    break;

  case 108: // dregaf: RD_AF
#line 257 "src/assembler/gbparser.ypp"
        { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1352 "src/assembler/gbparser.cpp"
    break;

  case 109: // snum: U16
#line 261 "src/assembler/gbparser.ypp"
      { yylhs.value.as < u16 > () = yystack_[0].value.as < u16 > (); }
#line 1358 "src/assembler/gbparser.cpp"
    break;

  case 110: // pnum: T_LPAREN U16 T_RPAREN
#line 265 "src/assembler/gbparser.ypp"
                        { yylhs.value.as < u16 > () = yystack_[1].value.as < u16 > (); }
#line 1364 "src/assembler/gbparser.cpp"
    break;


#line 1368 "src/assembler/gbparser.cpp"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }



  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -69;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -69,    13,   -69,   -69,   166,   -69,   -69,   -69,    38,   -68,
     -59,   -69,    22,   167,   167,   167,   167,   167,   167,    77,
      77,   167,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -43,   -43,   -43,   -43,   -43,   -43,   -55,   -54,   -19,   -26,
     -26,   -43,   -69,   -43,   -43,   -43,    89,    89,    89,    89,
      89,    89,    89,    89,    89,   -69,   -69,   -43,   -46,     1,
     -69,   -69,   -43,    41,    49,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,    53,    54,    59,
      62,    73,    75,   -69,    76,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -43,   -69,   -69,   -69,   -43,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,    82,    84,    95,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,    97,    99,   100,   101,
     123,   122,    55,    58,    51,     9,    60,    63,    61,    64,
       6,   -69,   -69,    89,    89,    89,    66,   -43,    56,    65,
      86,   125,   -69,   -69,    72,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,   -69,
     -69,   -69,   -69,   -69,   -69,   135,   -14,   161,   -69,   -69,
     -69,   -69,   -69
  };

  const signed char
  Parser::yydefact_[] =
  {
       2,     0,     4,     1,     3,     6,     7,     8,     0,     0,
       0,    92,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    30,    43,    44,    45,    46,    59,    61,    60,
       0,     0,     0,     0,     0,     0,     0,    75,     0,     0,
       0,     0,    77,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    80,    81,     0,     0,     0,
      89,     5,     0,     0,     0,    93,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,     0,     0,     0,
       0,     0,     0,   109,     0,    26,    35,    27,    36,    28,
      37,    29,    38,    31,    39,    32,    40,    33,    41,    82,
      84,    83,    85,    34,    42,    63,    64,    65,    66,    67,
      68,     0,    72,    76,    71,     0,    69,   105,   106,   107,
     108,    78,    79,    74,     0,     0,     0,    47,    48,    49,
      50,    51,    52,    53,    54,    55,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    73,    70,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    12,    13,     0,    14,    15,     9,    10,    18,
      16,    11,    19,    21,    22,    23,    24,    62,    56,    57,
      58,    86,    87,    90,    91,     0,     0,     0,    88,    17,
      20,    25,   110
  };

  const short
  Parser::yypgoto_[] =
  {
     -69,   -69,   -69,   -69,   -69,    21,   -10,   128,   -13,    24
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,     1,     2,     4,    61,    77,    78,   121,    86,   169
  };

  const unsigned char
  Parser::yytable_[] =
  {
      88,    90,    92,    94,    96,    98,    79,    80,   104,   100,
     102,   138,    83,     3,   164,    81,    82,   105,   106,   107,
     108,   109,   110,   112,    83,   116,   111,   113,   123,   137,
     124,   125,   126,    85,    87,    89,    91,    93,    95,    97,
      99,   101,   103,    62,   136,   142,    63,    64,    83,   141,
     117,   118,   119,   143,   120,   114,   164,   144,   145,   165,
     166,   189,   115,   146,   190,   191,   147,   127,   128,   129,
     130,   131,   132,   133,   134,   135,    83,   148,   139,   149,
     150,   140,    73,    74,    75,    76,   153,   170,   154,    83,
      65,    66,    67,    68,    69,    70,    71,    72,   151,   155,
      84,   156,   152,   157,   158,   159,    65,    66,    67,    68,
      69,    70,    71,    72,    73,    74,    75,    76,    83,    65,
      66,    67,    68,    69,    70,    71,    72,   160,   161,   186,
     162,   168,   171,   163,   183,   173,   175,   174,   176,   187,
     177,   181,   188,   184,   182,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,    65,    66,    67,
      68,    69,    70,    71,    72,   167,   185,   192,   122,   172,
       0,     0,     0,     0,   178,   179,   180,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    59,    60,     0,    83,    65,    66,    67,    68,    69,
      70,    71,    72
  };

  const short
  Parser::yycheck_[] =
  {
      13,    14,    15,    16,    17,    18,    74,    75,    21,    19,
      20,    10,    67,     0,     5,    74,    75,    30,    31,    32,
      33,    34,    35,    36,    67,    38,    81,    81,    41,    75,
      43,    44,    45,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,     5,    57,     4,     8,     9,    67,    62,
      76,    77,    78,     4,    80,    74,     5,     4,     4,     8,
       9,    75,    81,     4,    78,    79,     4,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    67,     4,    77,     4,
       4,    80,    76,    77,    78,    79,     4,    78,     4,    67,
      68,    69,    70,    71,    72,    73,    74,    75,   111,     4,
      78,     4,   115,     4,     4,     4,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    77,    78,    79,    67,    68,
      69,    70,    71,    72,    73,    74,    75,     4,     6,     4,
      75,   144,   145,    75,    78,    75,    75,    74,    74,    67,
     150,    75,     7,    78,   157,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    68,    69,    70,
      71,    72,    73,    74,    75,   144,    80,     6,    40,   145,
      -1,    -1,    -1,    -1,   153,   154,   155,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    -1,    67,    68,    69,    70,    71,    72,
      73,    74,    75
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    86,    87,     0,    88,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    89,     5,     8,     9,    68,    69,    70,    71,    72,
      73,    74,    75,    76,    77,    78,    79,    90,    91,    74,
      75,    74,    75,    67,    78,    90,    93,    90,    93,    90,
      93,    90,    93,    90,    93,    90,    93,    90,    93,    90,
      91,    90,    91,    90,    93,    93,    93,    93,    93,    93,
      93,    81,    93,    81,    74,    81,    93,    76,    77,    78,
      80,    92,    92,    93,    93,    93,    93,    90,    90,    90,
      90,    90,    90,    90,    90,    90,    93,    75,    10,    77,
      80,    93,     4,     4,     4,     4,     4,     4,     4,     4,
       4,    93,    93,     4,     4,     4,     4,     4,     4,     4,
       4,     6,    75,    75,     5,     8,     9,    90,    93,    94,
      78,    93,    94,    75,    74,    75,    74,    91,    90,    90,
      90,    75,    93,    78,    78,    80,     4,    67,     7,    75,
      78,    79,     6
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    85,    87,    86,    88,    88,    88,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    90,    90,    90,    90,    90,    90,    90,
      90,    91,    91,    91,    91,    92,    92,    92,    92,    93,
      94
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     0,     2,     0,     2,     2,     1,     1,     4,
       4,     4,     4,     4,     4,     4,     4,     6,     4,     4,
       6,     4,     4,     4,     4,     6,     2,     2,     2,     2,
       1,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     1,     1,     1,     1,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     4,     4,     4,     1,
       1,     1,     4,     2,     2,     2,     2,     2,     2,     2,
       3,     2,     2,     3,     2,     1,     2,     1,     2,     2,
       1,     1,     2,     2,     2,     2,     4,     4,     5,     1,
       4,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "T_COLON", "T_COMMA",
  "T_LPAREN", "T_RPAREN", "T_QUOTE", "RDP_BC", "RDP_DE", "RDP_SP",
  "\"\\n\"", "OP_NOP", "OP_STOP", "OP_LD", "OP_LDI", "OP_LDD", "OP_HALT",
  "OP_ADD", "OP_ADC", "OP_SUB", "OP_SBC", "OP_AND", "OP_XOR", "OP_OR",
  "OP_INC", "OP_DEC", "OP_CP", "OP_DAA", "OP_RLCA", "OP_RLA", "OP_RRCA",
  "OP_RRA", "OP_CPL", "OP_CCF", "OP_SCF", "OP_DJNZ", "OP_JR", "OP_JRNZ",
  "OP_JRZ", "OP_JRNC", "OP_JRC", "OP_CALL", "OP_RET", "OP_JP", "OP_PUSH",
  "OP_POP", "OP_RST", "OP_RETI", "OP_BIT", "OP_RES", "OP_SET", "OP_RLC",
  "OP_RL", "OP_RRC", "OP_RR", "OP_SLA", "OP_SRA", "OP_SLL", "OP_SRL",
  "OP_SWAP", "OP_EI", "OP_DI", "OP_OUT", "OP_IN", "OP_EX", "OP_EXX", "U16",
  "RS_B", "RS_C", "RS_D", "RS_E", "RS_H", "RS_L", "RS_HL", "RS_A", "RD_BC",
  "RD_DE", "RD_HL", "RD_SP", "RD_AF", "CC_COND", "FLOAT", "LITERAL",
  "IDENTIFIER", "$accept", "start", "$@1", "instructions", "instruction",
  "sreg", "dreg", "dregaf", "snum", "pnum", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   106,   106,   106,   109,   110,   111,   116,   117,   120,
     121,   122,   124,   125,   126,   127,   128,   129,   130,   132,
     133,   135,   136,   137,   138,   140,   142,   143,   144,   145,
     146,   148,   149,   150,   151,   153,   154,   155,   156,   158,
     159,   160,   161,   163,   164,   165,   166,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   178,   179,   180,   182,
     183,   184,   186,   188,   189,   190,   191,   192,   193,   195,
     196,   197,   199,   200,   202,   204,   205,   206,   208,   209,
     211,   212,   214,   215,   217,   218,   220,   221,   223,   224,
     225,   226,   228,   236,   237,   238,   239,   240,   241,   242,
     243,   247,   248,   249,   250,   254,   255,   256,   257,   261,
     265
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 5 "src/assembler/gbparser.ypp"
} // assembler
#line 1975 "src/assembler/gbparser.cpp"

#line 273 "src/assembler/gbparser.ypp"


void assembler::Parser::error(const location_type& l, const std::string& m)
{
  assembler.error(l,m);
}
