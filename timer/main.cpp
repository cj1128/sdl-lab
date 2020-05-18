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

  SDL_Color color = { 0x00, 0xff, 0x00, 0xff };

  font_texture resetPrompt
    = RenderText(renderer, font, color, "Press Enter to reset the timer");

  char buf[1024];
  unsigned int startTick = 0;
  SDL_Event e;
  bool quit = false;
  while(!quit) {
    unsigned int newTick = SDL_GetTicks();

    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN) {
        startTick = newTick;
      }
    }

    SDL_Rect rect;

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Reset prompt
    rect.x = (WIDTH - resetPrompt.w) / 2;
    rect.y = 50;
    rect.w = resetPrompt.w;
    rect.h = resetPrompt.h;
    SDL_RenderCopy(renderer, resetPrompt.texture, NULL, &rect);

    // Timer
    snprintf(buf,
      sizeof(buf),
      "Milliseconds since start time: %d",
      newTick - startTick);

    font_texture tick = RenderText(renderer, font, color, buf);
    rect.x = 50;
    rect.y = 150;
    rect.w = tick.w;
    rect.h = tick.h;

    SDL_RenderCopy(renderer, tick.texture, NULL, &rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
