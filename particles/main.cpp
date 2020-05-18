#include "../common.h"

#define WIDTH 800
#define HEIGHT 600

struct particle {
  int x;
  int y;
  int frame;
  img_texture *texture;
};

img_texture
LoadImg2(SDL_Renderer *renderer, char *path)
{
  img_texture result = {};

  SDL_Surface *img = IMG_Load(path);
  if(img != NULL) {
    SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 0, 0xFF, 0xFF));

    result.texture = SDL_CreateTextureFromSurface(renderer, img);
    result.w = img->w;
    result.h = img->h;
    SDL_FreeSurface(img);
  }

  return result;
}

void
InitializeParticle(particle *p,
  int x,
  int y,
  img_texture *red,
  img_texture *green,
  img_texture *blue)
{
  int randomValue = rand() % 3;
  p->x = x - 10 + rand() % 25;
  p->y = y - 10 + rand() % 25;
  if(randomValue == 0) {
    p->texture = red;
  } else if(randomValue == 1) {
    p->texture = blue;
  } else {
    p->texture = green;
  }
  p->frame = rand() % 5;
}

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  img_texture dot = LoadImg2(renderer, "dot.bmp");
  if(dot.texture == NULL) {
    return 1;
  }

  int x = 100, y = 100;
  int dX = 0, dY = 0;

  img_texture red = LoadImg2(renderer, "red.bmp");
  img_texture blue = LoadImg2(renderer, "blue.bmp");
  img_texture green = LoadImg2(renderer, "green.bmp");
  img_texture shimmer = LoadImg2(renderer, "shimmer.bmp");
  if(red.texture == NULL || blue.texture == NULL || green.texture == NULL
    || shimmer.texture == NULL) {
    return 1;
  }

#define PARTICLE_COUNT 20
  particle particles[PARTICLE_COUNT] = {};
  for(int i = 0; i < PARTICLE_COUNT; i++) {
    InitializeParticle(particles + i, x, y, &red, &green, &blue);
  }

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
        quit = true;
      }

      if(e.type == SDL_MOUSEMOTION) {
        SDL_GetMouseState(&x, &y);
      }
    }

    if(x >= WIDTH - dot.w) {
      x = WIDTH - dot.w;
    }
    if(y >= HEIGHT - dot.h) {
      y = HEIGHT - dot.h;
    }

    SDL_Rect rect;

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Dot
    rect.x = x;
    rect.y = y;
    rect.w = dot.w;
    rect.h = dot.h;
    SDL_RenderCopy(renderer, dot.texture, NULL, &rect);

    // Particles
    for(int i = 0; i < PARTICLE_COUNT; i++) {
      particle *p = particles + i;
      rect.x = p->x;
      rect.y = p->y;
      rect.w = p->texture->w;
      rect.h = p->texture->h;
      SDL_RenderCopy(renderer, p->texture->texture, NULL, &rect);

      if(p->frame % 2 == 0) {
        rect.w = shimmer.w;
        rect.h = shimmer.h;
        SDL_RenderCopy(renderer, shimmer.texture, NULL, &rect);
      }

      p->frame++;

      if(p->frame == 10) {
        InitializeParticle(p, x, y, &red, &green, &blue);
      }
    }

    SDL_RenderPresent(renderer);
  }

  return 0;
}
