#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "globalVariable.h"

int errorHandle() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return 1;
	}
	if ( IMG_Init( IMG_INIT_JPG | IMG_INIT_PNG ) < 0 ) {
		printf("Failed to initialize SDL_image: %s", IMG_GetError());
		return 1;
	}
	if (TTF_Init() < 0 ) {
		printf("Error initializing SDL_ttf: %s", TTF_GetError());
		return 1;
	}
	if ( Mix_OpenAudio( MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024 ) != 0 ) {
		printf("Failed to open audio: %s", Mix_GetError());
		return 1;
	}
	return 0;
}
void init() {
	errorHandle();  // maybe use the output ?
	sdlWindow = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}