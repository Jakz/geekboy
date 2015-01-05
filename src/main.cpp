#include "screen.h"

#include <vector>
#include <string>

using namespace std;

void startWithArgs(const vector<string>& args)
{
  if (args.size() < 2)
    return;
  
  
  
  Screen::i()->execute(args[1]);
}

int SDL_main(int argc, char **argv)
{
  vector<string> args;
  for (int i = 0; i < argc; ++i)
    args.push_back(argv[i]);

  startWithArgs(args);

  return 0;
}

#ifdef __linux__
int main(int argc, char **argv)
{
  SDL_main(argc,argv);
}
#endif