#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

#define BOX_SIZE 20

typedef struct {
  float x;
  float y;
  float dX;
  float dY;
  int size;
} game_box;

bool
CheckHitWall(SDL_Rect *wall, game_box *box)
{
  float wallMinX = wall->x;
  float wallMaxX = wall->x + wall->w;
  float wallMinY = wall->y;
  float wallMaxY = wall->y + wall->h;

  float boxMinX = box->x;
  float boxMaxX = box->x + box->size;
  float boxMinY = box->y;
  float boxMaxY = box->y + box->size;

  return !((boxMinX > wallMaxX) || (boxMaxX < wallMinX) || (boxMinY > wallMaxY)
    || (boxMaxY < wallMinY));
}

void
MoveBox(float ddX,
  float ddY,
  float ddPScale,
  float drag,
  game_box *box,
  float dt,
  SDL_Rect *wall)
{
  float oldX = box->x, oldY = box->y;

  ddX *= ddPScale;
  ddX += -box->dX * drag;
  box->x += box->dX * dt + 0.5f * ddX * dt * dt;
  box->dX += ddX * dt;

  ddY *= ddPScale;
  ddY += -box->dY * drag;
  box->y += box->dY * dt + 0.5f * ddY * dt * dt;
  box->dY += ddY * dt;

  if(CheckHitWall(wall, box)) {
    box->x = oldX;
    box->dX = 0;
    box->y = oldY;
    box->dY = 0;
  }

  if(box->x < 0 || box->x >= WIDTH - box->size) {
    box->dX = 0;
    box->x = box->x < 0 ? 0 : WIDTH - box->size;
  }

  if(box->y < 0 | box->y >= HEIGHT - box->size) {
    box->dY = 0;
    box->y = box->y < 0 ? 0 : HEIGHT - box->size;
  }
}

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win, true);

  SDL_Rect wall = {
    .x = WIDTH / 3,
    .y = 40,
    .h = HEIGHT - 40 * 2,
    .w = 20,
  };

  SDL_Event e;
  bool quit = false;
  float dt = 1.0f / 60.0f;
  float ddPScale = 20000.0f;
  float drag = 12.0f;
  game_box box = {
    .size = BOX_SIZE,
  };
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

    MoveBox(ddX, ddY, ddPScale, drag, &box, dt, &wall);

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Wall
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &wall);

    // Box
    SDL_Rect rect
      = { .x = (int)box.x, .y = (int)box.y, .w = box.size, .h = box.size };
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
