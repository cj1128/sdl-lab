#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

#define RECT_SIZE 20

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win, true);

  SDL_Event e;
  bool quit = false;
  float dt = 1.0f / 60.0f;
  float ddPScale = 20000.0f;
  float drag = 12.0f;
  float dX = 0, dY = 0;
  float x = 0, y = 0;
  while(!quit) {
    float ddX = 0, ddY = 0;

    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
        case SDLK_w:
          ddY = -1;
          break;

        case SDLK_s:
          ddY = 1;
          break;

        case SDLK_a:
          ddX = -1;
          break;

        case SDLK_d:
          ddX = 1;
          break;
        }
      }
    }

    ddX *= ddPScale;
    ddX += -dX * drag;
    x += dX * dt + 0.5f * ddX * dt * dt;
    dX += ddX * dt;

    ddY *= ddPScale;
    ddY += -dY * drag;
    y += dY * dt + 0.5f * ddY * dt * dt;
    dY += ddY * dt;

    if(x < 0) {
      dX = 0;
      x = 0;
    } else if(x >= WIDTH - RECT_SIZE) {
      dX = 0;
      x = WIDTH - RECT_SIZE;
    }

    if(y < 0) {
      dY = 0;
      y = 0;
    } else if(y >= HEIGHT - RECT_SIZE) {
      dY = 0;
      y = HEIGHT - RECT_SIZE;
    }

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // item
    SDL_Rect rect
      = { .x = (int)x, .y = (int)y, .w = RECT_SIZE, .h = RECT_SIZE };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
