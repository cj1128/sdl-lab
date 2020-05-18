#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef COMMON_H
#define COMMON_H

struct img_texture {
  SDL_Texture *texture;
  int w;
  int h;
};

struct font_texture {
  SDL_Texture *texture;
  int w;
  int h;
};

int
Square(int v)
{
  return v * v;
}

font_texture
RenderText(SDL_Renderer *renderer, TTF_Font *font, SDL_Color color, char *str)
{
  font_texture result = {};
  SDL_Surface *surface = TTF_RenderText_Solid(font, str, color);

  if(surface == NULL) {
    printf("error: %s\n", TTF_GetError());
    exit(1);
  }

  result.texture = SDL_CreateTextureFromSurface(renderer, surface);
  result.w = surface->w;
  result.h = surface->h;
  SDL_FreeSurface(surface);

  return result;
}

SDL_Surface *
RenderTextSurface(TTF_Font *font, SDL_Color color, char *str)
{
  SDL_Surface *surface = TTF_RenderText_Solid(font, str, color);
  if(surface == NULL) {
    printf("error: %s\n", TTF_GetError());
    exit(1);
  }
  return surface;
}

img_texture
LoadImg(SDL_Renderer *renderer, char *path)
{
  img_texture result = {};

  SDL_Surface *img = IMG_Load(path);
  if(img == NULL) {
    printf("error: %s\n", IMG_GetError());
    exit(1);
  }

  result.texture = SDL_CreateTextureFromSurface(renderer, img);
  result.w = img->w;
  result.h = img->h;
  SDL_FreeSurface(img);

  return result;
}

SDL_Surface *
LoadImgSurface(char *path)
{
  SDL_Surface *img = IMG_Load(path);
  if(img == NULL) {
    printf("error: %s\n", IMG_GetError());
    exit(1);
  }

  return img;
}

void
InitSDL()
{
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    printf("error: %s\n", SDL_GetError());
    exit(1);
  }

  if(TTF_Init() == -1) {
    printf("error: %s\n", TTF_GetError());
    exit(1);
  }

  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
  if((IMG_Init(imgFlags) & imgFlags) != imgFlags) {
    printf("error: %s\n", IMG_GetError());
    exit(1);
  }
}

SDL_Window *
InitWindow(int width, int height, char *name = "My Window")
{
  SDL_Window *win = SDL_CreateWindow(name,
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    width,
    height,
    SDL_WINDOW_SHOWN);

  if(win == NULL) {
    printf("error: %s\n", SDL_GetError());
    exit(1);
  }

  return win;
}

SDL_Renderer *
InitRenderer(SDL_Window *win, bool vsync = false)
{
  uint32_t flags = SDL_RENDERER_ACCELERATED;
  if(vsync) {
    flags |= SDL_RENDERER_PRESENTVSYNC;
  }
  SDL_Renderer *renderer = SDL_CreateRenderer(win, -1, flags);
  if(renderer == NULL) {
    printf("error: %s\n", SDL_GetError());
    exit(1);
  }

  return renderer;
}

TTF_Font *
OpenFont(int size = 30, char *path = "../Orbitron-Regular.ttf")
{
  TTF_Font *font = TTF_OpenFont(path, size);
  if(font == NULL) {
    printf("error: %s\n", TTF_GetError());
    exit(1);
  }

  return font;
}

Mix_Music *
LoadMusic(char *path)
{
  Mix_Music *result = Mix_LoadMUS(path);
  if(result == NULL) {
    printf("error: %s\n", Mix_GetError());
    exit(1);
  }

  return result;
}

Mix_Chunk *
LoadMusicChunk(char *path)
{
  Mix_Chunk *result = Mix_LoadWAV(path);
  if(result == NULL) {
    printf("error: %s\n", Mix_GetError());
    exit(1);
  }

  return result;
}

#endif
