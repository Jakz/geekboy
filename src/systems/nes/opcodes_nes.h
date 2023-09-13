#pragma once

#include "utils.h"

#include <array>

namespace nes
{
  enum class nes_opcode_t : u8
  {
    /* MOV R, R */
    MOV_Y_A = 0xA8,
    MOV_X_A = 0xAA,
    MOV_X_S = 0xBA,
    MOV_A_Y = 0x98,
    MOV_A_X = 0x8A,
    MOV_S_X = 0x9A,

    /* MOV R, NN */
    MOV_A_NN = 0xA9,
    MOV_X_NN = 0xA2,
    MOV_Y_NN = 0xA0,

    /* MOV R, [NN] */
    MOV_A_PTR_NN = 0xA5,
    MOV_X_PTR_NN = 0xA6,
    MOV_Y_PTR_NN = 0xA4,

    /* MOV R, [NN+R] */
    MOV_A_PTR_NN_X = 0xB5,
    MOV_X_PTR_NN_Y = 0xB6,
    MOV_Y_PTR_NN_X = 0xB4,

    /* MOV R, [NNNN] */
    MOV_A_PTR_NNNN = 0xAD,
    MOV_X_PTR_NNNN = 0xAE,
    MOV_Y_PTR_NNNN = 0xAC,

    /* PUSH / PULL */
    PUSH_A = 0x48,
    PUSH_P = 0x08,
    POP_A = 0x68,
    POP_P = 0x28,

    UNKNOWN = 0x00,
  };

  enum class OpcodeParamInfo : u8
  {
    None,
    Imm8,
    Addr8,
  };

  struct OpcodeInfo
  {
    const char* mnemonics[2];
    nes_opcode_t opcode;
    u8 cycles[2];
    u8 length;
    OpcodeParamInfo params;
  };

  class Opcodes
  {
  protected:
    static std::array<OpcodeInfo, 256> _opcodes;

  public:

    static instruction_len_t length(nes_opcode_t op);
    static cycle_count_t cyclesFor(nes_opcode_t op);

    static std::string decode(nes_opcode_t op, u8 d1);
  };
  
}