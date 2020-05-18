#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

#define MAX_FRAME_RATE 60

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  TTF_Font *font = OpenFont();

  SDL_Event e;
  bool quit = false;
  float msPerFrame = 0;
  unsigned int startTick = 0;
  float expectedMSPerFrame = 1000.0f / (float)MAX_FRAME_RATE;
  char buf[100] = {};
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }
    }

    SDL_Rect rect;

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Text
    snprintf(buf, sizeof(buf), "FPS: %.4f", 1000.0f / msPerFrame);

    if(msPerFrame != 0) {
      SDL_Color color = { 0x00, 0xff, 0 };
      font_texture text = RenderText(renderer, font, color, buf);

      rect.x = WIDTH / 10;
      rect.y = 20;
      rect.w = text.w;
      rect.h = text.h;

      SDL_RenderCopy(renderer, text.texture, NULL, &rect);
    }

    // Lock frame rate
    unsigned int elapsed = SDL_GetTicks() - startTick;
    while(elapsed < expectedMSPerFrame) {
      SDL_Delay((uint32_t)(expectedMSPerFrame - elapsed));
      elapsed = SDL_GetTicks() - startTick;
    }

    SDL_RenderPresent(renderer);

    unsigned int curTick = SDL_GetTicks();
    if(startTick != 0) {
      msPerFrame = curTick - startTick;
    }
    startTick = curTick;
  }

  return 0;
}
