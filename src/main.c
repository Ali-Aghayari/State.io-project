#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "globalVariable.h"
#include "Init.h"
#include "welcomePageRender.h"
#include "menuPageRender.h"
#include "mapChoosing.h"
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
			mapChooseSetup(id);
			break;
		case 2:
			gameSetup(2, id, -1, -1, -1, -1);
			break;
		case 3:
			rankingPageSetup ();
			break;
		}
	}
	return 0;
}