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


void drawbox(int ppl)
{
	FILE *dataBase;
	int id, rank, playTime;
	char userName[15];
	char line[256];
	int RGB[] = {120, 120, 120};
	for (int i = 0; i < ppl ; ++i)
	{
		dataBase = fopen("res/DataBase/userNames.txt", "r");
		if (dataBase == NULL)
		{
			printf("Error openning Files\n");
		}
		while (fgets(line, 256, dataBase) != NULL)
		{
			sscanf(line, " %d %d %d %[^\n]s\n", &id, &rank, &playTime, userName);
			if (rank == i)
			{
				boxRGBA(sdlRenderer, 150, 100 + 90 * i, SCREEN_WIDTH - 150, 180 + 90 * i, 0, 0, 0, 100);
				outputScreen(userName, SCREEN_WIDTH / 2,  140 + 90 * i, 20, RGB, 1 );
				break;
			}
		}
		fclose(dataBase);
	}
}
int userCount()
{
	int ppl = 0;
	FILE *dataBase  ;
	dataBase  = fopen("res/DataBase/userNames.txt", "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		ppl++;
	}
	fclose(dataBase);
	return ppl;
}
void rankingPageSetup () {
	int count = userCount();
	drawbox(MIN(count, 8));
	SDL_RenderPresent(sdlRenderer);
}

