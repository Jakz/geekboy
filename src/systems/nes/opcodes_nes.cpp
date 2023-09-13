#include "opcodes_nes.h"


using namespace nes;

using op = nes::nes_opcode_t;

cycle_count_t Opcodes::cyclesFor(nes_opcode_t op)
{
  return _opcodes[size_t(op)].cycles[0];
}

instruction_len_t Opcodes::length(nes_opcode_t op)
{
  return _opcodes[size_t(op)].length;
}

std::array<OpcodeInfo, 256> Opcodes::_opcodes = { {

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x00
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x01
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x02
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x03
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x04
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x05
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x06
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x07
  { {           "push P",         "php" },          op::PUSH_P, { 3, 0 }, 1,  OpcodeParamInfo::None }, // 0x08
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x09
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x0a
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x0b
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x0c
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x0d
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x0e
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x0f
  
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x10
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x11
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x12
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x13
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x14
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x15
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x16
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x17
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x18
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x19
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x1a
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x1b
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x1c
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x1d
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x1e
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x1f

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x20
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x21
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x22
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x23
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x24
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x25
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x26
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x27
  { {            "pop P",         "plp" },           op::POP_P, { 4, 0 }, 1,  OpcodeParamInfo::None }, // 0x28
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x29
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x2a
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x2b
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x2c
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x2d
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x2e
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x2f

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x30
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x31
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x32
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x33
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x34
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x35
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x36
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x37
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x38
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x39
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x3a
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x3b
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x3c
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x3d
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x3e
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x3f

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x40
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x41
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x42
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x43
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x44
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x45
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x46
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x47
  { {           "push A",         "pha" },          op::PUSH_A, { 3, 0 }, 1,  OpcodeParamInfo::None }, // 0x48
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x49
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x4a
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x4b
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x4c
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x4d
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x4e
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x4f

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x50
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x51
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x52
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x53
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x54
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x55
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x56
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x57
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x58
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x59
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x5a
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x5b
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x5c
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x5d
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x5e
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x5f

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x60
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x61
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x62
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x63
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x64
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x65
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x66
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x67
  { {            "pop A",         "pla" },           op::POP_A, { 4, 0 }, 1,  OpcodeParamInfo::None }, // 0x68
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x69
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x6a
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x6b
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x6c
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x6d
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x6e
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x6f

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x70
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x71
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x72
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x73
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x74
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x75
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x76
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x77
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x78
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x79
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x7a
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x7b
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x7c
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x7d
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x7e
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x7f

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x80
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x81
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x82
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x83
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x84
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x85
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x86
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x87
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x88
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x89
  { {         "mov A, X",         "txa" },         op::MOV_A_X, { 2, 0 }, 1,  OpcodeParamInfo::None }, // 0x8a
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x8b
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x8c
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x8d
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x8e
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x8f

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x90
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x91
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x92
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x93
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x94
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x95
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x96
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x97
  { {         "mov A, Y",         "tya" },         op::MOV_A_Y, { 2, 0 }, 1,  OpcodeParamInfo::None }, // 0x98
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x99
  { {         "mov S, X",         "txs" },         op::MOV_S_X, { 2, 0 }, 1,  OpcodeParamInfo::None }, // 0x9a
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x9b
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x9c
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x9d
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x9e
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0x9f

  { {      "mov Y, %.2X",    "ldy %.2X" },        op::MOV_Y_NN, { 2, 0 }, 2,  OpcodeParamInfo::Imm8 }, // 0xa0
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xa1
  { {      "mov X, %.2X",    "ldx %.2X" },        op::MOV_X_NN, { 2, 0 }, 2,  OpcodeParamInfo::Imm8 }, // 0xa2
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xa3
  { {    "mov Y, [%.2X]",    "ldy %.2X" },    op::MOV_Y_PTR_NN, { 3, 0 }, 2, OpcodeParamInfo::Addr8 }, // 0xa4
  { {    "mov A, [%.2X]",    "lda %.2X" },    op::MOV_A_PTR_NN, { 3, 0 }, 2, OpcodeParamInfo::Addr8 }, // 0xa5
  { {    "mov X, [%.2X]",    "ldx %.2X" },    op::MOV_X_PTR_NN, { 3, 0 }, 2, OpcodeParamInfo::Addr8 }, // 0xa6
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xa7
  { {         "mov Y, A",         "tay" },         op::MOV_Y_A, { 2, 0 }, 1,  OpcodeParamInfo::None }, // 0xa8
  { {      "mov A, %.2X",    "lda %.2X" },        op::MOV_A_NN, { 2, 0 }, 2,  OpcodeParamInfo::Imm8 }, // 0xa9
  { {         "mov X, A",         "tax" },         op::MOV_X_A, { 2, 0 }, 1,  OpcodeParamInfo::None }, // 0xaa
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xab
  { {      "mov Y, %.4X",    "LDY %.4X" }, op::UNKNOWN, { 4, 0 }, 3, OpcodeParamInfo::None }, // 0xac
  { {      "mov A, %.4X",    "LDA %.4X" }, op::UNKNOWN, { 4, 0 }, 3, OpcodeParamInfo::None }, // 0xad
  { {      "mov X, %.4X",    "LDX %.4X" }, op::UNKNOWN, { 4, 0 }, 3, OpcodeParamInfo::None }, // 0xae
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xaf

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xb0
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xb1
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xb2
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xb3
  { {  "mov Y, [%.2X+X]", "ldy %.2X, X" },  op::MOV_Y_PTR_NN_X, { 4, 0 }, 2, OpcodeParamInfo::Addr8 }, // 0xb4
  { {  "mov A, [%.2X+X]", "lda %.2X, X" },  op::MOV_A_PTR_NN_X, { 4, 0 }, 2, OpcodeParamInfo::Addr8 }, // 0xb5
  { {  "mov X, [%.2X+Y]", "ldx %.2X, Y" },  op::MOV_X_PTR_NN_Y, { 4, 0 }, 2, OpcodeParamInfo::Addr8 }, // 0xb6
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xb7
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xb8
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xb9
  { {         "mov X, S",         "tsx" },         op::MOV_X_S, { 2, 0 }, 1,  OpcodeParamInfo::None }, // 0xba
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xbb
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xbc
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xbd
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xbe
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xbf

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xc0
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xc1
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xc2
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xc3
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xc4
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xc5
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xc6
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xc7
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xc8
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xc9
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xca
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xcb
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xcc
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xcd
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xce
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xcf

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xd0
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xd1
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xd2
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xd3
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xd4
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xd5
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xd6
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xd7
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xd8
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xd9
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xda
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xdb
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xdc
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xdd
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xde
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xdf

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xe0
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xe1
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xe2
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xe3
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xe4
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xe5
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xe6
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xe7
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xe8
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xe9
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xea
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xeb
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xec
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xed
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xee
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xef

  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xf0
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xf1
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xf2
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xf3
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xf4
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xf5
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xf6
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xf7
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xf8
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xf9
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xfa
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xfb
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xfc
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xfd
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xfe
  { { "unk", "unk" }, op::UNKNOWN, { 0, 0 }, 1, OpcodeParamInfo::None }, // 0xff
} };


std::string Opcodes::decode(nes_opcode_t op, u8 d1)
{
  const auto& info = _opcodes[size_t(op)];

  char buffer[256];

  if (info.params == OpcodeParamInfo::None)
    return info.mnemonics[0];
  else if (info.params == OpcodeParamInfo::Imm8 || info.params == OpcodeParamInfo::Addr8)
  {
    sprintf(buffer, info.mnemonics[0], d1);
    return buffer;
  }
  else
    return "unknown";
    
  
}