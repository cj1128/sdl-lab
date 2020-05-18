#include "../common.h"

#define WIDTH 640
#define HEIGHT 480

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  TTF_Font *font = OpenFont(35);

  SDL_Color color = { 0xff, 0x00, 0x00 };
  font_texture mouseOver = RenderText(renderer, font, color, "mouse over");
  font_texture mouseOut = RenderText(renderer, font, color, "mouse out");
  font_texture mouseUp = RenderText(renderer, font, color, "mouse up");
  font_texture mouseDown = RenderText(renderer, font, color, "mouse down");

  int padding = 10;
  int width = (WIDTH - padding) / 2;
  int height = (HEIGHT - padding) / 2;

  SDL_Rect rects[4];
  SDL_Texture *textures[4];

  rects[0] = (SDL_Rect){ 0, 0, width, height }; // top left
  rects[1] = (SDL_Rect){ width + padding, 0, width, height }; // top right
  rects[2] = (SDL_Rect){ 0, height + padding, width, height }; // bottom right
  rects[3] = (SDL_Rect){ width + padding,
    height + padding,
    width,
    height }; // bottom right

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      if(e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN
        || e.type == SDL_MOUSEBUTTONUP) {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        for(int i = 0; i < 4; i++) {
          SDL_Rect rect = rects[i];

          if(mouseX >= rect.x && mouseX <= rect.x + rect.w && mouseY >= rect.y
            && mouseY <= rect.y + rect.w) {
            switch(e.type) {
            case SDL_MOUSEMOTION:
              textures[i] = mouseOver.texture;
              break;

            case SDL_MOUSEBUTTONDOWN:
              textures[i] = mouseDown.texture;
              break;

            case SDL_MOUSEBUTTONUP:
              textures[i] = mouseUp.texture;
              break;
            }
          } else {
            textures[i] = mouseOut.texture;
          }
        }
      }
    }

    // Clear
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);

    for(int i = 0; i < 4; i++) {
      SDL_RenderFillRect(renderer, &rects[i]);
      int width, height, access;
      uint32_t format;
      SDL_QueryTexture(textures[i], &format, &access, &width, &height);

      SDL_Rect rect;
      rect.x = rects[i].x + (rects[i].w - width) / 2;
      rect.y = rects[i].y + (rects[i].h - height) / 2;
      rect.w = width;
      rect.h = height;

      SDL_RenderCopy(renderer, textures[i], NULL, &rect);
    }

    SDL_RenderPresent(renderer);
  }

  return 0;
}
