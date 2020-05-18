#include "../common.h"

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(640, 480);

  SDL_Renderer *renderer = InitRenderer(win);

  img_texture texture = LoadImg(renderer, "hello.bmp");

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

      SDL_RenderCopy(renderer, texture.texture, NULL, NULL);

      SDL_RenderPresent(renderer);
    }
  }

  return 0;
}
