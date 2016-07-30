#ifndef _GB_CARTRIDGE_H_
#define _GB_CARTRIDGE_H_

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "utils.h"
#include "rtc.h"

namespace gb {

/* flags for ROM */
#define MBC_ROM 0x01
#define MBC_RAM 0x02
#define MBC_BATTERY 0x04
#define MBC_TIMER 0x08
#define MBC_RUMBLE 0x10
#define MBC_MBC1 0x20
#define MBC_MBC2 0x40
#define MBC_MBC3 0x80
#define MBC_MBC4 0x100
#define MBC_MBC5 0x200
#define MBC_SIMPLE 0x400

/*
  questo file dovrebbe preoccuparsi anche di essere interfacciato dallo Z80 per scrivere e leggere valori della ROM.
  Chiaramente lo Z80 può semplicemente richiedere una lettura o una scrittura di un byte su un indirizzo specifico.
  Il comportamento dipende dal tipo di gioco (e di mbc). In linea di massima per l'MBC1:

  0x0000 - 0x3FFF -> first 16kb of ROM (READ ONLY)
  0x4000 - 0x7FFF -> second 16kb of ROM (if without MBC), otherwise 16kb of the currently selected bank (READ ONLY)
  0xA000 - 0xBFFF -> here is the RAM (2Kb, 8Kb o 32Kb (4 banks)) (READ/WRITE)

  when there is MBC it is possible to switch the second ROM bank (address 0x4000-0x7FFF) or the RAM bank by writing in
  the following address spaces:

  0x0000 - 0x1FFF -> RAM Enable: 0x01 ON, 0x00 OFF (for emulation this is irrelevent)
  0x2000 - 0x3FFF -> ROM Bank number: takes 5 lower bits to compute page number to select, for banks
                      0x00, 0x20, 0x40, 0x60 value is adjusted by +1 (0x01, 0x21 ...)
  0x4000 - 0x5FFF -> RAM Bank number or upper bits ROM Bank number: 0x00-0x03 to select one of 4 RAM banks
                      or to set bit 5-6 of ROM bank number (per bank amount >= 32)
  0x6000 - 0x7FFF -> ROM/RAM bits: 0x00 -> usa il precedente per la ROM (8kb ram, 2mb rom)
									0x01 -> usa il precedente per la RAM (32kb ram, 512kb rom)
									
  others are similar (MBC2, MBC3)
*/

const u8 nintendo_logo[48] =
	{0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
	 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
	 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};

class Emulator;

/* struttura header di una ROM gb (o gbc), non inizia da 0x000 nel file ma da 0x100 (prima non so cosa c'è) */
struct GB_CART_HEADER
{
	u8 entry_point[4]; /* usually NOP, JP 0x150 */
	u8 nintendo_logo[48];
	u8 title[11];
	u8 manufacturer[4];
	u8 cgb_flag; /* 0x01 if gameboy color */
	u8 new_license[2]; 
	u8 sgb_flag; /* 0x01 if super gameboy */
	u8 cart_type;
	u8 rom_size; /* 0x00 - 0x07, 0x52 - 0x54 */
	u8 ram_size; /* 0x00 - 0x03 */
	u8 dest_code;
	u8 old_license;
	u8 version;
	u8 checksum;
	u8 global_checksum[2];
};

struct GB_CART_STATUS
{
	/* pointer to first 16kb of ROM */
	u8 *rom_bank_0;
	/* pointer to 16kb of ROM selected by MBC */
	u8 *rom_bank_1;	
	/* puntatore ai tot kb di RAM (in base al tipo di cart) */
	u8 *ram_bank;
  
	/* whole ROM */
	u8 *rom;
	/* whole RAM */
	u8 *ram;
  /* all RTC registers */
  u8 *rtc;
	
	/* true = ram attiva */
	bool ram_enabled;
  /* true = writes are on RTC registers, not on RAM */
  bool rtc_override;
	/* true = 32kb RAM, false = 2mb ROM (indica i 2 bit 5-6 cosa contano) */
	bool rom_banking_mode;
  
  u16 current_rom_bank;
  u8 current_ram_bank;
  
	u32 flags;
  
  char *fileName;
};

class Cartridge
{
private:
  Emulator& emu;

  GB_CART_HEADER header;
  GB_CART_STATUS status;

  u32 romSize();
  u32 ramSize();
  
  RTC rtc;
  
public:
  Cartridge(Emulator& emu);
  ~Cartridge();

  /* carica una rom in memoria */
  void load(const char *romName);
  void dump();
  /* inizializza i valori (tipo banco selezionato, puntatori ai banchi) */
  void init();

  /* scrive un valore ad un determinato indirizzo, gestisce il cambio di pagina secondo il protocollo
   dell'MBC interno alla cart */
  void write(u16 address, u8 value);

  /* legge un valore ad un determinato indirizzo */
  u8 read(u16 address) const;

  void loadRaw(u8 *code, u32 length);

  void dumpSave();
};
  
}

#endif