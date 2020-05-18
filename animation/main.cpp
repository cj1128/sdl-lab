#include "../common.h"

#define WIDTH 518
#define HEIGHT 800

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win, true);

  img_texture img = LoadImg(renderer, "bar.png");

  SDL_Event e;
  bool quit = false;
  int frame = 0;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }
    }

    int factor = 10;
    int frameWidth = img.w / 4;

    SDL_Rect srcRect;
    srcRect.x = (frame / factor) * frameWidth;
    srcRect.y = 0;
    srcRect.w = frameWidth;
    srcRect.h = img.h;

    SDL_Rect dstRect = { .w = WIDTH, .h = HEIGHT };

    SDL_RenderCopy(renderer, img.texture, &srcRect, &dstRect);
    frame++;

    if(frame / factor > 4) {
      frame = 0;
    }

    SDL_RenderPresent(renderer);
  }

  return 0;
}
