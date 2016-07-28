// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file src/assembler/gbparser.hpp
 ** Define the assembler::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_SRC_ASSEMBLER_GBPARSER_HPP_INCLUDED
# define YY_YY_SRC_ASSEMBLER_GBPARSER_HPP_INCLUDED
// //                    "%code requires" blocks.
#line 12 "src/assembler/gbparser.ypp" // lalr1.cc:392

  #include "../utils.h"
  #include "../opcodes.h"
  
  namespace assembler
  {
    class Assembler;
    class Lexer;
  }

  using namespace gb;

#line 57 "src/assembler/gbparser.hpp" // lalr1.cc:392

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 5 "src/assembler/gbparser.ypp" // lalr1.cc:392
namespace assembler {
#line 134 "src/assembler/gbparser.hpp" // lalr1.cc:392



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // FLOAT
      char dummy1[sizeof(float)];

      // LITERAL
      // IDENTIFIER
      char dummy2[sizeof(std::string)];

      // U16
      // RS_B
      // RS_C
      // RS_D
      // RS_E
      // RS_H
      // RS_L
      // RS_HL
      // RS_A
      // RD_BC
      // RD_DE
      // RD_HL
      // RD_SP
      // RD_AF
      // CC_COND
      // instruction
      // sreg
      // dreg
      // dregaf
      // snum
      // pnum
      char dummy3[sizeof(u16)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        T_COLON = 258,
        T_COMMA = 259,
        T_LPAREN = 260,
        T_RPAREN = 261,
        T_QUOTE = 262,
        RDP_BC = 263,
        RDP_DE = 264,
        RDP_SP = 265,
        EOL = 266,
        OP_NOP = 267,
        OP_STOP = 268,
        OP_LD = 269,
        OP_LDI = 270,
        OP_LDD = 271,
        OP_HALT = 272,
        OP_ADD = 273,
        OP_ADC = 274,
        OP_SUB = 275,
        OP_SBC = 276,
        OP_AND = 277,
        OP_XOR = 278,
        OP_OR = 279,
        OP_INC = 280,
        OP_DEC = 281,
        OP_CP = 282,
        OP_DAA = 283,
        OP_RLCA = 284,
        OP_RLA = 285,
        OP_RRCA = 286,
        OP_RRA = 287,
        OP_CPL = 288,
        OP_CCF = 289,
        OP_SCF = 290,
        OP_DJNZ = 291,
        OP_JR = 292,
        OP_JRNZ = 293,
        OP_JRZ = 294,
        OP_JRNC = 295,
        OP_JRC = 296,
        OP_CALL = 297,
        OP_RET = 298,
        OP_JP = 299,
        OP_PUSH = 300,
        OP_POP = 301,
        OP_RST = 302,
        OP_RETI = 303,
        OP_BIT = 304,
        OP_RES = 305,
        OP_SET = 306,
        OP_RLC = 307,
        OP_RL = 308,
        OP_RRC = 309,
        OP_RR = 310,
        OP_SLA = 311,
        OP_SRA = 312,
        OP_SLL = 313,
        OP_SRL = 314,
        OP_SWAP = 315,
        OP_EI = 316,
        OP_DI = 317,
        OP_OUT = 318,
        OP_IN = 319,
        OP_EX = 320,
        OP_EXX = 321,
        U16 = 322,
        RS_B = 323,
        RS_C = 324,
        RS_D = 325,
        RS_E = 326,
        RS_H = 327,
        RS_L = 328,
        RS_HL = 329,
        RS_A = 330,
        RD_BC = 331,
        RD_DE = 332,
        RD_HL = 333,
        RD_SP = 334,
        RD_AF = 335,
        CC_COND = 336,
        FLOAT = 337,
        LITERAL = 338,
        IDENTIFIER = 339
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const float v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const u16 v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_T_COLON (const location_type& l);

    static inline
    symbol_type
    make_T_COMMA (const location_type& l);

    static inline
    symbol_type
    make_T_LPAREN (const location_type& l);

    static inline
    symbol_type
    make_T_RPAREN (const location_type& l);

    static inline
    symbol_type
    make_T_QUOTE (const location_type& l);

    static inline
    symbol_type
    make_RDP_BC (const location_type& l);

    static inline
    symbol_type
    make_RDP_DE (const location_type& l);

    static inline
    symbol_type
    make_RDP_SP (const location_type& l);

    static inline
    symbol_type
    make_EOL (const location_type& l);

    static inline
    symbol_type
    make_OP_NOP (const location_type& l);

    static inline
    symbol_type
    make_OP_STOP (const location_type& l);

    static inline
    symbol_type
    make_OP_LD (const location_type& l);

    static inline
    symbol_type
    make_OP_LDI (const location_type& l);

    static inline
    symbol_type
    make_OP_LDD (const location_type& l);

    static inline
    symbol_type
    make_OP_HALT (const location_type& l);

    static inline
    symbol_type
    make_OP_ADD (const location_type& l);

    static inline
    symbol_type
    make_OP_ADC (const location_type& l);

    static inline
    symbol_type
    make_OP_SUB (const location_type& l);

    static inline
    symbol_type
    make_OP_SBC (const location_type& l);

    static inline
    symbol_type
    make_OP_AND (const location_type& l);

    static inline
    symbol_type
    make_OP_XOR (const location_type& l);

    static inline
    symbol_type
    make_OP_OR (const location_type& l);

    static inline
    symbol_type
    make_OP_INC (const location_type& l);

    static inline
    symbol_type
    make_OP_DEC (const location_type& l);

    static inline
    symbol_type
    make_OP_CP (const location_type& l);

    static inline
    symbol_type
    make_OP_DAA (const location_type& l);

    static inline
    symbol_type
    make_OP_RLCA (const location_type& l);

    static inline
    symbol_type
    make_OP_RLA (const location_type& l);

    static inline
    symbol_type
    make_OP_RRCA (const location_type& l);

    static inline
    symbol_type
    make_OP_RRA (const location_type& l);

    static inline
    symbol_type
    make_OP_CPL (const location_type& l);

    static inline
    symbol_type
    make_OP_CCF (const location_type& l);

    static inline
    symbol_type
    make_OP_SCF (const location_type& l);

    static inline
    symbol_type
    make_OP_DJNZ (const location_type& l);

    static inline
    symbol_type
    make_OP_JR (const location_type& l);

    static inline
    symbol_type
    make_OP_JRNZ (const location_type& l);

    static inline
    symbol_type
    make_OP_JRZ (const location_type& l);

    static inline
    symbol_type
    make_OP_JRNC (const location_type& l);

    static inline
    symbol_type
    make_OP_JRC (const location_type& l);

    static inline
    symbol_type
    make_OP_CALL (const location_type& l);

    static inline
    symbol_type
    make_OP_RET (const location_type& l);

    static inline
    symbol_type
    make_OP_JP (const location_type& l);

    static inline
    symbol_type
    make_OP_PUSH (const location_type& l);

    static inline
    symbol_type
    make_OP_POP (const location_type& l);

    static inline
    symbol_type
    make_OP_RST (const location_type& l);

    static inline
    symbol_type
    make_OP_RETI (const location_type& l);

    static inline
    symbol_type
    make_OP_BIT (const location_type& l);

    static inline
    symbol_type
    make_OP_RES (const location_type& l);

    static inline
    symbol_type
    make_OP_SET (const location_type& l);

    static inline
    symbol_type
    make_OP_RLC (const location_type& l);

    static inline
    symbol_type
    make_OP_RL (const location_type& l);

    static inline
    symbol_type
    make_OP_RRC (const location_type& l);

    static inline
    symbol_type
    make_OP_RR (const location_type& l);

    static inline
    symbol_type
    make_OP_SLA (const location_type& l);

    static inline
    symbol_type
    make_OP_SRA (const location_type& l);

    static inline
    symbol_type
    make_OP_SLL (const location_type& l);

    static inline
    symbol_type
    make_OP_SRL (const location_type& l);

    static inline
    symbol_type
    make_OP_SWAP (const location_type& l);

    static inline
    symbol_type
    make_OP_EI (const location_type& l);

    static inline
    symbol_type
    make_OP_DI (const location_type& l);

    static inline
    symbol_type
    make_OP_OUT (const location_type& l);

    static inline
    symbol_type
    make_OP_IN (const location_type& l);

    static inline
    symbol_type
    make_OP_EX (const location_type& l);

    static inline
    symbol_type
    make_OP_EXX (const location_type& l);

    static inline
    symbol_type
    make_U16 (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RS_B (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RS_C (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RS_D (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RS_E (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RS_H (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RS_L (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RS_HL (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RS_A (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RD_BC (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RD_DE (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RD_HL (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RD_SP (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_RD_AF (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_CC_COND (const u16& v, const location_type& l);

    static inline
    symbol_type
    make_FLOAT (const float& v, const location_type& l);

    static inline
    symbol_type
    make_LITERAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_IDENTIFIER (const std::string& v, const location_type& l);


    /// Build a parser object.
    Parser (assembler::Lexer &lexer_yyarg, assembler::Assembler &assembler_yyarg);
    virtual ~Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    Parser (const Parser&);
    Parser& operator= (const Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const unsigned char yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 242,     ///< Last index in yytable_.
      yynnts_ = 10,  ///< Number of nonterminal symbols.
      yyfinal_ = 3, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 85  ///< Number of tokens.
    };


    // User arguments.
    assembler::Lexer &lexer;
    assembler::Assembler &assembler;
  };

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84
    };
    const unsigned int user_token_number_max_ = 339;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 82: // FLOAT
        value.copy< float > (other.value);
        break;

      case 83: // LITERAL
      case 84: // IDENTIFIER
        value.copy< std::string > (other.value);
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
        value.copy< u16 > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 82: // FLOAT
        value.copy< float > (v);
        break;

      case 83: // LITERAL
      case 84: // IDENTIFIER
        value.copy< std::string > (v);
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
        value.copy< u16 > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const float v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const u16 v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 82: // FLOAT
        value.template destroy< float > ();
        break;

      case 83: // LITERAL
      case 84: // IDENTIFIER
        value.template destroy< std::string > ();
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
        value.template destroy< u16 > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 82: // FLOAT
        value.move< float > (s.value);
        break;

      case 83: // LITERAL
      case 84: // IDENTIFIER
        value.move< std::string > (s.value);
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
        value.move< u16 > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }

  inline
  Parser::token_type
  Parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  Parser::symbol_type
  Parser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  Parser::symbol_type
  Parser::make_T_COLON (const location_type& l)
  {
    return symbol_type (token::T_COLON, l);
  }

  Parser::symbol_type
  Parser::make_T_COMMA (const location_type& l)
  {
    return symbol_type (token::T_COMMA, l);
  }

  Parser::symbol_type
  Parser::make_T_LPAREN (const location_type& l)
  {
    return symbol_type (token::T_LPAREN, l);
  }

  Parser::symbol_type
  Parser::make_T_RPAREN (const location_type& l)
  {
    return symbol_type (token::T_RPAREN, l);
  }

  Parser::symbol_type
  Parser::make_T_QUOTE (const location_type& l)
  {
    return symbol_type (token::T_QUOTE, l);
  }

  Parser::symbol_type
  Parser::make_RDP_BC (const location_type& l)
  {
    return symbol_type (token::RDP_BC, l);
  }

  Parser::symbol_type
  Parser::make_RDP_DE (const location_type& l)
  {
    return symbol_type (token::RDP_DE, l);
  }

  Parser::symbol_type
  Parser::make_RDP_SP (const location_type& l)
  {
    return symbol_type (token::RDP_SP, l);
  }

  Parser::symbol_type
  Parser::make_EOL (const location_type& l)
  {
    return symbol_type (token::EOL, l);
  }

  Parser::symbol_type
  Parser::make_OP_NOP (const location_type& l)
  {
    return symbol_type (token::OP_NOP, l);
  }

  Parser::symbol_type
  Parser::make_OP_STOP (const location_type& l)
  {
    return symbol_type (token::OP_STOP, l);
  }

  Parser::symbol_type
  Parser::make_OP_LD (const location_type& l)
  {
    return symbol_type (token::OP_LD, l);
  }

  Parser::symbol_type
  Parser::make_OP_LDI (const location_type& l)
  {
    return symbol_type (token::OP_LDI, l);
  }

  Parser::symbol_type
  Parser::make_OP_LDD (const location_type& l)
  {
    return symbol_type (token::OP_LDD, l);
  }

  Parser::symbol_type
  Parser::make_OP_HALT (const location_type& l)
  {
    return symbol_type (token::OP_HALT, l);
  }

  Parser::symbol_type
  Parser::make_OP_ADD (const location_type& l)
  {
    return symbol_type (token::OP_ADD, l);
  }

  Parser::symbol_type
  Parser::make_OP_ADC (const location_type& l)
  {
    return symbol_type (token::OP_ADC, l);
  }

  Parser::symbol_type
  Parser::make_OP_SUB (const location_type& l)
  {
    return symbol_type (token::OP_SUB, l);
  }

  Parser::symbol_type
  Parser::make_OP_SBC (const location_type& l)
  {
    return symbol_type (token::OP_SBC, l);
  }

  Parser::symbol_type
  Parser::make_OP_AND (const location_type& l)
  {
    return symbol_type (token::OP_AND, l);
  }

  Parser::symbol_type
  Parser::make_OP_XOR (const location_type& l)
  {
    return symbol_type (token::OP_XOR, l);
  }

  Parser::symbol_type
  Parser::make_OP_OR (const location_type& l)
  {
    return symbol_type (token::OP_OR, l);
  }

  Parser::symbol_type
  Parser::make_OP_INC (const location_type& l)
  {
    return symbol_type (token::OP_INC, l);
  }

  Parser::symbol_type
  Parser::make_OP_DEC (const location_type& l)
  {
    return symbol_type (token::OP_DEC, l);
  }

  Parser::symbol_type
  Parser::make_OP_CP (const location_type& l)
  {
    return symbol_type (token::OP_CP, l);
  }

  Parser::symbol_type
  Parser::make_OP_DAA (const location_type& l)
  {
    return symbol_type (token::OP_DAA, l);
  }

  Parser::symbol_type
  Parser::make_OP_RLCA (const location_type& l)
  {
    return symbol_type (token::OP_RLCA, l);
  }

  Parser::symbol_type
  Parser::make_OP_RLA (const location_type& l)
  {
    return symbol_type (token::OP_RLA, l);
  }

  Parser::symbol_type
  Parser::make_OP_RRCA (const location_type& l)
  {
    return symbol_type (token::OP_RRCA, l);
  }

  Parser::symbol_type
  Parser::make_OP_RRA (const location_type& l)
  {
    return symbol_type (token::OP_RRA, l);
  }

  Parser::symbol_type
  Parser::make_OP_CPL (const location_type& l)
  {
    return symbol_type (token::OP_CPL, l);
  }

  Parser::symbol_type
  Parser::make_OP_CCF (const location_type& l)
  {
    return symbol_type (token::OP_CCF, l);
  }

  Parser::symbol_type
  Parser::make_OP_SCF (const location_type& l)
  {
    return symbol_type (token::OP_SCF, l);
  }

  Parser::symbol_type
  Parser::make_OP_DJNZ (const location_type& l)
  {
    return symbol_type (token::OP_DJNZ, l);
  }

  Parser::symbol_type
  Parser::make_OP_JR (const location_type& l)
  {
    return symbol_type (token::OP_JR, l);
  }

  Parser::symbol_type
  Parser::make_OP_JRNZ (const location_type& l)
  {
    return symbol_type (token::OP_JRNZ, l);
  }

  Parser::symbol_type
  Parser::make_OP_JRZ (const location_type& l)
  {
    return symbol_type (token::OP_JRZ, l);
  }

  Parser::symbol_type
  Parser::make_OP_JRNC (const location_type& l)
  {
    return symbol_type (token::OP_JRNC, l);
  }

  Parser::symbol_type
  Parser::make_OP_JRC (const location_type& l)
  {
    return symbol_type (token::OP_JRC, l);
  }

  Parser::symbol_type
  Parser::make_OP_CALL (const location_type& l)
  {
    return symbol_type (token::OP_CALL, l);
  }

  Parser::symbol_type
  Parser::make_OP_RET (const location_type& l)
  {
    return symbol_type (token::OP_RET, l);
  }

  Parser::symbol_type
  Parser::make_OP_JP (const location_type& l)
  {
    return symbol_type (token::OP_JP, l);
  }

  Parser::symbol_type
  Parser::make_OP_PUSH (const location_type& l)
  {
    return symbol_type (token::OP_PUSH, l);
  }

  Parser::symbol_type
  Parser::make_OP_POP (const location_type& l)
  {
    return symbol_type (token::OP_POP, l);
  }

  Parser::symbol_type
  Parser::make_OP_RST (const location_type& l)
  {
    return symbol_type (token::OP_RST, l);
  }

  Parser::symbol_type
  Parser::make_OP_RETI (const location_type& l)
  {
    return symbol_type (token::OP_RETI, l);
  }

  Parser::symbol_type
  Parser::make_OP_BIT (const location_type& l)
  {
    return symbol_type (token::OP_BIT, l);
  }

  Parser::symbol_type
  Parser::make_OP_RES (const location_type& l)
  {
    return symbol_type (token::OP_RES, l);
  }

  Parser::symbol_type
  Parser::make_OP_SET (const location_type& l)
  {
    return symbol_type (token::OP_SET, l);
  }

  Parser::symbol_type
  Parser::make_OP_RLC (const location_type& l)
  {
    return symbol_type (token::OP_RLC, l);
  }

  Parser::symbol_type
  Parser::make_OP_RL (const location_type& l)
  {
    return symbol_type (token::OP_RL, l);
  }

  Parser::symbol_type
  Parser::make_OP_RRC (const location_type& l)
  {
    return symbol_type (token::OP_RRC, l);
  }

  Parser::symbol_type
  Parser::make_OP_RR (const location_type& l)
  {
    return symbol_type (token::OP_RR, l);
  }

  Parser::symbol_type
  Parser::make_OP_SLA (const location_type& l)
  {
    return symbol_type (token::OP_SLA, l);
  }

  Parser::symbol_type
  Parser::make_OP_SRA (const location_type& l)
  {
    return symbol_type (token::OP_SRA, l);
  }

  Parser::symbol_type
  Parser::make_OP_SLL (const location_type& l)
  {
    return symbol_type (token::OP_SLL, l);
  }

  Parser::symbol_type
  Parser::make_OP_SRL (const location_type& l)
  {
    return symbol_type (token::OP_SRL, l);
  }

  Parser::symbol_type
  Parser::make_OP_SWAP (const location_type& l)
  {
    return symbol_type (token::OP_SWAP, l);
  }

  Parser::symbol_type
  Parser::make_OP_EI (const location_type& l)
  {
    return symbol_type (token::OP_EI, l);
  }

  Parser::symbol_type
  Parser::make_OP_DI (const location_type& l)
  {
    return symbol_type (token::OP_DI, l);
  }

  Parser::symbol_type
  Parser::make_OP_OUT (const location_type& l)
  {
    return symbol_type (token::OP_OUT, l);
  }

  Parser::symbol_type
  Parser::make_OP_IN (const location_type& l)
  {
    return symbol_type (token::OP_IN, l);
  }

  Parser::symbol_type
  Parser::make_OP_EX (const location_type& l)
  {
    return symbol_type (token::OP_EX, l);
  }

  Parser::symbol_type
  Parser::make_OP_EXX (const location_type& l)
  {
    return symbol_type (token::OP_EXX, l);
  }

  Parser::symbol_type
  Parser::make_U16 (const u16& v, const location_type& l)
  {
    return symbol_type (token::U16, v, l);
  }

  Parser::symbol_type
  Parser::make_RS_B (const u16& v, const location_type& l)
  {
    return symbol_type (token::RS_B, v, l);
  }

  Parser::symbol_type
  Parser::make_RS_C (const u16& v, const location_type& l)
  {
    return symbol_type (token::RS_C, v, l);
  }

  Parser::symbol_type
  Parser::make_RS_D (const u16& v, const location_type& l)
  {
    return symbol_type (token::RS_D, v, l);
  }

  Parser::symbol_type
  Parser::make_RS_E (const u16& v, const location_type& l)
  {
    return symbol_type (token::RS_E, v, l);
  }

  Parser::symbol_type
  Parser::make_RS_H (const u16& v, const location_type& l)
  {
    return symbol_type (token::RS_H, v, l);
  }

  Parser::symbol_type
  Parser::make_RS_L (const u16& v, const location_type& l)
  {
    return symbol_type (token::RS_L, v, l);
  }

  Parser::symbol_type
  Parser::make_RS_HL (const u16& v, const location_type& l)
  {
    return symbol_type (token::RS_HL, v, l);
  }

  Parser::symbol_type
  Parser::make_RS_A (const u16& v, const location_type& l)
  {
    return symbol_type (token::RS_A, v, l);
  }

  Parser::symbol_type
  Parser::make_RD_BC (const u16& v, const location_type& l)
  {
    return symbol_type (token::RD_BC, v, l);
  }

  Parser::symbol_type
  Parser::make_RD_DE (const u16& v, const location_type& l)
  {
    return symbol_type (token::RD_DE, v, l);
  }

  Parser::symbol_type
  Parser::make_RD_HL (const u16& v, const location_type& l)
  {
    return symbol_type (token::RD_HL, v, l);
  }

  Parser::symbol_type
  Parser::make_RD_SP (const u16& v, const location_type& l)
  {
    return symbol_type (token::RD_SP, v, l);
  }

  Parser::symbol_type
  Parser::make_RD_AF (const u16& v, const location_type& l)
  {
    return symbol_type (token::RD_AF, v, l);
  }

  Parser::symbol_type
  Parser::make_CC_COND (const u16& v, const location_type& l)
  {
    return symbol_type (token::CC_COND, v, l);
  }

  Parser::symbol_type
  Parser::make_FLOAT (const float& v, const location_type& l)
  {
    return symbol_type (token::FLOAT, v, l);
  }

  Parser::symbol_type
  Parser::make_LITERAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::LITERAL, v, l);
  }

  Parser::symbol_type
  Parser::make_IDENTIFIER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::IDENTIFIER, v, l);
  }


#line 5 "src/assembler/gbparser.ypp" // lalr1.cc:392
} // assembler
#line 1976 "src/assembler/gbparser.hpp" // lalr1.cc:392




#endif // !YY_YY_SRC_ASSEMBLER_GBPARSER_HPP_INCLUDED
