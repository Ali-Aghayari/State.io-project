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
#include "gameRender.h"
#include "rankingPageRender.h"



int main (int argv, char *args[])
{
	init();
	int id = welcomePageSetup();
	while (1) {
		int mode = mainMenuSetup(id);
		switch (mode) {
		case 1:
			gameSetup(1, id);
			break;
		case 2:
			gameSetup(2, id);
			break;
		case 3:
			rankingPageSetup ();
			break;
		}
	}
	return 0;
}




// rgbs :
/*
0xffffc75f
0xffaaaa00
0xff5fc7ff
0xffff00ff
0xffccb5fc
0xffff6f91
0xffff9671
0xff916fff
0xff9b9b9e


Hex #C3447A done 9
Hex #BC243C done
Hex #45B8AC done 10
Hex #9B2335
Hex #E15D44 done 8
Hex #EFC050 done 7
Hex #5B5EA6
Hex #D65076 with 9 ??
Hex #B565A7

HEX: #FF6F61
*/


// Mix_FreeChunk( sound );
// Mix_FreeMusic( music );
// Mix_Quit();
// TTF_CloseFont( font );
// TTF_Quit();
// SDL_DestroyTexture(sdlTexture);
// SDL_FreeSurface(sdlImage);
// SDL_Quit();
// null ptr those thingies