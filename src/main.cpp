#include "screen.h"

int SDL_main(int argc, char **argv)
{
  Screen::i()->execute();
  

  return 0;
}

#ifdef __linux__
int main(int argc, char **argv)
{
  SDL_main(argc,argv);
}
#endif