#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  img_texture img = LoadImg(renderer, "hello.bmp");

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
      SDL_RenderClear(renderer);

      // top left
      SDL_Rect top_left = { 0, 0, WIDTH / 2, HEIGHT / 2 };
      SDL_RenderSetViewport(renderer, &top_left);
      SDL_RenderCopy(renderer, img.texture, NULL, NULL);

      // top right
      SDL_Rect top_right = { WIDTH / 2, 0, WIDTH / 2, HEIGHT / 2 };
      SDL_RenderSetViewport(renderer, &top_right);
      SDL_RenderCopy(renderer, img.texture, NULL, NULL);

      // bottom
      SDL_Rect bottom = { 0, HEIGHT / 2, WIDTH, HEIGHT };
      SDL_RenderSetViewport(renderer, &bottom);
      SDL_RenderCopy(renderer, img.texture, NULL, NULL);

      SDL_RenderPresent(renderer);
    }
  }

  return 0;
}
