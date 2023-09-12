#include "opcodes_nes.h"

using namespace nes;

std::array<OpcodeInfo, 256> Opcodes::_opcodes = { {
  
  { {    "mov A, X",      "txa" }, 0x8a, { 2, 0 }, 1, OpcodeParamInfo::None }, // 0x8a

  { {    "mov A, Y",      "tya" }, 0x98, { 2, 0 }, 1, OpcodeParamInfo::None }, // 0x98
  { {    "mov S, X",      "txs" }, 0x9a, { 2, 0 }, 1, OpcodeParamInfo::None }, // 0x9a

  { { "mov X, %.2X", "ldx %.2X" }, 0xa2, { 2, 0 }, 2, OpcodeParamInfo::Imm8 }, // 0xa0
  { { "mov Y, %.2X", "ldy %.2X" }, 0xa0, { 2, 0 }, 2, OpcodeParamInfo::Imm8 }, // 0xa2
  { {    "mov Y, A",      "tay" }, 0xa8, { 2, 0 }, 1, OpcodeParamInfo::None }, // 0xa8
  { { "mov A, %.2X", "lda %.2X" }, 0xa9, { 2, 0 }, 2, OpcodeParamInfo::Imm8 }, // 0xa9
  { {    "mov X, A",      "tax" }, 0xaa, { 2, 0 }, 1, OpcodeParamInfo::None }, // 0xa8

  { {    "mov X, S",      "tsx" }, 0xba, { 2, 0 }, 1 }, // 0xba



} };