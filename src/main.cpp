#include "screen.h"

#include <vector>
#include <string>

using namespace std;

void startWithArgs(vector<string> args);
void end();

#ifdef __cplusplus

#include "systems/nes/cartridge_nes.h"

extern "C"
{
  int main(int argc, char** argv)
  {
    /*std::string path = R"(F:\Misc\Roms\Nintendo - NES\Super Mario Bros. 1.nes)";
    nes::CartridgeNES cart(path);
    return 0;*/
    
    vector<string> args;
    for (int i = 0; i < argc; ++i)
      args.push_back(argv[i]);

    Screen::i()->init(gb::EmuSpec{ 160, 144 });

    startWithArgs(args);
    //Screen::i()->load("F:\\Misc\\Roms\\Nintendo - GameBoy\\Super Mario Land.gb");
    //Screen::i()->emulator()->mute(true);
    Screen::i()->execute();
    Screen::i()->cleanup();

    end();
   
    return 0;
  }
}

#endif

#ifndef _WIN32

void startWithArgs(vector<string> args)
{
  /*if (args.size() < 2)
    args.push_back("F:\\Misc\\Roms\\Nintendo - GameBoy\\Super Mario Land.gb");
  */
  Screen::i()->init(gb::EmuSpec{ 160, 144 });
  Screen::i()->execute();
  Screen::i()->load(args[1].c_str());
  Screen::i()->cleanup();
}

void end()
{
  
}

#else

#include "SDL.h"
#include "SDL_syswm.h"

#include "resource.h"

#include <winuser.h>
#include <ShObjIdl.h>

#include "BearLibTerminal.h"

void messageHook(void* userdata, void* hWnd, unsigned int message, Uint64 wParam, Sint64 lParam);

#include "systems/gb/debugger_gb.h"

gb::Debugger debugger;

void startWithArgs(vector<string> args)
{
  terminal_open();
  terminal_set("window.size=100x50; font: consola.ttf, size=10; window.title='Debugger'");
  terminal_refresh();
   
  SDL_SetWindowsMessageHook(messageHook, nullptr);

  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);
  SDL_GetWindowWMInfo(Screen::i()->window(), &wmInfo);
  HWND hwnd = wmInfo.info.win.window;

  HMENU menu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU1));

  SetMenu(hwnd, menu);
  SetWindowTextW(hwnd, L"Geekboy");
}

void end()
{
  terminal_close();
}


bool toggleMenuCheckbox(HWND hwnd, UINT resource)
{
  HMENU hmenu = GetMenu(hwnd);

  MENUITEMINFO menuItem = { 0 };
  menuItem.cbSize = sizeof(MENUITEMINFO);
  menuItem.fMask = MIIM_STATE;

  GetMenuItemInfo(hmenu, ID_EMULATION_MUTE, FALSE, &menuItem);

  if (menuItem.fState == MFS_CHECKED)
    menuItem.fState = MFS_UNCHECKED;
  else
    menuItem.fState = MFS_CHECKED;
  
  SetMenuItemInfo(hmenu, ID_EMULATION_MUTE, FALSE, &menuItem);

  return menuItem.fState == MFS_CHECKED;
}

void messageHook(void* userdata, void* hWnd, unsigned int message, Uint64 wParam, Sint64 lParam)
{
  if (message == WM_COMMAND)
  {
    if (wParam == MENU_EXIT)
      exit(0);
    else if (wParam == ID_FILE_LOAD)
    {
      IFileOpenDialog* pFileOpenDialog;
      HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFileOpenDialog));
      
      COMDLG_FILTERSPEC filterSpec[] = { { L"Game Boy roms", L"*.gb; *.gbc" } };
      pFileOpenDialog->SetFileTypes(1, filterSpec);

      hr = pFileOpenDialog->Show(NULL);
      if (FAILED(hr)) 
      {
        pFileOpenDialog->Release();
      }

      IShellItem* pSelectedItem;
      hr = pFileOpenDialog->GetResult(&pSelectedItem);
      
      if (SUCCEEDED(hr)) {
        PWSTR filePath;
        hr = pSelectedItem->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

        char utfName[256];
        wcstombs(utfName, filePath, 500);

        Screen::i()->load(utfName);

        debugger.setEmulator(Screen::i()->emulator());
        debugger.refresh();
        
        Screen::i()->execute();
        
        if (SUCCEEDED(hr)) {
          // Handle the selected file path (in filePath)
          CoTaskMemFree(filePath);
        }
        pSelectedItem->Release();
      }
    }
    else if (wParam == ID_EMULATION_MUTE)
    {
      HWND hwnd = (HWND)hWnd;
      HMENU hmenu = GetMenu(hwnd);

      MENUITEMINFO menuItem = { 0 };
      menuItem.cbSize = sizeof(MENUITEMINFO);
      menuItem.fMask = MIIM_STATE;

      bool checked = toggleMenuCheckbox((HWND)hWnd, ID_EMULATION_MUTE);
      Screen::i()->emulator()->mute(!checked);
    }
  }
}

#endif 