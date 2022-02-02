#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "globalVariable.h"
#include "Init.h"
#include "welcomePageRender.h"
#include "menuPageRender.h"



void drawbox(int ppl) {
	// if my rank is more than 7
	// 1 2 3
	// ....
	// my rank and - and ++ and + 
	for (int i = 0; i < ppl; ++i)
	{
		boxRGBA(sdlRenderer, 150, 100+90*i, SCREEN_WIDTH - 150, 180+90*i, 0, 0, 0, 100);
	}

}
void rankingPageSetup () {
	mainMenuscreen();
	drawbox(8);
	// need a back bottum 
	SDL_RenderPresent(sdlRenderer);
}