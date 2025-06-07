#pragma once

#include <cstdint>

namespace gb
{
  struct OpcodeGB
  {
	  const char *name;
  
    uint8_t length;
  
    uint8_t cycles[2];
    uint8_t t_states;
  
    uint8_t paramsSign;
  };
  
  enum Conditions
  {
    COND_NZ = 0x00,
    COND_Z = 0x01,
    COND_NC = 0x02,
    COND_C = 0x03,
    COND_PO = 0x04,
    COND_PE = 0x05,
    COND_SP = 0x06,
    COND_SN = 0x07
  };

  enum OpCodes
  {
    OPCODE_NOP = 0x00,
  
    OPCODE_LD_R_R = 0x40,
    OPCODE_LD_R_N = 0x06,
    OPCODE_LD_RR_NN = 0x01,

    OPCODE_LD_BC_A = 0x02,
    OPCODE_LD_DE_A = 0x12,
    OPCODE_LD_NN_A = 0x32,
    OPCODE_LD_A_BC = 0x0A,
    OPCODE_LD_A_DE = 0x1A,
    OPCODE_LD_A_NN = 0x3A,
  
    OPCODE_LD_NN_HL = 0x22,
    OPCODE_LD_HL_NN = 0x2A,
    OPCODE_LD_SP_HL = 0xF9,
  
  
    OPCODE_INC_R = 0x04,
    OPCODE_DEC_R = 0x05,
    OPCODE_INC_RR = 0x03,
    OPCODE_DEC_RR = 0x0B,
  
    OPCODE_ADD_R = 0x80,
    OPCODE_ADC_R = 0x88,
    OPCODE_SUB_R = 0x90,
    OPCODE_SBC_R = 0x98,
    OPCODE_AND_R = 0xA0,
    OPCODE_XOR_R = 0xA8,
    OPCODE_OR_R  = 0xB0,
    OPCODE_CP_R = 0xB8,
  
    OPCODE_ADD_N = 0xC6,
    OPCODE_ADC_N = 0xCE,
    OPCODE_SUB_N = 0xD6,
    OPCODE_SBC_N = 0xDE,
    OPCODE_AND_N = 0xE6,
    OPCODE_XOR_N = 0xEE,
    OPCODE_OR_N = 0xF6,
    OPCODE_CP_N = 0xFE,
  
    OPCODE_RLCA = 0x07,
    OPCODE_RLA = 0x17,
    OPCODE_RRCA = 0x0F,
    OPCODE_RRA = 0x1F,
  
    OPCODE_CPL = 0x2F,
    OPCODE_SCF = 0x37,
    OPCODE_CCF = 0x3F,
  
    OPCODE_DJNZ_N = 0x10,
    OPCODE_JR_N = 0x18,
    OPCODE_JRNZ_N = 0x20,
    OPCODE_JRZ_N = 0x28,
    OPCODE_JRNC_N = 0x30,
    OPCODE_JRC_N = 0x38,
  
    OPCODE_JP_NN = 0xC3,
    OPCODE_JP_CC_NN = 0xC2,
    OPCODE_JP_HL = 0xE9,
  
    OPCODE_CALL_NN = 0xCD,
    OPCODE_CALL_CC_NN = 0xC4,
    OPCODE_RST = 0xC7,
  
    OPCODE_RET = 0xC9,
    OPCODE_RET_CC = 0xC0,
  
    OPCODE_POP = 0xC1,
    OPCODE_PUSH = 0xC5,
  
  
  
    OPCODE_ADD_HL_RR = 0x09,
  
    OPCODE_BITS = 0xCB,
  
    OPCODE_BIT = 0x40,
    OPCODE_RES = 0x80,
    OPCODE_SET = 0xC0,
  
    OPCODE_RLC = 0x00,
    OPCODE_RRC = 0x08,
    OPCODE_RL = 0x10,
    OPCODE_RR = 0x18,
    OPCODE_SLA = 0x20,
    OPCODE_SRA = 0x28,
    OPCODE_SLL = 0x30,
    OPCODE_SRL = 0x38,
  
  
    OPCODE_DI = 0xF3,
    OPCODE_EI = 0xFB,
  
  
    OPCODE_OUT_N_A = 0xD3,
    OPCODE_IN_N_A = 0xDB,
  
    OPCODE_EX_AF_AF = 0x08,
    OPCODE_EXX = 0xD9,
    OPCODE_EX_SP_HL = 0xE3,
    OPCODE_EX_DE_HL = 0xEB,
  
  
    OPCODE_DAA = 0x27,
  
  
    OPCODE_HALT = 0x76
  };

  /* List of mnemonics for the Z80-GB instructions. The position in the array indicates the actual opcode, even though being a CISC, in the actual binary each opcode can be followed by 1 or 2 bytes of data (example 0x011000 -> LD, BC, 4096) */

  class Opcodes
  {
    public:
      /* The CB opcode expects two-byte instructions in the format 0xCBXX with XX from 0x00 to 0xFF, we use a second table */	
      static const char *cbMnemonics[];

      static OpcodeGB opcodesSpecs[];
     
      static uint8_t cpuCycles(uint8_t opcode, uint8_t opcode2, bool branchTaken);
          
      static void visualOpcode(char* buffer, uint8_t d1, uint8_t d2, uint8_t d3);
     
      /* Compared to the complete Z80, some opcodes have changed, others do not exist (those with NO as a comment), and some two-byte instructions
      (those starting with DD- ED- and FD-) do not exist because there are no IX and IY registers
      */
  };
}
