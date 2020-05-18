#include "../common.h"

#define WIDHT 1024
#define HEIGHT 800

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDHT, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win, true);

  img_texture background = LoadImg(renderer, "background.jpg");
  img_texture circle = LoadImg(renderer, "circle.png");

  int radius = circle.w / 2;
  int x = 50, y = 50;
  float dt = 1.0f / 60.0f;
  float ddPScale = 40000.0f;
  float drag = 12.0f;
  float dX = 0, dY = 0;
  SDL_Event e;
  bool quit = false;
  while(!quit) {
    float ddX = 0, ddY = 0;

    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
        case SDLK_w:
          ddY = -1;
          break;

        case SDLK_s:
          ddY = 1;
          break;

        case SDLK_a:
          ddX = -1;
          break;

        case SDLK_d:
          ddX = 1;
          break;
        }
      }
    }

    ddX *= ddPScale;
    ddX += -dX * drag;
    x += int(dX * dt + 0.5f * ddX * dt * dt);
    dX += ddX * dt;

    ddY *= ddPScale;
    ddY += -dY * drag;
    y += int(dY * dt + 0.5f * ddY * dt * dt);
    dY += ddY * dt;

    if(x < radius || x > background.w - radius) {
      dX = 0;
      x = x < radius ? radius : background.w - radius;
    }

    if(y < radius || y > background.h - radius) {
      dY = 0;
      y = y < radius ? radius : background.h - radius;
    }

    int cameraX = x - WIDHT / 2;
    int cameraY = y - HEIGHT / 2;
    if(cameraX < 0 || cameraX > background.w - WIDHT) {
      cameraX = cameraX < 0 ? 0 : background.w - WIDHT;
    }
    if(cameraY < 0 || cameraY > background.h - HEIGHT) {
      cameraY = cameraY < 0 ? 0 : background.h - HEIGHT;
    }

    SDL_Rect rect;

    // Background
    rect.x = cameraX;
    rect.y = cameraY;
    rect.w = WIDHT;
    rect.h = HEIGHT;
    SDL_RenderCopy(renderer, background.texture, &rect, NULL);

    // Dot
    rect.x = x - cameraX - radius;
    rect.y = y - cameraY - radius;
    rect.w = radius * 2;
    rect.h = radius * 2;
    SDL_RenderCopy(renderer, circle.texture, NULL, &rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
