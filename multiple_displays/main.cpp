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

  SDL_Color color = { 0x00, 0xff, 0x00 };

  font_texture prompt = RenderText(renderer,
    font,
    color,
    "Press Left/Right key to toggle display");

  SDL_Rect displayBounds[10];

  int displayNum = SDL_GetNumVideoDisplays();
  if(displayNum < 2) {
    printf("Warning: there is only one display.");
    return 0;
  }

  for(int i = 0; i < displayNum && i < sizeof(displayBounds); ++i) {
    SDL_GetDisplayBounds(i, &displayBounds[i]);
    printf("display %d: .x = %d, .y = %d, .w = %d, .h = %d\n",
      i,
      displayBounds[i].x,
      displayBounds[i].y,
      displayBounds[i].w,
      displayBounds[i].h);
  }

  int displayID = SDL_GetWindowDisplayIndex(win);
  bool switchDisplay = false;

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      else if(e.type == SDL_WINDOWEVENT) {
        switch(e.window.event) {
        case SDL_WINDOWEVENT_MOVED:
          displayID = SDL_GetWindowDisplayIndex(win);
          break;
        }
      }

      else if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
        case SDLK_LEFT:
          displayID++;
          switchDisplay = true;
          break;

        case SDLK_RIGHT:
          displayID--;
          switchDisplay = true;
          break;
        }
      }
    }

    SDL_Rect rect = {};

    if(switchDisplay) {
      switchDisplay = false;
      if(displayID < 0 || displayID >= displayNum) {
        displayID = displayID < 0 ? 0 : displayNum - 1;
      }
      int x
        = displayBounds[displayID].x + (displayBounds[displayID].w - WIDTH) / 2;
      int y = displayBounds[displayID].y
        + (displayBounds[displayID].h - HEIGHT) / 2;
      SDL_SetWindowPosition(win, x, y);
    }

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Prompt text
    rect.x = (WIDTH - prompt.w) / 2;
    rect.y = 50;
    rect.w = prompt.w;
    rect.h = prompt.h;
    SDL_RenderCopy(renderer, prompt.texture, NULL, &rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
