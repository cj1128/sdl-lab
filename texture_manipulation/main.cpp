#include "../common.h"

#define WIDTH 800
#define HEIGHT 600

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  uint32_t format = SDL_GetWindowPixelFormat(win);

  SDL_Surface *img = IMG_Load("foo.png");
  if(img == NULL) {
    return 1;
  }
  img = SDL_ConvertSurfaceFormat(img, format, 0);
  if(img == NULL) {
    return 1;
  }

  SDL_Texture *texture = SDL_CreateTexture(renderer,
    SDL_GetWindowPixelFormat(win),
    SDL_TEXTUREACCESS_STREAMING,
    img->w,
    img->h);
  if(texture == NULL) {
    return 1;
  }

  void *rawPixels;
  int pitch;
  SDL_LockTexture(texture, NULL, &rawPixels, &pitch);

  SDL_PixelFormat *mappingFormat = SDL_AllocFormat(format);

  uint32_t *pixels = (uint32_t *)rawPixels;
  int pixelCount = (pitch / 4) * img->h;

  uint32_t bgColor = SDL_MapRGB(mappingFormat, 0, 0xff, 0xff);
  uint32_t transparent = SDL_MapRGBA(mappingFormat, 0xff, 0xff, 0xff, 0x00);

  memcpy(pixels, img->pixels, (size_t)pitch * (size_t)img->h);

  for(int i = 0; i < pixelCount; i++) {
    if(pixels[i] == bgColor) {
      pixels[i] = transparent;
    }
  }

  SDL_UnlockTexture(texture);

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        quit = true;
      }

      if(e.type == SDL_QUIT) {
        quit = true;
      }
    }

    SDL_Rect rect;

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Texture
    rect.x = 100;
    rect.y = 100;
    rect.w = img->w;
    rect.h = img->h;
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
