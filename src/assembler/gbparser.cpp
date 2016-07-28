// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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
// //                    "%code top" blocks.
#line 40 "src/assembler/gbparser.ypp" // lalr1.cc:397

  #include "assembler.h"
  #include "gblexer.h"
  #include "gbparser.hpp"
  #include "../opcodes.h"
  #include "../utils.h"
  
  static assembler::Parser::symbol_type yylex(assembler::Lexer &scanner, assembler::Assembler &assembler) {
    return scanner.get_next_token();
  }

  using namespace assembler;

#line 48 "src/assembler/gbparser.cpp" // lalr1.cc:397


// First part of user declarations.

#line 53 "src/assembler/gbparser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "gbparser.hpp"

// User implementation prologue.

#line 67 "src/assembler/gbparser.cpp" // lalr1.cc:412


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
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      *yycdebug_ << std::endl;                  \
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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "src/assembler/gbparser.ypp" // lalr1.cc:479
namespace assembler {
#line 153 "src/assembler/gbparser.cpp" // lalr1.cc:479

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
        std::string yyr = "";
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
              // Fall through.
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


  /// Build a parser object.
  Parser::Parser (assembler::Lexer &lexer_yyarg, assembler::Assembler &assembler_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      lexer (lexer_yyarg),
      assembler (assembler_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 82: // FLOAT
        value.move< float > (that.value);
        break;

      case 83: // LITERAL
      case 84: // IDENTIFIER
        value.move< std::string > (that.value);
        break;

      case 67: // U16
      case 68: // RS_B
      case 69: // RS_C
      case 70: // RS_D
      case 71: // RS_E
      case 72: // RS_H
      case 73: // RS_L
      case 74: // RS_HL
      case 75: // RS_A
      case 76: // RD_BC
      case 77: // RD_DE
      case 78: // RD_HL
      case 79: // RD_SP
      case 80: // RD_AF
      case 81: // CC_COND
      case 89: // instruction
      case 90: // sreg
      case 91: // dreg
      case 92: // dregaf
      case 93: // snum
      case 94: // pnum
        value.move< u16 > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 82: // FLOAT
        value.copy< float > (that.value);
        break;

      case 83: // LITERAL
      case 84: // IDENTIFIER
        value.copy< std::string > (that.value);
        break;

      case 67: // U16
      case 68: // RS_B
      case 69: // RS_C
      case 70: // RS_D
      case 71: // RS_E
      case 72: // RS_H
      case 73: // RS_L
      case 74: // RS_HL
      case 75: // RS_A
      case 76: // RD_BC
      case 77: // RD_DE
      case 78: // RD_HL
      case 79: // RD_SP
      case 80: // RD_AF
      case 81: // CC_COND
      case 89: // instruction
      case 90: // sreg
      case 91: // dreg
      case 92: // dregaf
      case 93: // snum
      case 94: // pnum
        value.copy< u16 > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
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

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    // User initialization code.
    #line 32 "src/assembler/gbparser.ypp" // lalr1.cc:745
{
  yyla.location.begin.filename = yyla.location.end.filename = &assembler.file;
}

#line 493 "src/assembler/gbparser.cpp" // lalr1.cc:745

    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (lexer, assembler));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 82: // FLOAT
        yylhs.value.build< float > ();
        break;

      case 83: // LITERAL
      case 84: // IDENTIFIER
        yylhs.value.build< std::string > ();
        break;

      case 67: // U16
      case 68: // RS_B
      case 69: // RS_C
      case 70: // RS_D
      case 71: // RS_E
      case 72: // RS_H
      case 73: // RS_L
      case 74: // RS_HL
      case 75: // RS_A
      case 76: // RD_BC
      case 77: // RD_DE
      case 78: // RD_HL
      case 79: // RD_SP
      case 80: // RD_AF
      case 81: // CC_COND
      case 89: // instruction
      case 90: // sreg
      case 91: // dreg
      case 92: // dregaf
      case 93: // snum
      case 94: // pnum
        yylhs.value.build< u16 > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 106 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.init(8192); }
#line 636 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 106 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { }
#line 642 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 110 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { }
#line 648 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 111 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { }
#line 654 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 116 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_NOP); }
#line 660 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 117 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_DJNZ_N); }
#line 666 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 120 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_R_R | (yystack_[2].value.as< u16 > () << 3) | (yystack_[0].value.as< u16 > ())); }
#line 672 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 121 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_R_N | (yystack_[2].value.as< u16 > () << 3), (u8)yystack_[0].value.as< u16 > ()); }
#line 678 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 122 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_RR_NN | (yystack_[2].value.as< u16 > () << 4), (u8)(yystack_[0].value.as< u16 > () & 0xFF), (u8)((yystack_[0].value.as< u16 > () >> 8) & 0xFF) ); }
#line 684 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 124 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_BC_A); }
#line 690 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 125 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_DE_A); }
#line 696 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 126 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.aassert(yystack_[2].value.as< u16 > () == 7, "LD A, (BC) requires A reg!"); assembler.assemble(OPCODE_LD_A_BC); }
#line 702 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 127 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.aassert(yystack_[2].value.as< u16 > () == 7, "LD A, (DE) requires A reg!"); assembler.assemble(OPCODE_LD_A_DE); }
#line 708 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 128 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_SP_HL); }
#line 714 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 129 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_NN_A, (u8)(yystack_[3].value.as< u16 > () & 0xFF), (u8)((yystack_[3].value.as< u16 > () >> 8) & 0xFF)); }
#line 720 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 130 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.aassert(yystack_[2].value.as< u16 > () == 7, "LD A, (nn) requires A reg!"); assembler.assemble(OPCODE_LD_A_NN, (u8)(yystack_[0].value.as< u16 > () & 0xFF), (u8)((yystack_[0].value.as< u16 > () >> 8) & 0xFF)); }
#line 726 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 132 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_HL_NN, (u8)(yystack_[0].value.as< u16 > () & 0xFF), (u8)((yystack_[0].value.as< u16 > () >> 8) & 0xFF)); }
#line 732 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 133 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_NN_HL, (u8)(yystack_[3].value.as< u16 > () & 0xFF), (u8)((yystack_[3].value.as< u16 > () >> 8) & 0xFF)); }
#line 738 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 135 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_NN_HL); }
#line 744 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 136 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_HL_NN); }
#line 750 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 137 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_NN_A); }
#line 756 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 138 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_LD_A_NN); }
#line 762 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 140 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_EX_AF_AF, (u8)(yystack_[3].value.as< u16 > () & 0xFF), (u8)((yystack_[3].value.as< u16 > () >> 8) & 0xFF)); }
#line 768 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 142 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_ADD_R | yystack_[0].value.as< u16 > ()); }
#line 774 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 143 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_ADC_R | yystack_[0].value.as< u16 > ()); }
#line 780 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 144 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_SUB_R | yystack_[0].value.as< u16 > ()); }
#line 786 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 145 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_SBC_R | yystack_[0].value.as< u16 > ()); }
#line 792 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 146 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_DAA); }
#line 798 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 148 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_AND_R | yystack_[0].value.as< u16 > ()); }
#line 804 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 149 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_XOR_R | yystack_[0].value.as< u16 > ()); }
#line 810 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 150 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_OR_R | yystack_[0].value.as< u16 > ()); }
#line 816 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 151 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_CP_R | yystack_[0].value.as< u16 > ()); }
#line 822 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 153 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_ADD_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 828 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 154 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_ADC_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 834 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 155 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_SUB_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 840 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 156 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_SBC_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 846 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 158 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_AND_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 852 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 159 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_XOR_N | (u8)yystack_[0].value.as< u16 > ()); }
#line 858 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 160 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_OR_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 864 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 161 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_CP_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 870 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 163 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_RLCA); }
#line 876 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 164 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_RLA); }
#line 882 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 165 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_RRCA); }
#line 888 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 166 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_RRA); }
#line 894 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 168 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_BITS, OPCODE_RLC | yystack_[0].value.as< u16 > ()); }
#line 900 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 169 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_BITS, OPCODE_RL | yystack_[0].value.as< u16 > ()); }
#line 906 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 170 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_BITS, OPCODE_RRC | yystack_[0].value.as< u16 > ()); }
#line 912 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 171 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_BITS, OPCODE_RR | yystack_[0].value.as< u16 > ()); }
#line 918 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 172 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_BITS, OPCODE_SLA | yystack_[0].value.as< u16 > ()); }
#line 924 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 173 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_BITS, OPCODE_SRA | yystack_[0].value.as< u16 > ()); }
#line 930 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 174 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_BITS, OPCODE_SLL | yystack_[0].value.as< u16 > ()); }
#line 936 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 175 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_BITS, OPCODE_SRL | yystack_[0].value.as< u16 > ()); }
#line 942 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 176 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_BITS, OPCODE_SLL | yystack_[0].value.as< u16 > ()); }
#line 948 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 178 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.aassert(yystack_[2].value.as< u16 > () <= 7, "BIT specifier over bounds!"); assembler.assemble(OPCODE_BITS, OPCODE_BIT | (yystack_[2].value.as< u16 > () << 3) | yystack_[0].value.as< u16 > ()); }
#line 954 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 179 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.aassert(yystack_[2].value.as< u16 > () <= 7, "RES specifier over bounds!"); assembler.assemble(OPCODE_BITS, OPCODE_RES | (yystack_[2].value.as< u16 > () << 3) | yystack_[0].value.as< u16 > ()); }
#line 960 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 180 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.aassert(yystack_[2].value.as< u16 > () <= 7, "SET specifier over bounds!"); assembler.assemble(OPCODE_BITS, OPCODE_SET | (yystack_[2].value.as< u16 > () << 3) | yystack_[0].value.as< u16 > ()); }
#line 966 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 182 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_CPL); }
#line 972 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 183 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_SCF); }
#line 978 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 184 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_CCF); }
#line 984 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 186 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_ADD_HL_RR | yystack_[0].value.as< u16 > () << 4); }
#line 990 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 188 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_DJNZ_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 996 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 189 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_JR_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 1002 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 190 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_JRNZ_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 1008 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 191 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_JRZ_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 1014 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 192 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_JRNC_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 1020 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 193 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_JRC_N, (u8)yystack_[0].value.as< u16 > ()); }
#line 1026 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 195 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_JP_NN, (u8)(yystack_[0].value.as< u16 > () & 0xFF), (u8)((yystack_[0].value.as< u16 > () >> 8) & 0xFF)); }
#line 1032 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 196 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_JP_CC_NN | (yystack_[1].value.as< u16 > () << 3), (u8)(yystack_[0].value.as< u16 > () & 0xFF), (u8)((yystack_[0].value.as< u16 > () >> 8) & 0xFF)); }
#line 1038 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 197 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_JP_HL); }
#line 1044 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 199 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_CALL_NN, (u8)(yystack_[0].value.as< u16 > () & 0xFF), (u8)((yystack_[0].value.as< u16 > () >> 8) & 0xFF)); }
#line 1050 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 200 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_CALL_CC_NN | (yystack_[1].value.as< u16 > () << 3), (u8)(yystack_[0].value.as< u16 > () & 0xFF), (u8)((yystack_[0].value.as< u16 > () >> 8) & 0xFF)); }
#line 1056 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 202 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.aassert(assembler.correctRSTAddress(yystack_[0].value.as< u16 > ()), "RST Address over bounds!"); assembler.assemble(OPCODE_RST | ((yystack_[0].value.as< u16 > ()/8) << 3)); }
#line 1062 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 204 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_RET); }
#line 1068 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 205 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_RET_CC | (yystack_[0].value.as< u16 > () << 3)); }
#line 1074 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 206 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_EXX); }
#line 1080 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 208 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_PUSH | (yystack_[0].value.as< u16 > () << 4)); }
#line 1086 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 209 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_POP | (yystack_[0].value.as< u16 > () << 4)); }
#line 1092 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 211 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_EI); }
#line 1098 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 212 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_DI); }
#line 1104 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 214 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_INC_R | (yystack_[0].value.as< u16 > () << 3)); }
#line 1110 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 215 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_DEC_R | (yystack_[0].value.as< u16 > () << 3)); }
#line 1116 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 217 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_INC_RR | (yystack_[0].value.as< u16 > () << 4)); }
#line 1122 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 218 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_DEC_RR | (yystack_[0].value.as< u16 > () << 4)); }
#line 1128 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 220 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_OUT_N_A, yystack_[2].value.as< u16 > ()); }
#line 1134 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 221 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_IN_N_A, yystack_[0].value.as< u16 > ()); }
#line 1140 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 223 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_EX_AF_AF); }
#line 1146 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 224 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_EXX); }
#line 1152 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 225 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_EX_SP_HL); }
#line 1158 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 226 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_EX_DE_HL); }
#line 1164 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 228 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { assembler.assemble(OPCODE_HALT); }
#line 1170 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 236 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1176 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 237 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1182 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 238 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1188 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 239 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1194 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 240 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1200 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 241 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1206 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 242 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1212 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 243 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1218 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 247 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1224 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 248 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1230 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 249 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1236 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 250 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1242 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 254 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1248 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 255 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1254 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 256 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1260 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 257 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1266 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 261 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[0].value.as< u16 > (); }
#line 1272 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 265 "src/assembler/gbparser.ypp" // lalr1.cc:859
    { yylhs.value.as< u16 > () = yystack_[1].value.as< u16 > (); }
#line 1278 "src/assembler/gbparser.cpp" // lalr1.cc:859
    break;


#line 1282 "src/assembler/gbparser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
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

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -69;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
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

  const unsigned char
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

  const short int
  Parser::yypgoto_[] =
  {
     -69,   -69,   -69,   -69,   -69,    21,   -10,   128,   -13,    24
  };

  const short int
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

  const short int
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

  const unsigned char
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

  const unsigned char
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

  const unsigned char
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



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "T_COLON", "T_COMMA",
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

#if YYDEBUG
  const unsigned short int
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

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 5 "src/assembler/gbparser.ypp" // lalr1.cc:1167
} // assembler
#line 1795 "src/assembler/gbparser.cpp" // lalr1.cc:1167
#line 273 "src/assembler/gbparser.ypp" // lalr1.cc:1168


void assembler::Parser::error(const location_type& l, const std::string& m)
{
  assembler.error(l,m);
}
