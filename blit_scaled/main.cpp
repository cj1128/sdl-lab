#include "../common.h"

#define WIDTH 800
#define HEIGHT 600

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Surface *winSurface = SDL_GetWindowSurface(win);

  SDL_Surface *bmp = LoadImgSurface("hello.bmp");

  SDL_Surface *convertedBMP = SDL_ConvertSurface(bmp, winSurface->format, 0);
  if(convertedBMP == NULL) {
    printf("error: %s\n", SDL_GetError());
    return 1;
  }
  SDL_FreeSurface(bmp);

  SDL_Rect rect = {
    .x = 0,
    .y = 0,
    .w = WIDTH,
    .h = HEIGHT,
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
