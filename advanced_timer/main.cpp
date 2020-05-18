#include "../common.h"

#define WIDTH 800
#define HEIGHT 600

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  TTF_Font *font = OpenFont();

  SDL_Color color = { 0x00, 0xff, 0 };

  font_texture firstText
    = RenderText(renderer, font, color, "Press S to Start or Stop the timer");
  font_texture secondText = RenderText(renderer,
    font,
    color,
    "Press P to Pause or Unpause the timer");

  char buf[1024];
  float seconds = 0;
  bool paused = false;
  SDL_Event e;
  unsigned int lastTick = SDL_GetTicks();
  bool quit = false;
  bool started = false;
  while(!quit) {
    unsigned int newTick = SDL_GetTicks();

    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      if(e.type == SDL_KEYDOWN && e.key.keysym.sym == 'p') {
        if(started) {
          paused = !paused;
        }
      }

      if(e.type == SDL_KEYDOWN && e.key.keysym.sym == 's') {
        started = !started;
        seconds = 0;
        paused = false;
      }
    }

    if(started && !paused) {
      seconds += (float)(newTick - lastTick) / 1000;
    }

    SDL_Rect rect;

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Render top texts
    rect.x = (WIDTH - firstText.w) / 2;
    rect.y = 20;
    rect.w = firstText.w;
    rect.h = firstText.h;
    SDL_RenderCopy(renderer, firstText.texture, NULL, &rect);

    rect.x = (WIDTH - secondText.w) / 2;
    rect.y = 20 + 20 + firstText.h;
    rect.w = secondText.w;
    rect.h = secondText.h;
    SDL_RenderCopy(renderer, secondText.texture, NULL, &rect);

    snprintf(buf, sizeof(buf), "Seconds since start time: %.3f", seconds);

    font_texture tick = RenderText(renderer, font, color, buf);

    rect.x = 50;
    rect.y = 150;
    rect.w = tick.w;
    rect.h = tick.h;
    SDL_RenderCopy(renderer, tick.texture, NULL, &rect);

    SDL_RenderPresent(renderer);

    lastTick = newTick;
  }

  return 0;
}
