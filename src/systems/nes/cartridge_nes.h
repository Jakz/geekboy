#pragma once

#include "utils.h"

#include <string>

namespace nes
{
  
  enum RomFileFlag
  {
    Mirroring    = 0b00000001,
    Battery      = 0b00000010,
    Trainer      = 0b00000100,
    FourScreen   = 0b00001000,
    MapperLow    = 0b11110000,
    
    VsUniSystem  = 0b00000001,
    PlayChoice10 = 0b00000010,
    FormatNes2   = 0b00001100,
    MapperHigh   = 0b11110000,
  };

  using mapper_t = uint16_t;
  
  struct RomFileHeader
  {
    char magic[4];
    u8 prgRomSize;
    u8 chrRomSize;
    u8 flags1;
    u8 flags2;
  };

  class Mapper
  {
    virtual u8 readPrg(addr16_t address) = 0;
    virtual void writePrg(addr16_t adress, u8 data) = 0;

    virtual u8 readChr(addr16_t address) = 0;
    virtual void writeChr(addr16_t adress, u8 data) = 0;
  };
  
  class CartridgeNES
  {
  protected:
    std::vector<u8> _romData;
    Mapper* _mapper;
    
  public:
    CartridgeNES(const std::string& fileName);
  };
}