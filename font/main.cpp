#include "../common.h"

#define WIDTH 800
#define HEIGHT 600

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  TTF_Font *font = OpenFont(100);

  SDL_Color color = { 0x00, 0xff, 0 };
  font_texture text = RenderText(renderer, font, color, "Hello World");

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

    SDL_Rect rect;
    rect.x = 100;
    rect.y = 100;
    rect.w = text.w;
    rect.h = text.h;

    SDL_RenderCopy(renderer, text.texture, NULL, &rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
