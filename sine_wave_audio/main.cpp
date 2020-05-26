#include "../common.h"
#include <math.h>

int
main(void)
{
  InitSDL();

  if(SDL_GetNumAudioDevices(0) <= 0) {
    printf("No audio device found");
    return 0;
  }

  SDL_AudioSpec want = {}, have;
  SDL_AudioDeviceID device;
  want.freq = 20000;
  want.format = AUDIO_F32;
  want.channels = 2;
  want.samples = 128;

  device
    = SDL_OpenAudioDevice(NULL, 0, &want, &have, SDL_AUDIO_ALLOW_FORMAT_CHANGE);
  if(device == 0) {
    printf("Failed to open audio: %s", SDL_GetError());
    return 1;
  }

  if(have.format != want.format) {
    printf("We didn't get Float32 audio format.");
  }

  SDL_PauseAudioDevice(device, 0);

  unsigned int sampleCount = have.channels * have.samples;
  unsigned int bufsize = sampleCount * 4;
  float *data = (float *)malloc((size_t)bufsize);

  if(data == NULL) {
    printf("malloc failed");
    return 1;
  }

  float value = 0;

  SDL_Event e;
  bool quit = false;
  while(!quit) {
    while(SDL_PollEvent(&e)) {
      if(e.type == SDL_QUIT) {
        quit = true;
      }
    }

    for(int i = 0; i < sampleCount; i++) {
      data[i] = 0.3f * sinf(value);
      value += 0.05f;
    }

    SDL_QueueAudio(device, data, bufsize);
  }
}
