#include "cartridge.h"

#include "emulator.h"

using namespace gb;

Cartridge::Cartridge(Emulator* emu) : emu(emu)
{
  status.rom = NULL;
  status.rom_bank_0 = NULL;
  status.rom_bank_1 = NULL;
  status.ram = NULL;
  status.ram_bank = NULL;
  
  status.ram_enabled = false;
  status.flags = 0;
  
  status.current_rom_bank = 1;
  status.current_ram_bank = 0;
}

/* scrive un byte nella ROM */
void Cartridge::write(u16 address, u8 value)
{
	if ((status.flags & MBC_MBC1) == MBC_MBC1)
	{
		/* this enables or less the RAM */
		if (address <= 0x1FFF)
		{	
			if ((value & 0x0A) == 0x0A)
				status.ram_enabled = true;
			else
				status.ram_enabled = false;
		}
    /* this switches ROM bank using 5 lower bits of data */
		else if (address <= 0x3FFF)
		{
      // we select 5 lower bits of the value to set the lower part of the bank
      u8 romBank = value & 0x1F;
				
			// if it's zero we should increment by one
			if (romBank == 0)
				++romBank;
      
      // if we are in ROM banking mode we should keep bit 5-6 from current bank
      // because they are set by writing at 0x4000-0x5FFF
      if (status.rom_banking_mode)
        status.current_rom_bank = (status.current_rom_bank & 0x60) | romBank;
      else
        status.current_rom_bank = romBank;
        
			status.rom_bank_1 = &status.rom[KB16*status.current_rom_bank];
		}
		// in this address space we can either select bit 5-6 for ROM banks or bank 0-3 for RAM
    // according to current banking mode
		else if (address <= 0x5FFF)
		{
			if (status.rom_banking_mode)
			{
        // we mix lower 5 bits of current rom bank with bit 5-6 of the value provided to select rom bank
        status.current_rom_bank = (status.current_rom_bank & 0x1F) | (value & 0x60);
        status.rom_bank_1 = &status.rom[KB16*status.current_rom_bank];
			}
      else
      {
        status.current_ram_bank = value & 0x03;
        status.ram_bank = &status.ram[status.current_ram_bank*KB8];
      }
		}
		// switching from ROM banking to RAM banking
		else if (address <= 0x7FFF)
		{
      status.rom_banking_mode = value & 0x01;
			
      // if we entered ROM banking mode we should restore
      // ram bank to 0 since you cannot address anyone other
			if (status.rom_banking_mode)
      {
        status.ram_bank = status.ram;
        status.current_ram_bank = 0;
      }
		}
    // RAM nella cart (più banchi switchabili nel caso, da 8kb l'uno)
    else if (address >= 0xA000 && address <= 0xBFFF)
    {
      // scrive basandosi sull'offset nel banco di RAM selezionato
      if (status.ram_enabled)
        status.ram_bank[address - 0xA000] = value;
    }
	}
  
  
  else if ((status.flags & MBC_MBC2) == MBC_MBC2)
  {
    /* this enables or less the RAM */
		if (address <= 0x1FFF)
		{	
			if ((value & 0x0A) == 0x0A)
				status.ram_enabled = true;
			else
				status.ram_enabled = false;
		}
    else if (address <= 0x3FFF)
		{
      u8 romBank = value & 0x0F;
      
      status.current_rom_bank = romBank;
      status.rom_bank_1 = &status.rom[status.current_rom_bank*KB16];
    }
    else if (address >= 0xA000 && address <= 0xA1FF)
    {
      // scrive basandosi sull'offset nel banco di RAM selezionato
      if (status.ram_enabled)
        status.ram_bank[address - 0xA000] = value;
    }
  }
  
  
  else if ((status.flags & MBC_MBC5) == MBC_MBC5)
  {
    /* this enables or less the RAM */
		if (address <= 0x1FFF)
		{	
			if ((value & 0x0A) == 0x0A)
				status.ram_enabled = true;
			else
				status.ram_enabled = false;
		}
    // this sets 8 lower bits of 9bits for rom bank choose
    else if (address <= 0x2FFF)
    {
      status.current_rom_bank = (status.current_rom_bank & 0xFF00) | value;
      status.rom_bank_1 = &status.rom[status.current_rom_bank*KB16];
    }
    else if (address <= 0x3FFF)
    {
      status.current_rom_bank = (status.current_rom_bank & 0xFF) | ((((u16)value) & 0x01) << 8);
      status.rom_bank_1 = &status.rom[status.current_rom_bank*KB16];
    }
    else if (address >= 0x4000 && address <= 0x5FFF)
    {
      status.current_ram_bank = value & 0x0F;
      status.ram_bank = &status.ram[status.current_ram_bank*KB8];
    }
    else if (address >= 0xA000 && address <= 0xBFFF)
    {
      // scrive basandosi sull'offset nel banco di RAM selezionato
      if (status.ram_enabled)
        status.ram_bank[address - 0xA000] = value;
    }
  }

}

// legge un byte dalla ROM
u8 Cartridge::read(u16 address) const
{
  // first 16kb -> rom_bank_0
  if (address <= 0x3FFF)
    return status.rom_bank_0[address];
  // second 16k -> rom_bank_1
  else if (address >= 0x4000 && address <= 0x7FFF)
    return status.rom_bank_1[address-0x4000];
  // external ram 8k -> ram_bank
  else if (address >= 0xA000 && address <= 0xBFFF)
    return status.ram_bank[address-0xA000];

	return 0;
}

u32 Cartridge::romSize()
{
	if (header.rom_size <= 0x07)
		return 0x8000 << header.rom_size;
	else
	{
		/* TODO 0x52, 0x53, 0x54 */
	}
	
	return 0;
}

u32 Cartridge::ramSize()
{
	if ((status.flags & MBC_MBC2) == MBC_MBC2)
    return 512;
  
  switch (header.ram_size)
	{
		case 0x01: return 2048;
		case 0x02: return KB8;
		case 0x03: return KB32;
		default:
		case 0x00: return 0;
	}
}

void Cartridge::init(void)
{
	/* TODO: resetta lo status, sonasega */
}

void Cartridge::load(const char *rom_name)
{
	FILE *in = fopen(rom_name, "rb");
	long length = Utils::fileLength(in);
  
  status.fileName = strdup(rom_name);
	
	fseek(in, 0x100, SEEK_SET);
	fread(&header, sizeof(CartridgeHeader), 1, in);
  fseek(in, 0, SEEK_SET);
	
	status.flags = 0x00;
  
  if (header.cgb_flag & 0x80 && rom_name[strlen(rom_name)-1] == 'c')
    emu->mode = MODE_CGB;
	
	/* in base al cart_type assegna le flag della rom */
	if (header.cart_type == 0x00 || header.cart_type == 0x08 || header.cart_type == 0x09)
		status.flags |= MBC_ROM;
	else if (header.cart_type >= 0x01 && header.cart_type <= 0x03)
		status.flags |= MBC_MBC1;
	else if (header.cart_type == 0x05 || header.cart_type == 0x06)
  {
		status.flags |= MBC_MBC2;
    // built-in 512x4bit ram
    status.flags |= MBC_RAM;
  }
  else if (header.cart_type >= 0x19 && header.cart_type <= 0x1E)
    status.flags |= MBC_MBC5;
		
	if (header.cart_type >= 0x0F && header.cart_type <= 0x13)
		status.flags |= MBC_MBC3;
		
	if (header.cart_type == 0x02 || header.cart_type == 0x03 || header.cart_type == 0x08 || header.cart_type == 0x09 ||
	    header.cart_type == 0x10 || header.cart_type == 0x12 || header.cart_type == 0x13 || header.cart_type == 0x1A ||
      header.cart_type == 0x1B)
		status.flags |= MBC_RAM;
	
	if (header.cart_type == 0x03 || header.cart_type == 0x06 || header.cart_type == 0x09 || header.cart_type == 0x0F ||
	    header.cart_type == 0x10 || header.cart_type == 0x13)
		status.flags |= MBC_BATTERY;
		
	if (header.cart_type == 0x0F || header.cart_type == 0x10)
		status.flags |= MBC_TIMER;
	
	char *tmp_name = new char[12];
	memcpy(tmp_name, header.title, 11);
	
	tmp_name[11] = 0x00;
	
  printf("\nLOADING ROM\n");
	printf("-------------\n\n");
	printf("Rom name: %s\n", tmp_name);
	printf("Effective file length: %lu\n", length);
	printf("ROM size: %u\n", romSize());
	printf("RAM size: %u\n", ramSize());
	printf("Destination: %s\n", (header.dest_code == 0x00)?("Japanese"):("Not Japanese"));
	printf("Header CRC: %d\n", header.checksum);
	printf("Cart props %d\n", status.flags);



	if ((status.flags & MBC_ROM) == MBC_ROM)
	{
		printf("ROM allocating %ld bytes\r\n", length);
		
		/* il tipo è ROM -> dimensione max 32kb in due blocchi da 16kb */
		if (length > KB32)
			printf("ROM format invalid!\r\n");

		status.rom_bank_0 = (u8*)malloc(KB16);
		
		fread(status.rom_bank_0, 1, KB16, in);
		
		status.rom_bank_1 = (u8*)malloc(length - KB16);
		
		fread(status.rom_bank_1, 1, length - KB16, in);
	}
  else if ((status.flags & MBC_MBC1) == MBC_MBC1)
	{
		unsigned long n = length / KB16;
		
		/* allochiamo n banks da 16kb */
		printf("MBC1 allocating %lu x 16kb = %ld bytes\r\n", n, length);

		status.rom = (u8*)calloc(length, sizeof(u8));
    fread(status.rom, 1, n*KB16, in);
    
		status.rom_bank_0 = status.rom;
    status.rom_bank_1 = &status.rom[KB16];
	}
  else if ((status.flags & MBC_MBC2) == MBC_MBC2)
  {
    unsigned long n = length / KB16;
		
		/* allochiamo n banks da 16kb */
		printf("MBC2 allocating %lu x 16kb = %ld bytes\r\n", n, length);
    
		status.rom = (u8*)calloc(length, sizeof(u8));
    fread(status.rom, 1, n*KB16, in);
    
		status.rom_bank_0 = status.rom;
    status.rom_bank_1 = &status.rom[KB16];
  }
  else if ((status.flags & MBC_MBC5) == MBC_MBC5)
  {
    unsigned long n = length / KB16;
		
		/* allochiamo n banks da 16kb */
		printf("MBC5 allocating %lu x 16kb = %ld bytes\r\n", n, length);
    
		status.rom = (u8*)calloc(length, sizeof(u8));
    fread(status.rom, 1, n*KB16, in);
    
		status.rom_bank_0 = status.rom;
    status.rom_bank_1 = &status.rom[KB16];
  }
  
  if ((status.flags & MBC_RAM) == MBC_RAM)
  {
    u16 size = ramSize();
    
    status.ram = (u8*)calloc(size, sizeof(u8));
    status.ram_bank = status.ram;
    
    /* allochiamo n banks da 8kb */
		printf("RAM allocating %u x 8kb = %u bytes\r\n", size/KB8, size);
  }
		
	fclose(in);
  
  
  /*if (ramSize() > 0)
  {
    char buffer[128];
    sprintf(buffer, "%s.sav", status.fileName);
    
    FILE *in = fopen(buffer, "rb");
    fread(status.ram, ramSize(), sizeof(u8), in);
    fclose(in);
  }*/
}

void Cartridge::dump()
{
  FILE *out = fopen("rom.gb","wb");

  fwrite(status.rom, KB32, sizeof(u8), out);
  fclose(out);
}

void Cartridge::dumpSave()
{
  u16 size = ramSize();
  
  if (size > 0)
  {
    char buffer[128];
    sprintf(buffer, "%s.sav", status.fileName);
    
    FILE *out = fopen(buffer, "wb");
    fwrite(status.ram, size, sizeof(u8), out);
    fclose(out);
  }
}