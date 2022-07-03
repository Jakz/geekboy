#include "vmgui.h"

#include <cstring>

#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#include "emulator.h"

template<class T>
T MIN(T a, T b) {
  return a < b ? a : b;
}

using namespace std;

#define R_BYTES (totalRamBytes)
#define ROM_ROWS (height-10)

static WINDOW *wRegisters, *wRom, *wRam, *wOpt, *wPorts, *wHL;
static PANEL *pRegs, *pRom, *pRam, *pOpt, *pPorts, *pHL;

static u16 width;
static u16 height;
static u16 totalRamBytes;

static const u16 REGS_ROWS = 4;
static const u16 OPT_ROWS = 4;
static u16 PORT_ROWS;
static u16 STACK_ROWS;

void Gui::init(Debugger *debugger)
{
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
  
  printf ("lines %d\n", w.ws_row);
  printf ("columns %d\n", w.ws_col);
  
  width = w.ws_col;
  height = w.ws_row;
  
  initscr();
	keypad(stdscr, TRUE);
	noecho();
	cbreak();
  curs_set(0);
  
  u16 sideWidth = width/2 + 16;
  u16 romWidth = width/2 - 16;
  
  totalRamBytes = ((sideWidth - 4 - 6 - 3) + 1) / 3;
  
  PORT_ROWS = MIN((height - REGS_ROWS - OPT_ROWS) / 2, 12);
  
  if (totalRamBytes < 128 && totalRamBytes >= 64) totalRamBytes = 64;
  else if (totalRamBytes < 64 && totalRamBytes >= 32) totalRamBytes = 32;
  else if (totalRamBytes < 32 && totalRamBytes >= 16) totalRamBytes = 16;
  else if (totalRamBytes < 16 && totalRamBytes >= 8) totalRamBytes = 8;
  else totalRamBytes = 4;

  STACK_ROWS = height - REGS_ROWS - OPT_ROWS;
  
  wRegisters = newwin(REGS_ROWS, COLS, 0, 0);
	wRom = newwin(height - REGS_ROWS - OPT_ROWS, width/2 - 16, 4, 0);
	wRam = newwin(STACK_ROWS, sideWidth, 4, romWidth);
	wOpt = newwin(4, width, height-4, 0);
  wPorts = newwin(PORT_ROWS, sideWidth, height - OPT_ROWS - PORT_ROWS, romWidth);
  //wHL = newwin(7, COLS/2 - 30, 4, COLS/2 + 22 );
  
  pRegs = new_panel(wRegisters);
	pRom = new_panel(wRom);
	pRam = new_panel(wRam);
	pOpt = new_panel(wOpt);
  pPorts = new_panel(wPorts);
  //pHL = new_panel(wHL);
	
  offsetPC = 0;
  lastPC = 0;
	strcpy(lastMnemonic, "none");
  
  memset(buffer, 0, 32);
  insertingAddress = false;
  bufferIndex = 0;

  this->debugger = debugger;
}

void Gui::draw()
{
	//Registers r = *cpu->regs();
  
  wclear(wRom);
	wclear(wRam);
	wclear(wOpt);
  wclear(wPorts);
  //wclear(wHL);
	
  box(wRegisters, 0, 0);
	box(wRom, 0, 0);
	box(wRam, 0, 0);
	box(wOpt, 0, 0);
  box(wPorts, 0, 0);
  //box(wHL, 0, 0);
  
  const char *cpuName = debugger->cpuName;
  mvwprintw(wRegisters, 0, width - 1 - 2 - static_cast<int>(strlen(cpuName)), "[%s]", cpuName);
  
  mvwprintw(wRegisters, 0, 1, "[Registers]");
	mvwprintw(wRom, 0, 1, "[ROM]");
	mvwprintw(wRam, 0, 1, "[Stack]");
	mvwprintw(wOpt, 0, 1, "[Commands]");
  mvwprintw(wPorts, 0, 1, "[Ports]");
  //mvwprintw(wHL, 0, 1, "[HL]");

  
  char ibuf[256];
  debugger->registerVisual(ibuf, 0);
  mvwprintw(wRegisters, 1, 2, ibuf);
  debugger->registerVisual(ibuf, 1);
  mvwprintw(wRegisters, 2, 2, ibuf);

  sprintf(ibuf, "CYCLES %llu", debugger->cycles());
  mvwprintw(wRegisters, 2, width - 2 - static_cast<int>(strlen(ibuf)), ibuf);

  
  // ROM view
  u16 startPC = debugger->PC();
  
  DataWidth aw = debugger->widthAddress;
  int taw = aw + 3;
  DataWidth dw = debugger->widthData;
  int tdw = dw;
  DataWidth iw = debugger->widthMaxInstruction;
  
  for (int i = 0; i < ROM_ROWS; ++i)
  {
    mvwprintw(wRom, 1+i, 4, "0x%.*X", aw, startPC);
   
    u8 opcodes[3];

    opcodes[0] = debugger->read(startPC);
    u8 length = debugger->instructionLength(opcodes[0]);
    
    if (length == 0) length = 1;
    
    for (int j = 0; j < length; ++j)
    {
      if (startPC == debugger->PC())
        mvwprintw(wRom, 1+i, 2+1, ">");
      if (debugger->hasBreakPoint(startPC))
        mvwprintw(wRom, 1+i, 2, "*");
      
      if (j > 0)
        opcodes[j] = debugger->read(startPC+j);
      
      mvwprintw(wRom, 1+i, 4+taw+1+(j*2), "%.2X", opcodes[j]);
    }
    
    ibuf[0] = '\0';
    debugger->instructionVisual(ibuf, opcodes[0], opcodes[1], opcodes[2]);
    mvwprintw(wRom, 1+i, 4+(taw+1)+(iw+4)+(2), ibuf);
    
    startPC += length;
  }

  
  // STACK VIEW
  s32 base = 0x00;//debugger->SP() - (STACK_ROWS/2)*8;
  //base -= base%totalRamBytes;
	for (int i = 0; i < STACK_ROWS; ++i)
	{
    //u16 base = /*r.SP - (r.SP%8)*/0xC000 - (R_COLS-1)*R_BYTES+i*R_BYTES;
    s32 row = base + i*R_BYTES;

    if (row >= 0 && row <= 0xFFFF)
    {    
      mvwprintw(wRam, 1+i, 2, "0x%.*X", aw, row);
    
      for (int j = 0; j < R_BYTES; ++j)
      {
        if (row + j == debugger->SP())
        {
          mvwprintw(wRam, 1+i, (taw+3)+(j*3), "[");
        }
        
        mvwprintw(wRam, 1+i, taw+3+1+(j*3), "%.*X", dw, debugger->read(row + j));
      }
    }
	}
  
  // HL VIEW
  /*base = r.HL.HL - 2.5*8;
  base -= base%8;
	for (int i = 0; i < 5; ++i)
	{
    //u16 base = 0xC000 - (R_COLS-1)*R_BYTES+i*R_BYTES;
    s32 row = base + i*R_BYTES;
    
    if (row >= 0 && row <= 0xFFFF)
    {    
      mvwprintw(wHL, 1+i, 2, "0x%.4X", row);
      
      for (int j = 0; j < R_BYTES; ++j)
      {
        if (row + j == r.HL.HL)
        {
          mvwprintw(wHL, 1+i, 10+(j*3), "[");
        }
        
        mvwprintw(wHL, 1+i, 10+1+(j*3), "%.2X", mem->read(row + j));
      }
    }
	}*/
  
  
  // PORTS VIEW
  int row = 0, col = 0;
  for (int i = 0; i < debugger->ports.size(); ++i)
  {
    const DebuggerPort &port = debugger->ports.at(i);
    mvwprintw(wPorts, 1+row, 2+col*(taw+tdw+9), "0x%.*X %.*X %s", aw, port.address, dw, debugger->read(port.address),port.name);
    ++row;
    
    if ((i+1)%(PORT_ROWS-2) == 0)
    {
      ++col;
      row = 0;
    }
  }
  
  
	
	mvwprintw(wOpt, 1, 2, "S step instruction");
  mvwprintw(wOpt, 1, 25, "B breakpoint");
  mvwprintw(wOpt, 2, 25, "D run to breakpoint");
	mvwprintw(wOpt, 2, 2, "R run");
  mvwprintw(wOpt, 1, 50, "Q quit");
	mvwprintw(wOpt, 1, COLS-40, "Last Instruction: %s", lastMnemonic);
  
  if (insertingAddress)
  {
    mvwprintw(wOpt, 2, COLS-40, ">%s", buffer);
    mvwprintw(wOpt, 2, 25, "X cancel");
  }
	
	//mvprintw(23, COLS - 16, "-:[Z80-GB VM]:-");
	
	update_panels();
	doupdate();
	//refresh();
}

bool Gui::keyboard()
{
  int c = getch();
  
  if (!insertingAddress)
  {    
    switch (c)
    {
      case 'q':
      case 'Q':
        return true;
      case 's':
      case 'S':
      {
        lastPC = debugger->PC();
        //debugger->step();
        debugger->step();
        
        //visualOpcode(lastMnemonic, lastPC);
        break;
      }
      case 'd':
      case 'D':
      {
        lastPC = debugger->PC();
        debugger->run(16384);
        //visualOpcode(lastMnemonic, lastPC);
        break;
      }
      case 'f':
      case 'F':
      {
        debugger->run();
      } 
      case 'r':
      case 'R':
      {
        debugger->run();
        break;
      }
      case 'b':
      case 'B':
      {
        insertingAddress = true;
        bufferIndex = 0;
        break;
      }
    }
  }
  else
  {
    fflush(stdout);
    
    if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f'))
    {
      buffer[bufferIndex++] = c;
    }
    else if (c == 127) // BACKSPACE
    {
      if (bufferIndex > 0)
        buffer[--bufferIndex] = 0;
    }
    else if (c == 'x') // ESCAPE
    {
      insertingAddress = false;
      memset(buffer, 0, 32);
    }
    else if (c == '\n')
    {
      u16 address = strtol(buffer, NULL, 16);
      
      if (address >= 0 && address <= 0xFFFF)
      {
        debugger->toggleBreakPoint(address);
      }
      insertingAddress = false;
      memset(buffer, 0, 32);
    }
  }
  
  return false;

}

void Gui::end()
{
	endwin();
}

