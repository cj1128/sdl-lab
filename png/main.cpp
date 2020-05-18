#include "../common.h"

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(800, 600);

  SDL_Surface *winSurface = SDL_GetWindowSurface(win);

  SDL_Surface *png = IMG_Load("test.png");
  if(png == NULL) {
    printf("error: %s\n", IMG_GetError());
    return 1;
  }

  SDL_Surface *convertedBMP = SDL_ConvertSurface(png, winSurface->format, 0);
  if(convertedBMP == NULL) {
    printf("error: %s\n", SDL_GetError());
    return 1;
  }
  SDL_FreeSurface(png);

  SDL_BlitSurface(convertedBMP, NULL, winSurface, NULL);
  SDL_Rect rect = {
    .x = 0,
    .y = 0,
    .w = 1400,
    .h = 800,
  };
  SDL_BlitScaled(convertedBMP, NULL, winSurface, &rect);
  SDL_UpdateWindowSurface(win);

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }
    }
  }

  return 0;
}
