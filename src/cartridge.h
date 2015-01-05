#ifndef _GB_CARTRIDGE_H_
#define _GB_CARTRIDGE_H_

#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "utils.h"

namespace gb {

/* flags del gioco */
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

/* questo file dovrebbe preoccuparsi anche di essere interfacciato dallo Z80 per scrivere e leggere valori della ROM.
   Chiaramente lo Z80 può semplicemente richiedere una lettura o una scrittura di un byte su un indirizzo specifico.
   Il comportamento dipende dal tipo di gioco (e di mbc). In linea di massima per l'MBC1:

   0x0000 - 0x3FFF -> primi 16kb della ROM (READ ONLY)
   0x4000 - 0x7FFF -> secondi 16kb della ROM (se senza MBC), altrimenti 16kb del banco selezionato (READ ONLY)
   0xA000 - 0xBFFF -> qui si trova la RAM (2Kb, 8Kb o 32Kb (4 banchi)) (READ/WRITE)

   nel caso di MBC è possibile switchare il secondo banco ROM (quello in 0x4000-0x7FFF) o quello RAM scrivendo in
   questi ADDRESS SPACE:

   0x0000 - 0x1FFF -> RAM Enable: 0x01 ON, 0x00 OFF (in realtà per l'emulazione ce ne frega il giusto)
   0x2000 - 0x3FFF -> ROM Bank number: prende i 5 bit più bassi e ci fa numero di pagina, da selezionare, per i banchi
                      0x00, 0x20, 0x40, 0x60 seleziona un banco con +1 (0x01, 0x21 ...)
   0x4000 - 0x5FFF -> RAM Bank number o upper bits ROM Bank number: 0x00-0x03 per selezionare uno dei 4 banchi di RAM
                      o impostare il bit 5-6 del ROM bank number (per numero di banchi >= 32)
   0x6000 - 0x7FFF -> ROM/RAM bits: 0x00 -> usa il precedente per la ROM (8kb ram, 2mb rom)
									0x01 -> usa il precedente per la RAM (32kb ram, 512kb rom)
									
	gli altri son simili (MBC2, MBC3)
*/

const u8 nintendo_logo[48] =
	{0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
	 0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E, 0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
	 0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC, 0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E};

class Emulator;

/* struttura header di una ROM gb (o gbc), non inizia da 0x000 nel file ma da 0x100 (prima non so cosa c'è) */
struct GB_CART_HEADER
{
	u8 entry_point[4]; /* in genere NOP, JP 0x150 */
	u8 nintendo_logo[48];
	u8 title[11];
	u8 manufacturer[4];
	u8 cgb_flag; /* 0x01 se gameboy color */
	u8 new_license[2]; 
	u8 sgb_flag; /* 0x01 se super gameboy */
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
	/* puntatore ai primi 16kb di ROM (non varia mai a rigore) */
	u8 *rom_bank_0;
	/* puntatore ai 16kb di ROM selezionati dal bank number */
	u8 *rom_bank_1;	
	/* puntatore ai tot kb di RAM (in base al tipo di cart) */
	u8 *ram_bank;
	/* tutta la ROM */
	u8 *rom;
	/* tutta la RAM */
	u8 *ram;
	
	/* true = ram attiva */
	bool ram_enabled;
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
  
  public:
    Cartridge(Emulator& emu);
    ~Cartridge();
  
    /* carica una rom in memoria */
    void load(const char *romName);
    void loadRaw(u8 *code, u32 length);
    void loadRaw(u8 *code, u32 length, u32 offset);
    void dump();
    /* inizializza i valori (tipo banco selezionato, puntatori ai banchi) */
    void init();
  
    /* scrive un valore ad un determinato indirizzo, gestisce il cambio di pagina secondo il protocollo
     dell'MBC interno alla cart */
    void write(u16 address, u8 value);
  
    /* legge un valore ad un determinato indirizzo */
    u8 read(u16 address) const;
  
    void dumpSave();
};
  
}

#endif