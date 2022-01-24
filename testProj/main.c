#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define \
FPS 60
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

// funcs !!
// be able to close the game!
// my printOnWelcomePage func needs a font change
// change font / change color / change size and indexing
// get a username
void printOnWelcomePage(SDL_Renderer *sdlRenderer){
    //char text[20];
    //sprintf(text,"welcome to my game");
    stringRGBA(sdlRenderer,SCREEN_HEIGHT/2,SCREEN_WIDTH/100,"State.io",0,0,0,255); // bigger
    stringRGBA(sdlRenderer,SCREEN_HEIGHT/2,SCREEN_WIDTH/20,"Enter your username : ",0,0,0,255);
    stringRGBA(sdlRenderer,SCREEN_HEIGHT/2,SCREEN_WIDTH/10,"Created by : Ali Aghayari",0,0,0,255);
}

void welcomePage(SDL_Window *sdlWindow,SDL_Renderer *sdlRenderer){
    SDL_Surface* sdlImage = SDL_LoadBMP("/home/bemoache/CLionProjects/testProj/mainPage.bmp");
    if (sdlImage==NULL){printf("Unable to load bitmap: %s \n", SDL_GetError()); return;}
    SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlImage);
    SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
    printOnWelcomePage(sdlRenderer);
    SDL_RenderPresent(sdlRenderer);
    //SDL_UpdateWindowSurface(sdlWindow);
    SDL_Delay(3000);
    SDL_DestroyTexture(sdlTexture);
    SDL_FreeSurface(sdlImage);
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }
    SDL_Window *sdlWindow = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_SetWindowFullscreen(sdlWindow,0); // ,SDL_WINDOW_FULLSCREEN_DESKTOP
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    // welcome and get user name
    welcomePage(sdlWindow,sdlRenderer);

    // do the thingie

    // create map
    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(sdlRenderer, 	000000, 	000000, 	000000, 	000000);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(1000 / FPS);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_KEYUP:
                    switch (sdlEvent.key.keysym.scancode) {
                    }
            }
        }
    }

    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
    SDL_Quit();
    return 0;
}