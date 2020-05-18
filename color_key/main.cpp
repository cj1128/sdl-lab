#include "../common.h"

#define WIDTH 800
#define HEIGHT 600

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  SDL_Surface *fooPNG = IMG_Load("./foo.png");
  if(fooPNG == NULL) {
    printf("error: %s\n", IMG_GetError());
    return 1;
  }
  SDL_SetColorKey(fooPNG, SDL_TRUE, SDL_MapRGB(fooPNG->format, 0, 0xff, 0xff));
  SDL_Texture *foo = SDL_CreateTextureFromSurface(renderer, fooPNG);
  if(foo == NULL) {
    printf("error: %s\n", SDL_GetError());
    return 1;
  }

  img_texture bg = LoadImg(renderer, "background.png");

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

      // Background
      SDL_Rect rect = { 0, 0, bg.w, bg.h };
      SDL_RenderCopy(renderer, bg.texture, NULL, &rect);

      rect.x = 200;
      rect.y = 100;
      rect.w = fooPNG->w;
      rect.h = fooPNG->h;
      SDL_RenderCopy(renderer, foo, NULL, &rect);

      SDL_RenderPresent(renderer);
    }
  }

  return 0;
}
