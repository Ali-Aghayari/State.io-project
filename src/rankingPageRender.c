#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

#include "globalVariable.h"
#include "welcomePageRender.h"
#include "menuPageRender.h"


void drawbox(int ppl)
{
	FILE *dataBase;
	char userName[20], idS[5], rankS[5], scoreS[5];
	int id, rank, score;
	char line[256];
	int RGB[] = {158, 16, 48};
	for (int i = 0; i < ppl + 1 ; ++i)
	{
		dataBase = fopen("res/DataBase/userNames.txt", "r");
		if (dataBase == NULL)
		{
			printf("Error openning Files\n");
		}
		while (fgets(line, 256, dataBase) != NULL)
		{
			sscanf(line, " %d %d %d %[^\n]", &id, &rank, &score, userName);
			if (rank == i)
			{
				sprintf(idS, "%d", id);
				sprintf(rankS, "%d", rank);
				sprintf(scoreS, "%d", score);
				boxRGBA(sdlRenderer, 150, 90 + 90 * i, SCREEN_WIDTH - 150, 170 + 90 * i, 0, 0, 0, 100);
				outputScreen(rankS, 250,  135 + 90 * i, 30, RGB, 1 );
				outputScreen(userName, SCREEN_WIDTH / 2,  135 + 90 * i, 30, RGB, 1 );
				outputScreen(scoreS, SCREEN_WIDTH - 250,  135 + 90 * i, 30, RGB, 1 );
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
	SDL_RenderClear(sdlRenderer);
	mainMenuscreen();
	int RGB[] = {115, 115, 125};
	outputScreen("RANK", 250,  100, 40, RGB, 1 );
	outputScreen("USERNAME", SCREEN_WIDTH / 2,  100, 40, RGB, 1);
	outputScreen("SCORE", SCREEN_WIDTH - 250,  100, 40, RGB, 1 );
	outputScreen("press ESC to backout", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 , 30, RGB, 3 );
	int count = userCount();
	drawbox(MIN(count, 7));
	SDL_RenderPresent(sdlRenderer);
	while (1)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if  (event.type == SDL_QUIT ) {
				TTF_Quit();
				SDL_Quit();
				exit(0);
			}
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				return ;
			}
		}
	}
}

