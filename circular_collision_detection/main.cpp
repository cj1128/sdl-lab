#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

struct game_circle {
  int x, y, radius;
  SDL_Texture *texture;
};

// x,y is the center of the dot
struct game_dot {
  float dX;
  float dY;
  game_circle circle;
};

game_circle
LoadCircle(SDL_Renderer *renderer, char *file)
{
  game_circle result = {};
  img_texture png = LoadImg(renderer, file);
  result.texture = png.texture;
  result.radius = png.w / 2;
  return result;
}

bool
IsInsideCircle(int x, int y, game_circle *circle)
{
  int distanceSq = Square(x - circle->x) + Square(y - circle->y);
  return distanceSq <= Square(circle->radius);
}

bool
CheckCollision(game_dot *dot, game_circle *circle)
{
  int distanceSq
    = Square(dot->circle.x - circle->x) + Square(dot->circle.y - circle->y);

  return distanceSq <= Square(dot->circle.radius + circle->radius);
}

bool
CheckCollision(game_dot *dot, SDL_Rect *rect)
{
  int closestX, closestY;
  int minX = rect->x;
  int maxX = minX + rect->w;
  int minY = rect->y;
  int maxY = minY + rect->h;

  if(dot->circle.x < minX) {
    closestX = minX;
  } else if(dot->circle.x > maxX) {
    closestX = maxX;
  } else {
    closestX = dot->circle.x;
  }

  if(dot->circle.y < minY) {
    closestY = minY;
  } else if(dot->circle.y > maxY) {
    closestY = maxY;
  } else {
    closestY = dot->circle.y;
  }

  return IsInsideCircle(closestX, closestY, &dot->circle);
}

void
MoveDot(float dt,
  float ddX,
  float ddY,
  float ddPScale,
  float drag,
  game_dot *dot,
  game_circle *c,
  SDL_Rect *wall)
{
  int oldX = dot->circle.x, oldY = dot->circle.y;

  ddX *= ddPScale;
  ddX += -dot->dX * drag;
  float deltaX = dot->dX * dt + 0.5f * ddX * dt * dt;
  dot->circle.x += (int)deltaX;
  dot->dX += ddX * dt;

  ddY *= ddPScale;
  ddY += -dot->dY * drag;
  dot->circle.y += dot->dY * dt + 0.5f * ddY * dt * dt;
  dot->dY += ddY * dt;

  if(CheckCollision(dot, c) || CheckCollision(dot, wall)) {
    dot->circle.x = oldX;
    dot->circle.y = oldY;

    dot->dX = 0;
    dot->dY = 0;
  }

  int r = dot->circle.radius;

  if(dot->circle.x < r || dot->circle.x >= WIDTH - r) {
    dot->dX = 0;
    dot->circle.x = dot->circle.x < r ? r : WIDTH - r;
  }

  if(dot->circle.y < r | dot->circle.y >= HEIGHT - r) {
    dot->dY = 0;
    dot->circle.y = dot->circle.y < r ? r : HEIGHT - r;
  }
}

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win, true);

  game_dot dot = {};
  dot.circle = LoadCircle(renderer, "circle.png");
  if(dot.circle.texture == NULL) {
    return 1;
  }
  dot.circle.x = 40;
  dot.circle.y = 40;

  game_circle redCircle = LoadCircle(renderer, "circle2.png");
  if(redCircle.texture == NULL) {
    return 1;
  }
  redCircle.x = 500;
  redCircle.y = 200;

  SDL_Rect wall = {
    .x = WIDTH / 3,
    .y = 40,
    .h = HEIGHT - 40 * 2,
    .w = 20,
  };

  SDL_Event e;
  bool quit = false;
  float dt = 1.0f / 60.0f;
  float ddPScale = 18000.0f;
  float drag = 14.0f;
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

    MoveDot(dt, ddX, ddY, ddPScale, drag, &dot, &redCircle, &wall);

    SDL_Rect rect = {};

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Wall
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &wall);

    // Red Circle
    rect.x = redCircle.x - redCircle.radius;
    rect.y = redCircle.y - redCircle.radius;
    rect.w = redCircle.radius * 2;
    rect.h = rect.w;
    SDL_RenderCopy(renderer, redCircle.texture, NULL, &rect);

    // Dot
    rect.x = dot.circle.x - dot.circle.radius;
    rect.y = dot.circle.y - dot.circle.radius;
    rect.w = dot.circle.radius * 2;
    rect.h = rect.w;
    SDL_RenderCopy(renderer, dot.circle.texture, NULL, &rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
