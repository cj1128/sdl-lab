#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  img_texture bg = LoadImg(renderer, "fadeout.png");
  img_texture fg = LoadImg(renderer, "fadein.png");

  SDL_SetTextureBlendMode(fg.texture, SDL_BLENDMODE_BLEND);

  int alpha = 255;

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
        case SDLK_ESCAPE: {
          quit = true;
        } break;

        case SDLK_s: {
          alpha += 30;
          if(alpha > 255) {
            alpha = 255;
          }
        } break;

        case SDLK_w: {
          alpha -= 30;
          if(alpha < 0) {
            alpha = 0;
          }
        } break;
        }
      }
    }

    SDL_Rect rect = { 0, 0, WIDTH, HEIGHT };

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // bg
    SDL_RenderCopy(renderer, bg.texture, NULL, &rect);

    // fg
    SDL_SetTextureAlphaMod(fg.texture, (unsigned char)alpha);
    SDL_RenderCopy(renderer, fg.texture, NULL, &rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
