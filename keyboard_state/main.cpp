#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Surface *winSurface = SDL_GetWindowSurface(win);

  SDL_Surface *defaultBMP = LoadImgSurface("../keyboard/hello.bmp");
  SDL_Surface *leftBMP = LoadImgSurface("../keyboard/left.bmp");
  SDL_Surface *rightBMP = LoadImgSurface("../keyboard/right.bmp");
  SDL_Surface *upBMP = LoadImgSurface("../keyboard/up.bmp");
  SDL_Surface *downBMP = LoadImgSurface("../keyboard/down.bmp");

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
    }

    const uint8_t *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_UP]) {
      current = upBMP;
    } else if(state[SDL_SCANCODE_DOWN]) {
      current = downBMP;
    } else if(state[SDL_SCANCODE_LEFT]) {
      current = leftBMP;
    } else if(state[SDL_SCANCODE_RIGHT]) {
      current = rightBMP;
    } else if(state[SDL_SCANCODE_SPACE]) {
      current = defaultBMP;
    }

    SDL_BlitSurface(current, NULL, winSurface, NULL);
    SDL_UpdateWindowSurface(win);
  }

  return 0;
}
