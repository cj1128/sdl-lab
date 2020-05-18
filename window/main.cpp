#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("My Window",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    640,
    480,
    SDL_WINDOW_SHOWN);
  if(win == NULL) {
    printf("error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Surface *winSurface = SDL_GetWindowSurface(win);

  SDL_Surface *bmp = SDL_LoadBMP("./hello.bmp");
  if(bmp == NULL) {
    printf("error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_BlitSurface(bmp, NULL, winSurface, NULL);
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
