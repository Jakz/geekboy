#include "screen.h"

#include <vector>
#include <string>

using namespace std;

void startWithArgs(vector<string> args)
{
  if (args.size() < 2)
    args.push_back("F:\\Misc\\Roms\\Nintendo - GameBoy\\Super Mario Land.gb");
    //args.push_back("tests\\mem_timing.gb");
  
  Screen::i()->execute(args[1]);
}

int main(int argc, char** argv)
{
  vector<string> args;
  for (int i = 0; i < argc; ++i)
    args.push_back(argv[i]);

  startWithArgs(args);

  return 0;
}