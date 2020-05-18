#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  img_texture foo = LoadImg(renderer, "foo.png");

  SDL_Event e;
  double angle = 0;
  bool quit = false;
  SDL_RendererFlip flip = SDL_FLIP_NONE;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
        case SDLK_UP: {
          flip = SDL_FLIP_HORIZONTAL;
        } break;

        case SDLK_DOWN: {
          flip = SDL_FLIP_VERTICAL;
        } break;
        case SDLK_LEFT: {
          angle += 30.0;
        } break;
        case SDLK_RIGHT: {
          angle -= 30.0;
        } break;
        }
      }
    }

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Render
    SDL_Rect dstRect = {
      .x = (WIDTH - foo.w) / 2,
      .y = (HEIGHT - foo.h) / 2,
      .w = foo.w,
      .h = foo.h,
    };
    SDL_RenderCopyEx(renderer, foo.texture, NULL, &dstRect, angle, NULL, flip);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
