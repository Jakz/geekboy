#ifndef _GB_VMGUI_H_
#define _GB_VMGUI_H_

#include "debugger.h"

#include <ncurses.h>
#include <panel.h>

#include <string>

using namespace std;

class Gui
{
  private:
    char lastMnemonic[128];
    class Debugger *debugger;
  
    u8 bufferIndex;
    bool insertingAddress;
    char buffer[32];

  public:
    void init(Debugger *debugger);
    void draw();
    void end();

    bool keyboard();
  
    u16 offsetPC, lastPC;
};

#endif