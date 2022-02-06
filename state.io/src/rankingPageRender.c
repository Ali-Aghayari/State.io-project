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
	char userName[20], idS[5], rankS[5], playTimeS[5];
	int id, rank, playTime;
	char line[256];
	int RGB[] = {200, 200, 200};
	for (int i = 0; i < ppl+1 ; ++i)
	{
		dataBase = fopen("res/DataBase/userNames.txt", "r");
		if (dataBase == NULL)
		{
			printf("Error openning Files\n");
		}
		while (fgets(line, 256, dataBase) != NULL)
		{
			sscanf(line, " %d %d %d %[^\n]", &id, &rank, &playTime, userName);
			if (rank == i)
			{
				sprintf(idS, "%d", id);
				sprintf(rankS, "%d", rank);
				sprintf(playTimeS, "%d", playTime);
				boxRGBA(sdlRenderer, 150, 90 + 90 * i, SCREEN_WIDTH - 150, 170 + 90 * i, 0, 0, 0, 100);
				outputScreen(rankS, 250,  135 + 90 * i, 20, RGB, 1 );
				outputScreen(userName, SCREEN_WIDTH / 2,  135 + 90 * i, 20, RGB, 1 );
				outputScreen(playTimeS, SCREEN_WIDTH - 250,  135 + 90 * i, 20, RGB, 1 );
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
	mainMenuscreen();
	int RGB[] = {200, 0, 0};
	outputScreen("RANK", 250,  100, 20, RGB, 3 );
	outputScreen("USERNAME", SCREEN_WIDTH / 2,  100, 20, RGB, 3);
	outputScreen("PLAY TIME", SCREEN_WIDTH - 250,  100, 20, RGB, 3 );

	int count = userCount();
	drawbox(MIN(count, 7));
	SDL_RenderPresent(sdlRenderer);
}

