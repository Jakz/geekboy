#include "cartridge_nes.h"

#include "opcodes_nes.h"

#include <vector>
#include <cassert>

using namespace nes;

class Mapper0 : public Mapper
{
protected:
  u8 *_prg0, *_prg1;
  u8 *_chr;
  
  u8 readPrg(addr16_t address) override
  {
    if (address >= 0x8000 && address <= 0xBFFF)
      return _prg0[address - 0x8000];
    else if (address >= 0xC000 && address <= 0xFFFF)
      return _prg1[address - 0xC000];
    else
      return 0;
  }

  void writePrg(addr16_t adress, u8 data) override
  {
    // do nothing
    //TODO: prgRam
  }

  u8 readChr(addr16_t address) override
  {
    return _chr[address];
  }

  void writeChr(addr16_t adress, u8 data) override
  {
    // do nothing
  }

public:
  Mapper0(u8* data, size_t prgBanks) :
    _prg0(nullptr), _prg1(nullptr)
  {
    _prg0 = data;

    if (prgBanks == 1)
      _prg1 = _prg0;
    else if (prgBanks == 2)
      _prg1 = data + KB16;
    else
    {
      //TODO: invalid
    }

    _chr = data + KB16 * prgBanks;

    /*for (size_t i = 0; i < KB4; ++i)
    {
      std::string mnemonic = Opcodes::decode(nes_opcode_t(_prg0[i]), _prg0[i + 1]);
      printf("%s\n", mnemonic.c_str());
      i += Opcodes::length(nes_opcode_t(_prg0[i]));
    }*/
  }
};



CartridgeNES::CartridgeNES(const std::string& fileName) : _mapper(nullptr)
{
  auto buffer = Utils::readFile(fileName);

  if (!buffer.empty())
  {
    _romData = std::move(buffer);
    const u8* data = _romData.data();

    /* now buffer is invalid */
    
    auto* header = reinterpret_cast<const RomFileHeader*>(data);

    bool isNes2 = (header->flags2 & RomFileFlag::FormatNes2) == RomFileFlag::FormatNes2;
    mapper_t mapper = (header->flags1 & RomFileFlag::MapperLow) >> 4 | (header->flags2 & RomFileFlag::MapperHigh);
    
    assert(_romData.size() == 16 + header->chrRomSize * KB8 + header->prgRomSize * KB16);

    if (mapper == 0)
    {
      _mapper = new Mapper0(_romData.data() + 16, header->prgRomSize);
    }
  }
}