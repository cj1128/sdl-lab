#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Surface *winSurface = SDL_GetWindowSurface(win);

  SDL_Surface *defaultBMP = LoadImgSurface("hello.bmp");
  SDL_Surface *leftBMP = LoadImgSurface("left.bmp");
  SDL_Surface *rightBMP = LoadImgSurface("right.bmp");
  SDL_Surface *upBMP = LoadImgSurface("up.bmp");
  SDL_Surface *downBMP = LoadImgSurface("down.bmp");

  SDL_Surface *current = defaultBMP;

  SDL_BlitSurface(current, NULL, winSurface, NULL);
  SDL_UpdateWindowSurface(win);

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
        case SDLK_UP:
          current = upBMP;
          break;

        case SDLK_DOWN:
          current = downBMP;
          break;

        case SDLK_LEFT:
          current = leftBMP;
          break;

        case SDLK_RIGHT:
          current = rightBMP;
          break;

        case SDLK_SPACE:
          current = defaultBMP;
          break;
        }
      }
    }

    SDL_BlitSurface(current, NULL, winSurface, NULL);
    SDL_UpdateWindowSurface(win);
  }

  return 0;
}
