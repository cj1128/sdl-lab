#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      // Clear
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(renderer);

      // red rectangle
      SDL_Rect rect = { WIDTH / 4, HEIGHT / 4, WIDTH / 2, HEIGHT / 2 };
      SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
      SDL_RenderFillRect(renderer, &rect);

      // green rectangle
      SDL_Rect rect2 = { WIDTH / 6, HEIGHT / 6, WIDTH * 2 / 3, HEIGHT * 2 / 3 };
      SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
      SDL_RenderDrawRect(renderer, &rect2);

      // blue horizontal line
      SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
      SDL_RenderDrawLine(renderer, 0, HEIGHT / 2, WIDTH, HEIGHT / 2);

      // vertical line of yellow dots
      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
      for(int i = 0; i < HEIGHT; i += 4) {
        SDL_RenderDrawPoint(renderer, WIDTH / 2, i);
      }

      SDL_RenderPresent(renderer);
    }
  }

  return 0;
}
