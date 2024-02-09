#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>

SDL_Window  *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gHelloPic = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 480;

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gWindow = SDL_CreateWindow("SDL tutorial", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, 0);
    if (gWindow == NULL) {
      printf("Window could not bre created! SDL_ERROR: %s\n", SDL_GetError());
      success = false;
    }
    gRenderer = SDL_CreateRenderer(
                                   gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!gRenderer) {
      printf("Renderer could not bre created! SDL_ERROR: %s\n", SDL_GetError());
      success = false;
    }

  }
  return success;
}

bool loadMedia() {
  bool success = true;

  gHelloPic = IMG_Load("1_2.png");
  if (gHelloPic == NULL) {
    printf("UNABLE TO LOAD IMAGE, ERROR: %s\n", SDL_GetError());
    success = false;
  }

  gTexture = SDL_CreateTextureFromSurface(gRenderer, gHelloPic);
  if (!gTexture) {
      printf("Texturer could not be created! SDL_ERROR: %s\n", SDL_GetError());
      success = false;
  }
  return success;
}

void close() {

  SDL_FreeSurface(gHelloPic);
  gHelloPic = NULL;

  SDL_DestroyTexture(gTexture);
  gTexture = NULL;

  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}

int main(void) {
  bool err = init();
  bool quit = false;
  SDL_Event e;
  if (!err) {
    printf("FAILED TO INITIALIZE");
    SDL_Quit();
    return -1;
  }
  err = loadMedia();
  if (!err) {
    printf("FAILED TO LOAD MEDIA");
    SDL_Quit();
    return -1;
  } else {
    SDL_RenderClear(gRenderer);
    SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
    SDL_RenderPresent(gRenderer);
    //While application is running
    while( !quit ){
      //Handle events on queue
      while( SDL_PollEvent( &e ) != 0 )  {
        //User requests quit
        if( e.type == SDL_QUIT ) // unless player manually quits
          {
            quit = true;
          }
      }
    }
  }

  close();
  return (0);
}
