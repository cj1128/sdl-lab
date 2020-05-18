#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  TTF_Font *font = OpenFont(60);

  SDL_Color promptColor = { 0x00, 0xff, 0x00 };
  SDL_Color txtColor = { 0xff, 0xff, 0x00 };

  font_texture prompt = RenderText(renderer, font, promptColor, "Enter text:");

  char buf[100] = {};
  int written = 0;

  SDL_Event e;
  bool quit = false;
  bool renderText = true;
  font_texture txt;
  SDL_StartTextInput();
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      else if(e.type == SDL_KEYDOWN) {
        if(e.key.keysym.sym == SDLK_BACKSPACE && written > 0) {
          buf[--written] = 0;
          renderText = true;
        }
      }

      else if(e.type == SDL_TEXTINPUT) {
        if(!((SDL_GetModState() & KMOD_CTRL)
             && (e.text.text[0] == 'c' || e.text.text[0] == 'C'
               || e.text.text[0] == 'v' || e.text.text[0] == 'V'))) {
          strcpy(buf + written, e.text.text);
          written += strlen(e.text.text);
          renderText = true;
        }
      }
    }

    SDL_Rect rect = {};

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    // Prompt
    rect.x = (WIDTH - prompt.w) / 2;
    rect.y = 50;
    rect.w = prompt.w;
    rect.h = prompt.h;
    SDL_RenderCopy(renderer, prompt.texture, NULL, &rect);

    // Text
    if(renderText) {
      renderText = false;
      buf[written] = 0;
      char *str = buf;
      if(written == 0) {
        str = " ";
      }
      txt = RenderText(renderer, font, txtColor, str);
      if(txt.texture == NULL) {
        return 1;
      }
    }

    rect.x = WIDTH / 10;
    rect.y = 200;
    rect.w = txt.w;
    rect.h = txt.h;
    SDL_RenderCopy(renderer, txt.texture, NULL, &rect);

    SDL_RenderPresent(renderer);
  }

  return 0;
}
