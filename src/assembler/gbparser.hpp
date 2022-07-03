// A Bison parser, made by GNU Bison 3.7.1.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file src/assembler/gbparser.hpp
 ** Define the assembler::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_SRC_ASSEMBLER_GBPARSER_HPP_INCLUDED
# define YY_YY_SRC_ASSEMBLER_GBPARSER_HPP_INCLUDED
// "%code requires" blocks.
#line 12 "src/assembler/gbparser.ypp"

  #include "../utils.h"
  #include "../opcodes.h"
  
  namespace assembler
  {
    class Assembler;
    class Lexer;
  }

  using namespace gb;

#line 62 "src/assembler/gbparser.hpp"

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"
#include <typeinfo>
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 5 "src/assembler/gbparser.ypp"
namespace assembler {
#line 197 "src/assembler/gbparser.hpp"




  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
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
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // FLOAT
      char dummy1[sizeof (float)];

      // LITERAL
      // IDENTIFIER
      char dummy2[sizeof (std::string)];

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
      char dummy3[sizeof (u16)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    END = 0,                       // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    T_COLON = 258,                 // T_COLON
    T_COMMA = 259,                 // T_COMMA
    T_LPAREN = 260,                // T_LPAREN
    T_RPAREN = 261,                // T_RPAREN
    T_QUOTE = 262,                 // T_QUOTE
    RDP_BC = 263,                  // RDP_BC
    RDP_DE = 264,                  // RDP_DE
    RDP_SP = 265,                  // RDP_SP
    EOL = 266,                     // "\n"
    OP_NOP = 267,                  // OP_NOP
    OP_STOP = 268,                 // OP_STOP
    OP_LD = 269,                   // OP_LD
    OP_LDI = 270,                  // OP_LDI
    OP_LDD = 271,                  // OP_LDD
    OP_HALT = 272,                 // OP_HALT
    OP_ADD = 273,                  // OP_ADD
    OP_ADC = 274,                  // OP_ADC
    OP_SUB = 275,                  // OP_SUB
    OP_SBC = 276,                  // OP_SBC
    OP_AND = 277,                  // OP_AND
    OP_XOR = 278,                  // OP_XOR
    OP_OR = 279,                   // OP_OR
    OP_INC = 280,                  // OP_INC
    OP_DEC = 281,                  // OP_DEC
    OP_CP = 282,                   // OP_CP
    OP_DAA = 283,                  // OP_DAA
    OP_RLCA = 284,                 // OP_RLCA
    OP_RLA = 285,                  // OP_RLA
    OP_RRCA = 286,                 // OP_RRCA
    OP_RRA = 287,                  // OP_RRA
    OP_CPL = 288,                  // OP_CPL
    OP_CCF = 289,                  // OP_CCF
    OP_SCF = 290,                  // OP_SCF
    OP_DJNZ = 291,                 // OP_DJNZ
    OP_JR = 292,                   // OP_JR
    OP_JRNZ = 293,                 // OP_JRNZ
    OP_JRZ = 294,                  // OP_JRZ
    OP_JRNC = 295,                 // OP_JRNC
    OP_JRC = 296,                  // OP_JRC
    OP_CALL = 297,                 // OP_CALL
    OP_RET = 298,                  // OP_RET
    OP_JP = 299,                   // OP_JP
    OP_PUSH = 300,                 // OP_PUSH
    OP_POP = 301,                  // OP_POP
    OP_RST = 302,                  // OP_RST
    OP_RETI = 303,                 // OP_RETI
    OP_BIT = 304,                  // OP_BIT
    OP_RES = 305,                  // OP_RES
    OP_SET = 306,                  // OP_SET
    OP_RLC = 307,                  // OP_RLC
    OP_RL = 308,                   // OP_RL
    OP_RRC = 309,                  // OP_RRC
    OP_RR = 310,                   // OP_RR
    OP_SLA = 311,                  // OP_SLA
    OP_SRA = 312,                  // OP_SRA
    OP_SLL = 313,                  // OP_SLL
    OP_SRL = 314,                  // OP_SRL
    OP_SWAP = 315,                 // OP_SWAP
    OP_EI = 316,                   // OP_EI
    OP_DI = 317,                   // OP_DI
    OP_OUT = 318,                  // OP_OUT
    OP_IN = 319,                   // OP_IN
    OP_EX = 320,                   // OP_EX
    OP_EXX = 321,                  // OP_EXX
    U16 = 322,                     // U16
    RS_B = 323,                    // RS_B
    RS_C = 324,                    // RS_C
    RS_D = 325,                    // RS_D
    RS_E = 326,                    // RS_E
    RS_H = 327,                    // RS_H
    RS_L = 328,                    // RS_L
    RS_HL = 329,                   // RS_HL
    RS_A = 330,                    // RS_A
    RD_BC = 331,                   // RD_BC
    RD_DE = 332,                   // RD_DE
    RD_HL = 333,                   // RD_HL
    RD_SP = 334,                   // RD_SP
    RD_AF = 335,                   // RD_AF
    CC_COND = 336,                 // CC_COND
    FLOAT = 337,                   // FLOAT
    LITERAL = 338,                 // LITERAL
    IDENTIFIER = 339               // IDENTIFIER
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 85, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_T_COLON = 3,                           // T_COLON
        S_T_COMMA = 4,                           // T_COMMA
        S_T_LPAREN = 5,                          // T_LPAREN
        S_T_RPAREN = 6,                          // T_RPAREN
        S_T_QUOTE = 7,                           // T_QUOTE
        S_RDP_BC = 8,                            // RDP_BC
        S_RDP_DE = 9,                            // RDP_DE
        S_RDP_SP = 10,                           // RDP_SP
        S_EOL = 11,                              // "\n"
        S_OP_NOP = 12,                           // OP_NOP
        S_OP_STOP = 13,                          // OP_STOP
        S_OP_LD = 14,                            // OP_LD
        S_OP_LDI = 15,                           // OP_LDI
        S_OP_LDD = 16,                           // OP_LDD
        S_OP_HALT = 17,                          // OP_HALT
        S_OP_ADD = 18,                           // OP_ADD
        S_OP_ADC = 19,                           // OP_ADC
        S_OP_SUB = 20,                           // OP_SUB
        S_OP_SBC = 21,                           // OP_SBC
        S_OP_AND = 22,                           // OP_AND
        S_OP_XOR = 23,                           // OP_XOR
        S_OP_OR = 24,                            // OP_OR
        S_OP_INC = 25,                           // OP_INC
        S_OP_DEC = 26,                           // OP_DEC
        S_OP_CP = 27,                            // OP_CP
        S_OP_DAA = 28,                           // OP_DAA
        S_OP_RLCA = 29,                          // OP_RLCA
        S_OP_RLA = 30,                           // OP_RLA
        S_OP_RRCA = 31,                          // OP_RRCA
        S_OP_RRA = 32,                           // OP_RRA
        S_OP_CPL = 33,                           // OP_CPL
        S_OP_CCF = 34,                           // OP_CCF
        S_OP_SCF = 35,                           // OP_SCF
        S_OP_DJNZ = 36,                          // OP_DJNZ
        S_OP_JR = 37,                            // OP_JR
        S_OP_JRNZ = 38,                          // OP_JRNZ
        S_OP_JRZ = 39,                           // OP_JRZ
        S_OP_JRNC = 40,                          // OP_JRNC
        S_OP_JRC = 41,                           // OP_JRC
        S_OP_CALL = 42,                          // OP_CALL
        S_OP_RET = 43,                           // OP_RET
        S_OP_JP = 44,                            // OP_JP
        S_OP_PUSH = 45,                          // OP_PUSH
        S_OP_POP = 46,                           // OP_POP
        S_OP_RST = 47,                           // OP_RST
        S_OP_RETI = 48,                          // OP_RETI
        S_OP_BIT = 49,                           // OP_BIT
        S_OP_RES = 50,                           // OP_RES
        S_OP_SET = 51,                           // OP_SET
        S_OP_RLC = 52,                           // OP_RLC
        S_OP_RL = 53,                            // OP_RL
        S_OP_RRC = 54,                           // OP_RRC
        S_OP_RR = 55,                            // OP_RR
        S_OP_SLA = 56,                           // OP_SLA
        S_OP_SRA = 57,                           // OP_SRA
        S_OP_SLL = 58,                           // OP_SLL
        S_OP_SRL = 59,                           // OP_SRL
        S_OP_SWAP = 60,                          // OP_SWAP
        S_OP_EI = 61,                            // OP_EI
        S_OP_DI = 62,                            // OP_DI
        S_OP_OUT = 63,                           // OP_OUT
        S_OP_IN = 64,                            // OP_IN
        S_OP_EX = 65,                            // OP_EX
        S_OP_EXX = 66,                           // OP_EXX
        S_U16 = 67,                              // U16
        S_RS_B = 68,                             // RS_B
        S_RS_C = 69,                             // RS_C
        S_RS_D = 70,                             // RS_D
        S_RS_E = 71,                             // RS_E
        S_RS_H = 72,                             // RS_H
        S_RS_L = 73,                             // RS_L
        S_RS_HL = 74,                            // RS_HL
        S_RS_A = 75,                             // RS_A
        S_RD_BC = 76,                            // RD_BC
        S_RD_DE = 77,                            // RD_DE
        S_RD_HL = 78,                            // RD_HL
        S_RD_SP = 79,                            // RD_SP
        S_RD_AF = 80,                            // RD_AF
        S_CC_COND = 81,                          // CC_COND
        S_FLOAT = 82,                            // FLOAT
        S_LITERAL = 83,                          // LITERAL
        S_IDENTIFIER = 84,                       // IDENTIFIER
        S_YYACCEPT = 85,                         // $accept
        S_start = 86,                            // start
        S_87_1 = 87,                             // $@1
        S_instructions = 88,                     // instructions
        S_instruction = 89,                      // instruction
        S_sreg = 90,                             // sreg
        S_dreg = 91,                             // dreg
        S_dregaf = 92,                           // dregaf
        S_snum = 93,                             // snum
        S_pnum = 94                              // pnum
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_FLOAT: // FLOAT
        value.move< float > (std::move (that.value));
        break;

      case symbol_kind::S_LITERAL: // LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.move< std::string > (std::move (that.value));
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
        value.move< u16 > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, float&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const float& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, u16&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const u16& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_FLOAT: // FLOAT
        value.template destroy< float > ();
        break;

      case symbol_kind::S_LITERAL: // LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.template destroy< std::string > ();
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
        value.template destroy< u16 > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YY_ASSERT (tok == token::END || tok == token::YYerror || tok == token::YYUNDEF || tok == token::T_COLON || tok == token::T_COMMA || tok == token::T_LPAREN || tok == token::T_RPAREN || tok == token::T_QUOTE || tok == token::RDP_BC || tok == token::RDP_DE || tok == token::RDP_SP || tok == token::EOL || tok == token::OP_NOP || tok == token::OP_STOP || tok == token::OP_LD || tok == token::OP_LDI || tok == token::OP_LDD || tok == token::OP_HALT || tok == token::OP_ADD || tok == token::OP_ADC || tok == token::OP_SUB || tok == token::OP_SBC || tok == token::OP_AND || tok == token::OP_XOR || tok == token::OP_OR || tok == token::OP_INC || tok == token::OP_DEC || tok == token::OP_CP || tok == token::OP_DAA || tok == token::OP_RLCA || tok == token::OP_RLA || tok == token::OP_RRCA || tok == token::OP_RRA || tok == token::OP_CPL || tok == token::OP_CCF || tok == token::OP_SCF || tok == token::OP_DJNZ || tok == token::OP_JR || tok == token::OP_JRNZ || tok == token::OP_JRZ || tok == token::OP_JRNC || tok == token::OP_JRC || tok == token::OP_CALL || tok == token::OP_RET || tok == token::OP_JP || tok == token::OP_PUSH || tok == token::OP_POP || tok == token::OP_RST || tok == token::OP_RETI || tok == token::OP_BIT || tok == token::OP_RES || tok == token::OP_SET || tok == token::OP_RLC || tok == token::OP_RL || tok == token::OP_RRC || tok == token::OP_RR || tok == token::OP_SLA || tok == token::OP_SRA || tok == token::OP_SLL || tok == token::OP_SRL || tok == token::OP_SWAP || tok == token::OP_EI || tok == token::OP_DI || tok == token::OP_OUT || tok == token::OP_IN || tok == token::OP_EX || tok == token::OP_EXX);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YY_ASSERT (tok == token::END || tok == token::YYerror || tok == token::YYUNDEF || tok == token::T_COLON || tok == token::T_COMMA || tok == token::T_LPAREN || tok == token::T_RPAREN || tok == token::T_QUOTE || tok == token::RDP_BC || tok == token::RDP_DE || tok == token::RDP_SP || tok == token::EOL || tok == token::OP_NOP || tok == token::OP_STOP || tok == token::OP_LD || tok == token::OP_LDI || tok == token::OP_LDD || tok == token::OP_HALT || tok == token::OP_ADD || tok == token::OP_ADC || tok == token::OP_SUB || tok == token::OP_SBC || tok == token::OP_AND || tok == token::OP_XOR || tok == token::OP_OR || tok == token::OP_INC || tok == token::OP_DEC || tok == token::OP_CP || tok == token::OP_DAA || tok == token::OP_RLCA || tok == token::OP_RLA || tok == token::OP_RRCA || tok == token::OP_RRA || tok == token::OP_CPL || tok == token::OP_CCF || tok == token::OP_SCF || tok == token::OP_DJNZ || tok == token::OP_JR || tok == token::OP_JRNZ || tok == token::OP_JRZ || tok == token::OP_JRNC || tok == token::OP_JRC || tok == token::OP_CALL || tok == token::OP_RET || tok == token::OP_JP || tok == token::OP_PUSH || tok == token::OP_POP || tok == token::OP_RST || tok == token::OP_RETI || tok == token::OP_BIT || tok == token::OP_RES || tok == token::OP_SET || tok == token::OP_RLC || tok == token::OP_RL || tok == token::OP_RRC || tok == token::OP_RR || tok == token::OP_SLA || tok == token::OP_SRA || tok == token::OP_SLL || tok == token::OP_SRL || tok == token::OP_SWAP || tok == token::OP_EI || tok == token::OP_DI || tok == token::OP_OUT || tok == token::OP_IN || tok == token::OP_EX || tok == token::OP_EXX);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, float v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::FLOAT);
      }
#else
      symbol_type (int tok, const float& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::FLOAT);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::LITERAL || tok == token::IDENTIFIER);
      }
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::LITERAL || tok == token::IDENTIFIER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, u16 v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::U16 || tok == token::RS_B || tok == token::RS_C || tok == token::RS_D || tok == token::RS_E || tok == token::RS_H || tok == token::RS_L || tok == token::RS_HL || tok == token::RS_A || tok == token::RD_BC || tok == token::RD_DE || tok == token::RD_HL || tok == token::RD_SP || tok == token::RD_AF || tok == token::CC_COND);
      }
#else
      symbol_type (int tok, const u16& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::U16 || tok == token::RS_B || tok == token::RS_C || tok == token::RS_D || tok == token::RS_E || tok == token::RS_H || tok == token::RS_L || tok == token::RS_HL || tok == token::RS_A || tok == token::RD_BC || tok == token::RD_DE || tok == token::RD_HL || tok == token::RD_SP || tok == token::RD_AF || tok == token::CC_COND);
      }
#endif
    };

    /// Build a parser object.
    Parser (assembler::Lexer &lexer_yyarg, assembler::Assembler &assembler_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

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

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_COLON (location_type l)
      {
        return symbol_type (token::T_COLON, std::move (l));
      }
#else
      static
      symbol_type
      make_T_COLON (const location_type& l)
      {
        return symbol_type (token::T_COLON, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_COMMA (location_type l)
      {
        return symbol_type (token::T_COMMA, std::move (l));
      }
#else
      static
      symbol_type
      make_T_COMMA (const location_type& l)
      {
        return symbol_type (token::T_COMMA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_LPAREN (location_type l)
      {
        return symbol_type (token::T_LPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_T_LPAREN (const location_type& l)
      {
        return symbol_type (token::T_LPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_RPAREN (location_type l)
      {
        return symbol_type (token::T_RPAREN, std::move (l));
      }
#else
      static
      symbol_type
      make_T_RPAREN (const location_type& l)
      {
        return symbol_type (token::T_RPAREN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_T_QUOTE (location_type l)
      {
        return symbol_type (token::T_QUOTE, std::move (l));
      }
#else
      static
      symbol_type
      make_T_QUOTE (const location_type& l)
      {
        return symbol_type (token::T_QUOTE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RDP_BC (location_type l)
      {
        return symbol_type (token::RDP_BC, std::move (l));
      }
#else
      static
      symbol_type
      make_RDP_BC (const location_type& l)
      {
        return symbol_type (token::RDP_BC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RDP_DE (location_type l)
      {
        return symbol_type (token::RDP_DE, std::move (l));
      }
#else
      static
      symbol_type
      make_RDP_DE (const location_type& l)
      {
        return symbol_type (token::RDP_DE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RDP_SP (location_type l)
      {
        return symbol_type (token::RDP_SP, std::move (l));
      }
#else
      static
      symbol_type
      make_RDP_SP (const location_type& l)
      {
        return symbol_type (token::RDP_SP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EOL (location_type l)
      {
        return symbol_type (token::EOL, std::move (l));
      }
#else
      static
      symbol_type
      make_EOL (const location_type& l)
      {
        return symbol_type (token::EOL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_NOP (location_type l)
      {
        return symbol_type (token::OP_NOP, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_NOP (const location_type& l)
      {
        return symbol_type (token::OP_NOP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_STOP (location_type l)
      {
        return symbol_type (token::OP_STOP, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_STOP (const location_type& l)
      {
        return symbol_type (token::OP_STOP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_LD (location_type l)
      {
        return symbol_type (token::OP_LD, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_LD (const location_type& l)
      {
        return symbol_type (token::OP_LD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_LDI (location_type l)
      {
        return symbol_type (token::OP_LDI, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_LDI (const location_type& l)
      {
        return symbol_type (token::OP_LDI, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_LDD (location_type l)
      {
        return symbol_type (token::OP_LDD, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_LDD (const location_type& l)
      {
        return symbol_type (token::OP_LDD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_HALT (location_type l)
      {
        return symbol_type (token::OP_HALT, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_HALT (const location_type& l)
      {
        return symbol_type (token::OP_HALT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_ADD (location_type l)
      {
        return symbol_type (token::OP_ADD, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_ADD (const location_type& l)
      {
        return symbol_type (token::OP_ADD, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_ADC (location_type l)
      {
        return symbol_type (token::OP_ADC, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_ADC (const location_type& l)
      {
        return symbol_type (token::OP_ADC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_SUB (location_type l)
      {
        return symbol_type (token::OP_SUB, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_SUB (const location_type& l)
      {
        return symbol_type (token::OP_SUB, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_SBC (location_type l)
      {
        return symbol_type (token::OP_SBC, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_SBC (const location_type& l)
      {
        return symbol_type (token::OP_SBC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_AND (location_type l)
      {
        return symbol_type (token::OP_AND, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_AND (const location_type& l)
      {
        return symbol_type (token::OP_AND, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_XOR (location_type l)
      {
        return symbol_type (token::OP_XOR, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_XOR (const location_type& l)
      {
        return symbol_type (token::OP_XOR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_OR (location_type l)
      {
        return symbol_type (token::OP_OR, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_OR (const location_type& l)
      {
        return symbol_type (token::OP_OR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_INC (location_type l)
      {
        return symbol_type (token::OP_INC, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_INC (const location_type& l)
      {
        return symbol_type (token::OP_INC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_DEC (location_type l)
      {
        return symbol_type (token::OP_DEC, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_DEC (const location_type& l)
      {
        return symbol_type (token::OP_DEC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_CP (location_type l)
      {
        return symbol_type (token::OP_CP, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_CP (const location_type& l)
      {
        return symbol_type (token::OP_CP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_DAA (location_type l)
      {
        return symbol_type (token::OP_DAA, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_DAA (const location_type& l)
      {
        return symbol_type (token::OP_DAA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RLCA (location_type l)
      {
        return symbol_type (token::OP_RLCA, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RLCA (const location_type& l)
      {
        return symbol_type (token::OP_RLCA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RLA (location_type l)
      {
        return symbol_type (token::OP_RLA, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RLA (const location_type& l)
      {
        return symbol_type (token::OP_RLA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RRCA (location_type l)
      {
        return symbol_type (token::OP_RRCA, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RRCA (const location_type& l)
      {
        return symbol_type (token::OP_RRCA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RRA (location_type l)
      {
        return symbol_type (token::OP_RRA, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RRA (const location_type& l)
      {
        return symbol_type (token::OP_RRA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_CPL (location_type l)
      {
        return symbol_type (token::OP_CPL, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_CPL (const location_type& l)
      {
        return symbol_type (token::OP_CPL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_CCF (location_type l)
      {
        return symbol_type (token::OP_CCF, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_CCF (const location_type& l)
      {
        return symbol_type (token::OP_CCF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_SCF (location_type l)
      {
        return symbol_type (token::OP_SCF, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_SCF (const location_type& l)
      {
        return symbol_type (token::OP_SCF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_DJNZ (location_type l)
      {
        return symbol_type (token::OP_DJNZ, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_DJNZ (const location_type& l)
      {
        return symbol_type (token::OP_DJNZ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_JR (location_type l)
      {
        return symbol_type (token::OP_JR, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_JR (const location_type& l)
      {
        return symbol_type (token::OP_JR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_JRNZ (location_type l)
      {
        return symbol_type (token::OP_JRNZ, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_JRNZ (const location_type& l)
      {
        return symbol_type (token::OP_JRNZ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_JRZ (location_type l)
      {
        return symbol_type (token::OP_JRZ, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_JRZ (const location_type& l)
      {
        return symbol_type (token::OP_JRZ, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_JRNC (location_type l)
      {
        return symbol_type (token::OP_JRNC, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_JRNC (const location_type& l)
      {
        return symbol_type (token::OP_JRNC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_JRC (location_type l)
      {
        return symbol_type (token::OP_JRC, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_JRC (const location_type& l)
      {
        return symbol_type (token::OP_JRC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_CALL (location_type l)
      {
        return symbol_type (token::OP_CALL, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_CALL (const location_type& l)
      {
        return symbol_type (token::OP_CALL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RET (location_type l)
      {
        return symbol_type (token::OP_RET, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RET (const location_type& l)
      {
        return symbol_type (token::OP_RET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_JP (location_type l)
      {
        return symbol_type (token::OP_JP, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_JP (const location_type& l)
      {
        return symbol_type (token::OP_JP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_PUSH (location_type l)
      {
        return symbol_type (token::OP_PUSH, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_PUSH (const location_type& l)
      {
        return symbol_type (token::OP_PUSH, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_POP (location_type l)
      {
        return symbol_type (token::OP_POP, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_POP (const location_type& l)
      {
        return symbol_type (token::OP_POP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RST (location_type l)
      {
        return symbol_type (token::OP_RST, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RST (const location_type& l)
      {
        return symbol_type (token::OP_RST, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RETI (location_type l)
      {
        return symbol_type (token::OP_RETI, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RETI (const location_type& l)
      {
        return symbol_type (token::OP_RETI, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_BIT (location_type l)
      {
        return symbol_type (token::OP_BIT, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_BIT (const location_type& l)
      {
        return symbol_type (token::OP_BIT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RES (location_type l)
      {
        return symbol_type (token::OP_RES, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RES (const location_type& l)
      {
        return symbol_type (token::OP_RES, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_SET (location_type l)
      {
        return symbol_type (token::OP_SET, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_SET (const location_type& l)
      {
        return symbol_type (token::OP_SET, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RLC (location_type l)
      {
        return symbol_type (token::OP_RLC, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RLC (const location_type& l)
      {
        return symbol_type (token::OP_RLC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RL (location_type l)
      {
        return symbol_type (token::OP_RL, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RL (const location_type& l)
      {
        return symbol_type (token::OP_RL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RRC (location_type l)
      {
        return symbol_type (token::OP_RRC, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RRC (const location_type& l)
      {
        return symbol_type (token::OP_RRC, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_RR (location_type l)
      {
        return symbol_type (token::OP_RR, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_RR (const location_type& l)
      {
        return symbol_type (token::OP_RR, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_SLA (location_type l)
      {
        return symbol_type (token::OP_SLA, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_SLA (const location_type& l)
      {
        return symbol_type (token::OP_SLA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_SRA (location_type l)
      {
        return symbol_type (token::OP_SRA, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_SRA (const location_type& l)
      {
        return symbol_type (token::OP_SRA, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_SLL (location_type l)
      {
        return symbol_type (token::OP_SLL, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_SLL (const location_type& l)
      {
        return symbol_type (token::OP_SLL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_SRL (location_type l)
      {
        return symbol_type (token::OP_SRL, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_SRL (const location_type& l)
      {
        return symbol_type (token::OP_SRL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_SWAP (location_type l)
      {
        return symbol_type (token::OP_SWAP, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_SWAP (const location_type& l)
      {
        return symbol_type (token::OP_SWAP, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_EI (location_type l)
      {
        return symbol_type (token::OP_EI, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_EI (const location_type& l)
      {
        return symbol_type (token::OP_EI, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_DI (location_type l)
      {
        return symbol_type (token::OP_DI, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_DI (const location_type& l)
      {
        return symbol_type (token::OP_DI, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_OUT (location_type l)
      {
        return symbol_type (token::OP_OUT, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_OUT (const location_type& l)
      {
        return symbol_type (token::OP_OUT, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_IN (location_type l)
      {
        return symbol_type (token::OP_IN, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_IN (const location_type& l)
      {
        return symbol_type (token::OP_IN, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_EX (location_type l)
      {
        return symbol_type (token::OP_EX, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_EX (const location_type& l)
      {
        return symbol_type (token::OP_EX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OP_EXX (location_type l)
      {
        return symbol_type (token::OP_EXX, std::move (l));
      }
#else
      static
      symbol_type
      make_OP_EXX (const location_type& l)
      {
        return symbol_type (token::OP_EXX, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_U16 (u16 v, location_type l)
      {
        return symbol_type (token::U16, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_U16 (const u16& v, const location_type& l)
      {
        return symbol_type (token::U16, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RS_B (u16 v, location_type l)
      {
        return symbol_type (token::RS_B, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RS_B (const u16& v, const location_type& l)
      {
        return symbol_type (token::RS_B, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RS_C (u16 v, location_type l)
      {
        return symbol_type (token::RS_C, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RS_C (const u16& v, const location_type& l)
      {
        return symbol_type (token::RS_C, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RS_D (u16 v, location_type l)
      {
        return symbol_type (token::RS_D, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RS_D (const u16& v, const location_type& l)
      {
        return symbol_type (token::RS_D, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RS_E (u16 v, location_type l)
      {
        return symbol_type (token::RS_E, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RS_E (const u16& v, const location_type& l)
      {
        return symbol_type (token::RS_E, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RS_H (u16 v, location_type l)
      {
        return symbol_type (token::RS_H, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RS_H (const u16& v, const location_type& l)
      {
        return symbol_type (token::RS_H, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RS_L (u16 v, location_type l)
      {
        return symbol_type (token::RS_L, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RS_L (const u16& v, const location_type& l)
      {
        return symbol_type (token::RS_L, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RS_HL (u16 v, location_type l)
      {
        return symbol_type (token::RS_HL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RS_HL (const u16& v, const location_type& l)
      {
        return symbol_type (token::RS_HL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RS_A (u16 v, location_type l)
      {
        return symbol_type (token::RS_A, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RS_A (const u16& v, const location_type& l)
      {
        return symbol_type (token::RS_A, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RD_BC (u16 v, location_type l)
      {
        return symbol_type (token::RD_BC, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RD_BC (const u16& v, const location_type& l)
      {
        return symbol_type (token::RD_BC, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RD_DE (u16 v, location_type l)
      {
        return symbol_type (token::RD_DE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RD_DE (const u16& v, const location_type& l)
      {
        return symbol_type (token::RD_DE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RD_HL (u16 v, location_type l)
      {
        return symbol_type (token::RD_HL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RD_HL (const u16& v, const location_type& l)
      {
        return symbol_type (token::RD_HL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RD_SP (u16 v, location_type l)
      {
        return symbol_type (token::RD_SP, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RD_SP (const u16& v, const location_type& l)
      {
        return symbol_type (token::RD_SP, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RD_AF (u16 v, location_type l)
      {
        return symbol_type (token::RD_AF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RD_AF (const u16& v, const location_type& l)
      {
        return symbol_type (token::RD_AF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CC_COND (u16 v, location_type l)
      {
        return symbol_type (token::CC_COND, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CC_COND (const u16& v, const location_type& l)
      {
        return symbol_type (token::CC_COND, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FLOAT (float v, location_type l)
      {
        return symbol_type (token::FLOAT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FLOAT (const float& v, const location_type& l)
      {
        return symbol_type (token::FLOAT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LITERAL (std::string v, location_type l)
      {
        return symbol_type (token::LITERAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LITERAL (const std::string& v, const location_type& l)
      {
        return symbol_type (token::LITERAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (std::string v, location_type l)
      {
        return symbol_type (token::IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const std::string& v, const location_type& l)
      {
        return symbol_type (token::IDENTIFIER, v, l);
      }
#endif


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const { return yyla_; }
      symbol_kind_type token () const { return yyla_.kind (); }
      const location_type& location () const { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const unsigned char yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const signed char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
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
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

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
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yylast_ = 242,     ///< Last index in yytable_.
      yynnts_ = 10,  ///< Number of nonterminal symbols.
      yyfinal_ = 3 ///< Termination state number.
    };


    // User arguments.
    assembler::Lexer &lexer;
    assembler::Assembler &assembler;

  };

  inline
  Parser::symbol_kind_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
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
    // Last valid token kind.
    const int code_max = 339;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_FLOAT: // FLOAT
        value.copy< float > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LITERAL: // LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.copy< std::string > (YY_MOVE (that.value));
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
        value.copy< u16 > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_FLOAT: // FLOAT
        value.move< float > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_LITERAL: // LITERAL
      case symbol_kind::S_IDENTIFIER: // IDENTIFIER
        value.move< std::string > (YY_MOVE (s.value));
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
        value.move< u16 > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_kind::clear ()
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

#line 5 "src/assembler/gbparser.ypp"
} // assembler
#line 2898 "src/assembler/gbparser.hpp"




#endif // !YY_YY_SRC_ASSEMBLER_GBPARSER_HPP_INCLUDED
