#include "../common.h"

#define WIDTH 800
#define HEIGHT 600

int
main(void)
{
  InitSDL();

  SDL_Window *win = InitWindow(WIDTH, HEIGHT);

  SDL_Renderer *renderer = InitRenderer(win);

  if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
    printf("error: %s\n", Mix_GetError());
    return 1;
  }

  img_texture prompt = LoadImg(renderer, "prompt.png");

  Mix_Music *gMusic = LoadMusic("Red - Tarlor Swift.mp3");

  Mix_Chunk *gScratch = LoadMusicChunk("scratch.wav");
  Mix_Chunk *gHigh = LoadMusicChunk("high.wav");
  Mix_Chunk *gMedium = LoadMusicChunk("medium.wav");
  Mix_Chunk *gLow = LoadMusicChunk("low.wav");

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }

      if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
        case SDLK_ESCAPE:
          quit = true;
          break;

        case SDLK_1:
          Mix_PlayChannel(-1, gHigh, 0);
          break;

        case SDLK_2:
          Mix_PlayChannel(-1, gMedium, 0);
          break;

        case SDLK_3:
          Mix_PlayChannel(-1, gLow, 0);
          break;

        case SDLK_4:
          Mix_PlayChannel(-1, gScratch, 0);
          break;

        case SDLK_9: {
          if(Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(gMusic, -1);
          } else {
            if(Mix_PausedMusic() == 1) {
              Mix_ResumeMusic();
            } else {
              Mix_PauseMusic();
            }
          }

        } break;

        case SDLK_0:
          Mix_HaltMusic();
          break;
        }
      }
    }

    SDL_RenderCopy(renderer, prompt.texture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  return 0;
}
