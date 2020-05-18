#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  img_texture dots = LoadImg(renderer, "./dots.png");

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }
    }

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    int size = 100;
    SDL_Rect src_rect = { .w = size, .h = size };
    SDL_Rect dst_rect = { .w = size, .h = size };

    for(int y = 0; y < 2; y++) {
      for(int x = 0; x < 2; x++) {
        src_rect.x = x * size;
        src_rect.y = y * size;

        dst_rect.x = x == 0 ? 0 : WIDTH - size;
        dst_rect.y = y == 0 ? 0 : HEIGHT - size;

        SDL_RenderCopy(renderer, dots.texture, &src_rect, &dst_rect);
      }
    }

    SDL_RenderPresent(renderer);
  }

  return 0;
}
