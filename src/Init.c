#include <SDL2/SDL_ttf.h>
#include "globalVariable.h"

void errorHandle() {
	if (SDL_Init(SDL_INIT_VIDEO |SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return ;
	}
	if (TTF_Init() < 0 ) {
		printf("Error initializing SDL_ttf: %s", TTF_GetError());
		return ;
	}
	return ;
}
void init() {
	errorHandle();
	sdlWindow = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
}