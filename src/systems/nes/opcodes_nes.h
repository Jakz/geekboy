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

    /* PUSH / PULL */
    PUSH_A = 0x48,
    PUSH_P = 0x08,
    POP_A = 0x68,
    POP_P = 0x28,
  };

  enum class OpcodeParamInfo : u8
  {
    None,
    Imm8,
  };

  struct OpcodeInfo
  {
    const char* mnemonics[2];
    u8 opcode;
    u8 cycles[2];
    u8 length;
    OpcodeParamInfo params;
  };

  class Opcodes
  {
  protected:
    static std::array<OpcodeInfo, 256> _opcodes;

  public:
  };
  
}