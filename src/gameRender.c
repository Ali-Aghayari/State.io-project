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

void gamePage()
{
	SDL_Surface *sdlImage = SDL_LoadBMP("res/img/world.bmp");
	if (sdlImage == NULL)
	{
		printf("Unable to load bitmap: %s \n", SDL_GetError());
	}
	SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlImage);
	SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
	SDL_DestroyTexture(sdlTexture);
	SDL_FreeSurface(sdlImage);
}
void printTroopCount(struct State *input)
{
	TTF_Font *font;
	font = TTF_OpenFont("res/pricedown bl.otf", 20);
	if (!font)
	{
		printf("Failed to load font: %s", TTF_GetError());
	}


	SDL_Surface *sdlText;
	SDL_Color color1 = {0, 0, 0};
	SDL_Color color2 = {255, 0, 0};


	int length = snprintf(NULL, 0, "%d", input->troops);
	char *str = malloc(length + 1);
	snprintf(str, length + 1, "%d", input->troops);
	if (input->selected == 0)
	{
		sdlText = TTF_RenderText_Solid(font, str, color1);
	}
	else
	{
		sdlText = TTF_RenderText_Solid(font, str, color2);
	}
	if (!sdlText)
	{
		printf("Failed to render text: %s", TTF_GetError());
	}
	free(str);

	SDL_Texture *textTexture;
	textTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlText);
	SDL_Rect src = {0, 0, sdlText->w, sdlText->h};
	SDL_Rect dest = {MapSize / 2 + input->xArea * MapSize - (sdlText->w) / 2, 20 + MapSize / 2 + input->yArea * MapSize - (sdlText->h) / 2, sdlText->w, sdlText->h};
	SDL_RenderCopy(sdlRenderer, textTexture, &src, &dest);
	TTF_CloseFont(font);
	SDL_FreeSurface(sdlText);
	SDL_DestroyTexture(textTexture);
}

void printAllert(int team , int booster , int mode) {
	char input[255];
	char teamS[15];
	char boosterS[15];
	switch (team) {
	case 1:
		sprintf(teamS, "%s", "RED");
		break;
	case 2:
		sprintf(teamS, "%s", "PURPLE");
		break;
	case 3:
		sprintf(teamS, "%s", "GREEN");
		break;
	case 4:
		sprintf(teamS, "%s", "BLUE");
		break;
	case 5:
		sprintf(teamS, "%s", "YELLOW");
		break;
	default:
		sprintf(teamS, "%s", "--UNKNOWN--");
		break;
	}
	switch (booster) {
	case 1:
		sprintf(boosterS, "%s", "TURTLE");
		break;
	case 2:
		sprintf(boosterS, "%s", "DOUBLE");
		break;
	case 3:
		sprintf(boosterS, "%s", "INFINITY");
		break;
	case 4:
		sprintf(boosterS, "%s", "RABBIT");
		break;
	default:
		sprintf(boosterS, "%s", "--UNKNOWN--");
		break;
	}
	if (mode) { sprintf(input, "team %s got %s booster", teamS, boosterS);}
	else { sprintf(input, "team %s lost %s booster", teamS, boosterS);}
	int RGB[] = {255, 255, 255};
	boxRGBA(sdlRenderer, 150, 90 , SCREEN_WIDTH - 150, SCREEN_HEIGHT - 90, 0, 0, 0, 100);
	outputScreen(input, SCREEN_WIDTH / 2,  SCREEN_HEIGHT / 2 , 40 , RGB, 3 );
}
void loadMap(struct State *input)
{
	char location[] = "res/img/teamX/mapX.bmp";
	location[12] = (char)(48 + input->team);
	location[17] = (char)(48 + input->shape);
	SDL_Surface *sdlImage = SDL_LoadBMP(location);
	if (sdlImage == NULL)
	{
		printf("Unable to load bitmap: %s \n", SDL_GetError());
	}
	SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlImage);
	SDL_Rect SrcR, DestR;
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = MapSize;
	SrcR.h = MapSize;
	DestR.x = input->xArea * MapSize;
	DestR.y = input->yArea * MapSize;
	DestR.w = MapSize;
	DestR.h = MapSize;
	SDL_RenderCopy(sdlRenderer, sdlTexture, &SrcR, &DestR);
	SDL_DestroyTexture(sdlTexture);
	SDL_FreeSurface(sdlImage);
	printTroopCount(input);
}

void loadBooster(struct Booster *input)
{
	char location[] = "res/img/boosters/boosterX.bmp";
	location[24] = (char)(48 + input->mode);
	SDL_Surface *sdlImage = SDL_LoadBMP(location);
	if (sdlImage == NULL)
	{
		printf("Unable to load bitmap: %s \n", SDL_GetError());
	}
	SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlImage);
	SDL_Rect SrcR, DestR;
	SrcR.x = 0;
	SrcR.y = 0;
	SrcR.w = BoosterSize;
	SrcR.h = BoosterSize;
	DestR.x = input->xPos;
	DestR.y = input->yPos;
	DestR.w = BoosterSize;
	DestR.h = BoosterSize;
	SDL_RenderCopy(sdlRenderer, sdlTexture, &SrcR, &DestR);
	SDL_DestroyTexture(sdlTexture);
	SDL_FreeSurface(sdlImage);
}

void makeStates(struct State *states, int groups, int greyStatesCount)
{
	srand(time(NULL));
	int Xmap, Ymap, map[7][5];
	for (int i = 0; i < groups; i++)
	{
		states[i * 2].boostedMode = 0;
		states[i * 2].attackTo = NULL;
		states[i * 2].selected = 0;
		states[i * 2].team = i + 1;
		states[i * 2].shape = rand() % 10;
		states[i * 2].troops = StartingT;
		do
		{
			Xmap = rand() % 7;
			Ymap = rand() % 5;
		} while (map[Xmap][Ymap] == 1);
		map[Xmap][Ymap] = 1;
		states[i * 2].xArea = Xmap;
		states[i * 2].yArea = Ymap;

		states[i * 2 + 1].boostedMode = 0;
		states[i * 2 + 1].attackTo = NULL;
		states[i * 2 + 1].selected = 0;
		states[i * 2 + 1].team = i + 1;
		states[i * 2 + 1].shape = rand() % 10;
		states[i * 2 + 1].troops = StartingT;
		do
		{
			Xmap = rand() % 7;
			Ymap = rand() % 5;
		} while (map[Xmap][Ymap] == 1);
		map[Xmap][Ymap] = 1;
		states[i * 2 + 1].xArea = Xmap;
		states[i * 2 + 1].yArea = Ymap;
	}
	for (int i = 0; i < greyStatesCount; i++)
	{
		states[i + 2 * groups].boostedMode = 0;
		states[i + 2 * groups].attackTo = NULL;
		states[i + 2 * groups].selected = 0;
		states[i + 2 * groups].team = 6;
		states[i + 2 * groups].shape = rand() % 10;
		states[i + 2 * groups].troops = StartingG ;
		do
		{
			Xmap = rand() % 7;
			Ymap = rand() % 5;
		} while (map[Xmap][Ymap] == 1);
		map[Xmap][Ymap] = 1;
		states[i + 2 * groups].xArea = Xmap;
		states[i + 2 * groups].yArea = Ymap;
	}
}
void makeBooster(struct Booster * (boosters[BoostersMax]), struct State *states, int indexBoosters)
{
	srand(time(NULL));
	if (boosters[indexBoosters] == NULL && rand() % 10 == 0)
	{
		int temp1, temp2;
		do
		{
			temp1 = rand() % totalStates;
			temp2 = rand() % totalStates;
		} while (temp1 == temp2);
		int xDiff = ((states + temp2)->xArea * MapSize - (states + temp1)->xArea * MapSize);
		int yDiff = ((states + temp2)->yArea * MapSize - (states + temp1)->yArea * MapSize);
		int controlX = 1, controlY = 1;
		if (xDiff < 0)
		{
			controlX = -1;
		}
		if (yDiff < 0)
		{
			controlY = -1;
		}
		xDiff *= controlX;
		yDiff *= controlY;

		if (xDiff < 10)
			xDiff = 10;
		if (yDiff < 10)
			yDiff = 10;
		int xPosi = (states + temp1)->xArea * MapSize + HalfSize + controlX * (rand() % (xDiff));
		int yPosi = (states + temp1)->yArea * MapSize + HalfSize + controlY * (rand() % (yDiff));
		boosters[indexBoosters] = (struct Booster *)malloc(sizeof(struct Booster));
		boosters[indexBoosters]->mode = rand() % 4 + 1;
		boosters[indexBoosters]->xPos = xPosi;
		boosters[indexBoosters]->yPos = yPosi;
		boosters[indexBoosters]->teamOnIt[0] = 0;
		boosters[indexBoosters]->teamOnIt[1] = 0;
		boosters[indexBoosters]->teamOnIt[2] = 0;
		boosters[indexBoosters]->teamOnIt[3] = 0;
		boosters[indexBoosters]->teamOnIt[4] = 0;
		boosters[indexBoosters]->teamOnIt[5] = 0;
		boosters[indexBoosters]->timeLimit = BoosterTime;
	}
}
int makeTroops(struct Troop * (troops[TroopsMax]), struct State *states, int indexTroops, int reverseBoostFlag) {
	int control = 0;
	for (int i = 0; i < totalStates; ++i)
	{
		if ((states + i)->attackTo != NULL)
		{
			if ((states + i)->troops > 0 && (states + i)->attackCount > 0)
			{
				(states + i)->troops--;
				(states + i)->attackCount--;
			}
			else
			{
				(states + i)->attackTo = NULL;
				continue;
			}
			float xPos, yPos, Vx, Vy;
			int team, xEnd, yEnd;
			team = (states + i)->team;
			xPos = (states + i)->xArea * MapSize + HalfSize;
			yPos = (states + i)->yArea * MapSize + HalfSize;
			xEnd = (states + i)->attackTo->xArea * MapSize + HalfSize;
			yEnd = (states + i)->attackTo->yArea * MapSize + HalfSize;
			Vx = Sorat * ((states + i)->attackTo->xArea - (states + i)->xArea) / sqrt(((states + i)->xArea - (states + i)->attackTo->xArea) * ((states + i)->xArea - (states + i)->attackTo->xArea) + ((states + i)->yArea - (states + i)->attackTo->yArea) * ((states + i)->yArea - (states + i)->attackTo->yArea));
			Vy = Sorat * ((states + i)->attackTo->yArea - (states + i)->yArea) / sqrt(((states + i)->xArea - (states + i)->attackTo->xArea) * ((states + i)->xArea - (states + i)->attackTo->xArea) + ((states + i)->yArea - (states + i)->attackTo->yArea) * ((states + i)->yArea - (states + i)->attackTo->yArea));
			if ((states + i)->boostedMode == 4) { Vx *= 2; Vy *= 2;}
			if (reverseBoostFlag != 0 && (states + i)->boostedMode != 1) { Vx /= 2; Vy /= 2;}
			troops[indexTroops] = (struct Troop *)malloc(sizeof(struct Troop));
			troops[indexTroops]->boostedMode = (states + i)->boostedMode;
			troops[indexTroops]->attackTo = (states + i)->attackTo;
			troops[indexTroops]->team = team;
			troops[indexTroops]->xPos = xPos - 5;
			troops[indexTroops]->yPos = yPos - 5;
			troops[indexTroops]->xEnd = xEnd - 5;
			troops[indexTroops]->yEnd = yEnd - 5;
			troops[indexTroops]->Vx = Vx;
			troops[indexTroops]->Vy = Vy;
			do {
				indexTroops++;
				control++;
				indexTroops %= TroopsMax;
			} while (troops[indexTroops] != NULL);

			if ((states + i)->troops > 0 && (states + i)->attackCount > 0)
			{
				(states + i)->troops--;
				(states + i)->attackCount--;
			}
			else
			{
				(states + i)->attackTo = NULL;
				continue;
			}
			troops[indexTroops] = (struct Troop *)malloc(sizeof(struct Troop));
			troops[indexTroops]->boostedMode = (states + i)->boostedMode;
			troops[indexTroops]->attackTo = (states + i)->attackTo;
			troops[indexTroops]->team = team;
			troops[indexTroops]->xPos = xPos + 5;
			troops[indexTroops]->yPos = yPos + 5;
			troops[indexTroops]->xEnd = xEnd + 5;
			troops[indexTroops]->yEnd = yEnd + 5;
			troops[indexTroops]->Vx = Vx;
			troops[indexTroops]->Vy = Vy;
			do {
				indexTroops++;
				control++;
				indexTroops %= TroopsMax;
			} while (troops[indexTroops] != NULL);

			if ((states + i)->troops > 0 && (states + i)->attackCount > 0)
			{
				(states + i)->troops--;
				(states + i)->attackCount--;
			}
			else
			{
				(states + i)->attackTo = NULL;
				continue;
			}
			troops[indexTroops] = (struct Troop *)malloc(sizeof(struct Troop));
			troops[indexTroops]->boostedMode = (states + i)->boostedMode;
			troops[indexTroops]->attackTo = (states + i)->attackTo;
			troops[indexTroops]->team = team;
			troops[indexTroops]->xPos = xPos - 5;
			troops[indexTroops]->yPos = yPos + 5;
			troops[indexTroops]->xEnd = xEnd - 5;
			troops[indexTroops]->yEnd = yEnd + 5;
			troops[indexTroops]->Vx = Vx;
			troops[indexTroops]->Vy = Vy;
			do {
				indexTroops++;
				control++;
				indexTroops %= TroopsMax;
			} while (troops[indexTroops] != NULL);

			if ((states + i)->troops > 0 && (states + i)->attackCount > 0)
			{
				(states + i)->troops--;
				(states + i)->attackCount--;
			}
			else
			{
				(states + i)->attackTo = NULL;
				continue;
			}
			troops[indexTroops] = (struct Troop *)malloc(sizeof(struct Troop));
			troops[indexTroops]->boostedMode = (states + i)->boostedMode;
			troops[indexTroops]->attackTo = (states + i)->attackTo;
			troops[indexTroops]->team = team;
			troops[indexTroops]->xPos = xPos + 5;
			troops[indexTroops]->yPos = yPos - 5;
			troops[indexTroops]->xEnd = xEnd + 5;
			troops[indexTroops]->yEnd = yEnd - 5;
			troops[indexTroops]->Vx = Vx;
			troops[indexTroops]->Vy = Vy;
			do {
				indexTroops++;
				control++;
				indexTroops %= TroopsMax;
			} while (troops[indexTroops] != NULL);
		}
	}
	return control;
}
void boosterTimer(struct Booster * (boosters[BoostersMax])) {
	for (int i = 0; i < BoostersMax; ++i)
	{
		if (boosters[i] == NULL)
		{
			continue;
		}
		if (boosters[i]->timeLimit <= 0)
		{
			free(*(boosters + i));
			boosters[i] = NULL;
			continue;
		}
		else
		{
			boosters[i]->timeLimit -= 1;
			loadBooster(*(boosters + i));
		}
	}

}
void troopsMoveAndPrint(struct Troop * (troops[TroopsMax])) {
	for (int i = 0; i < TroopsMax; ++i)
	{
		if (troops[i] != NULL)
		{
			if (troops[i]->team == 1)filledEllipseRGBA(sdlRenderer, troops[i]->xPos, troops[i]->yPos, 3, 3, 100, 0, 0, 255);
			if (troops[i]->team == 2)filledEllipseRGBA(sdlRenderer, troops[i]->xPos, troops[i]->yPos, 3, 3, 0, 100, 0 , 255);
			if (troops[i]->team == 3)filledEllipseRGBA(sdlRenderer, troops[i]->xPos, troops[i]->yPos, 3, 3, 0, 0, 100, 255);
			if (troops[i]->team == 4)filledEllipseRGBA(sdlRenderer, troops[i]->xPos, troops[i]->yPos, 3, 3, 100, 0, 100, 255);
			if (troops[i]->team == 5)filledEllipseRGBA(sdlRenderer, troops[i]->xPos, troops[i]->yPos, 3, 3, 100, 100, 0, 255);

			troops[i]->xPos += troops[i]->Vx;
			troops[i]->yPos += troops[i]->Vy;
			if ((troops[i]->xPos - troops[i]->xEnd) < 3 && (troops[i]->xPos - troops[i]->xEnd) > -3 && (troops[i]->yPos - troops[i]->yEnd) < 3 && (troops[i]->yPos - troops[i]->yEnd) > -3)
			{

				if (troops[i]->team == troops[i]->attackTo->team)
				{
					troops[i]->attackTo->troops++;
				}
				else
				{
					troops[i]->attackTo->troops--;
					if (troops[i]->attackTo->troops == -1)
					{
						troops[i]->attackTo->troops = 1;
						troops[i]->attackTo->team = troops[i]->team;
						troops[i]->attackTo->boostedMode = troops[i]->boostedMode;
						troops[i]->attackTo->attackTo = NULL;
					}
				}
				free(*(troops + i));
				troops[i] = NULL;
			}
		}
	}
}
void myAI(struct State *states) {
	srand(time(NULL));
	int random;
	for (int m = 0; m < totalStates; m++)
	{
		if ((states + m)->team == MyTeam || (states + m)->team == GreyTeam || (states + m)->attackTo != NULL) {continue;}
		else if ((states + m)->troops > 45 && rand() % 2 == 0 ) {
			do {
				random = rand() % totalStates;
			} while (random == m);
			(states + m)->attackTo = (states + random);
		}
		else if ( rand() % 2 == 0) {continue;}
		else if ((states + m)->troops >  MaxInState * 4 / 5) {
			random = rand() % totalStates;
			if ((states + m)->troops - (states + random)->troops > 5 && (states + m)->team != (states + random)->team ) {
				(states + m)->attackTo = (states + random);
			} else if (rand() % 100 == 0) {
				(states + m)->attackTo = (states + random);
			}
		}
		else if ((states + m)->troops >  MaxInState * 3 / 5) {
			random = rand() % totalStates;
			if ((states + m)->troops - (states + random)->troops > 5 && (states + m)->team != (states + random)->team ) {
				(states + m)->attackTo = (states + random);
			} else if (rand() % 100 == 0) {
				(states + m)->attackTo = (states + random);
			}
		}
		else if ((states + m)->troops >  MaxInState * 2 / 5) {
			random = rand() % totalStates;
			if ((states + m)->troops - (states + random)->troops > 5 && (states + m)->team != (states + random)->team ) {
				(states + m)->attackTo = (states + random);
			} else if (rand() % 100 == 0) {
				(states + m)->attackTo = (states + random);
			}
		}

	}

}

void readTroop(struct Troop * (troops[TroopsMax]), struct State *states, int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "T.txt");
	int control = 0;
	int team, xEnd, yEnd, boostedMode, indexOfState;
	float Vx, xPos, Vy, yPos;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %f %f %f %f %d %d %d %d", &team, &xPos, &yPos, &Vx, &Vy, &xEnd, &yEnd, &boostedMode, &indexOfState);
		troops[control] = (struct Troop *)malloc(sizeof(struct Troop));
		troops[control]->team = team;
		troops[control]->xPos = xPos;
		troops[control]->yPos = yPos;
		troops[control]->Vx = Vx;
		troops[control]->Vy = Vy;
		troops[control]->yEnd = yEnd;
		troops[control]->xEnd = xEnd;
		troops[control]->boostedMode = boostedMode;
		troops[control]->attackTo = (states + indexOfState);
		control++;
	}
	fclose(dataBase);
}
void writeTroop(struct Troop * (troops[TroopsMax]), struct State *states, int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "T.txt");
	int index;
	FILE *dataBase = fopen(string, "w");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	for (int i = 0; i < TroopsMax; ++i)
	{
		if (troops[i] == NULL)
		{
			continue;
		}
		for (int j = 0; j < totalStates; ++j)
		{
			if (troops[i]->attackTo == (states + j))
			{
				index = j;
				break;
			}
		}
		fprintf(dataBase, "%d %f %f %f %f %d %d %d %d\n", troops[i]->team, troops[i]->xPos, troops[i]->yPos, troops[i]->Vx, troops[i]->Vy, troops[i]->xEnd, troops[i]->yEnd, troops[i]->boostedMode, index);
	}
	fclose(dataBase);
}
void writeMap(struct State *states, int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "S.txt");
	int index;
	FILE *dataBase = fopen(string, "w");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	for (int i = 0; i < totalStates; ++i)
	{
		index = -1;
		if ((states + i)->attackTo != NULL)
		{
			for (int j = 0; j < totalStates; ++j)
			{
				if ((states + i)->attackTo == (states + j))
				{
					index = j;
					break;
				}
			}
		}
		fprintf(dataBase, "%d %d %d %d %d %d %d %d %d\n", (states + i)->team, (states + i)->shape, (states + i)->troops, (states + i)->xArea, (states + i)->yArea, (states + i)->selected, (states + i)->attackCount, (states + i)->boostedMode, index);
	}
	fclose(dataBase);
}
void readMap(struct State *states, int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "S.txt");
	int team, shape, troops, xArea, yArea, selected, attackCount, boostedMode, indexOfState, control = 0;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %d %d %d %d %d %d %d %d", &team, &shape, &troops, &xArea, &yArea, &selected, &attackCount, &boostedMode, &indexOfState);
		(states + control)->team = team;
		(states + control)->shape = shape;
		(states + control)->troops = troops;
		(states + control)->xArea = xArea;
		(states + control)->yArea = yArea;
		(states + control)->selected = selected;
		(states + control)->attackCount = attackCount;
		(states + control)->boostedMode = boostedMode;
		if (indexOfState == -1) {(states + control)->attackTo = NULL;}
		else {(states + control)->attackTo = (states + indexOfState);}
		control++;
	}
	fclose(dataBase);
}
void readBooster(struct Booster * (boosters[BoostersMax]), int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "B.txt");
	int index, mode, timelimit, xPos, yPos, team[6];
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %d %d %d %d %d %d %d %d %d %d", &index, &mode, &timelimit, &xPos, &yPos, team + 0, team + 1, team + 2, team + 3, team + 4, team + 5);
		boosters[index] = (struct Booster *)malloc(sizeof(struct Booster));
		boosters[index]->mode = mode;
		boosters[index]->timeLimit = timelimit;
		boosters[index]->xPos = xPos;
		boosters[index]->yPos = yPos;
		for (int i = 0; i < 6; i++)
		{
			boosters[index]->teamOnIt[i] = team[i];
		}
	}
	fclose(dataBase);
}
void writeBooster(struct Booster * (boosters[BoostersMax]), int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "B.txt");

	FILE *dataBase = fopen(string, "w");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	for (int i = 0; i < BoostersMax; i++)
	{
		if (boosters[i] == NULL)
		{
			continue;
		}
		fprintf(dataBase, "%d %d %d %d %d %d %d %d %d %d %d\n", i, boosters[i]->mode, boosters[i]->timeLimit, boosters[i]->xPos, boosters[i]->yPos, boosters[i]->teamOnIt[0], boosters[i]->teamOnIt[1], boosters[i]->teamOnIt[2], boosters[i]->teamOnIt[3], boosters[i]->teamOnIt[4], boosters[i]->teamOnIt[5]);
	}
	fclose(dataBase);
}
void readOnlineBooster(struct OnlineBooster * (onlineBoosters[OnlineBoostersMax]), int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "O.txt");
	int index, mode, timer;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %d %d", &index, &mode, &timer);
		onlineBoosters[index] = (struct OnlineBooster *)malloc(sizeof(struct OnlineBooster));
		onlineBoosters[index]->mode = mode;
		onlineBoosters[index]->timer = timer;
	}
	fclose(dataBase);
}

void writeOnlineBooster(struct OnlineBooster * (onlineBoosters[OnlineBoostersMax]), int id)
{
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "O.txt");
	FILE *dataBase = fopen(string, "w");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	for (int i = 0; i < OnlineBoostersMax; i++)
	{
		if (onlineBoosters[i] == NULL)
		{
			continue;
		}
		fprintf(dataBase, "%d %d %d\n", i, onlineBoosters[i]->mode, onlineBoosters[i]->timer);
	}
	fclose(dataBase);
}
int CountStates(int id) {
	char temp[5];
	char string [50] = "res/DataBase/";
	sprintf(temp, "%d", id);
	strcat(string, temp);
	strcat(string, "S.txt");
	int stateCount = 0;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		stateCount++;
	}
	fclose(dataBase);
	return stateCount;
}

void endGame(int id, int mode, int socreChange) {
	SDL_RenderClear(sdlRenderer);
	if (mode == 1) {
		SDL_Surface* sdlImage = SDL_LoadBMP("res/img/win.bmp");
		if (sdlImage == NULL) {printf("Unable to load bitmap: %s \n", SDL_GetError());}
		SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlImage);
		SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
		SDL_DestroyTexture(sdlTexture);
		SDL_FreeSurface(sdlImage);
	}
	else if (mode == 0) {
		SDL_Surface* sdlImage = SDL_LoadBMP("res/img/lose.bmp");
		if (sdlImage == NULL) {printf("Unable to load bitmap: %s \n", SDL_GetError());}
		SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlImage);
		SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, NULL);
		SDL_DestroyTexture(sdlTexture);
		SDL_FreeSurface(sdlImage);
	}

	int RGB[] = {200, 0, 0};
	outputScreen("press ESC to get back to main menu", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 , 20, RGB, 3 );
	// slkadflaskdjfsfskdkljfd	
	SDL_RenderPresent(sdlRenderer);
	while (1)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if  (event.type == SDL_QUIT ) {
				SDL_Quit();
			}
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				/// get back to main menu
			}
		}
	}
}

void saveRandomMap(struct State *states, int name) {
	char temp[5];
	char string [50] = "res/DataBase/SavedMaps/";
	sprintf(temp, "%d", name);
	strcat(string, temp);
	strcat(string, "S.txt");
	int index;
	FILE *dataBase = fopen(string, "w");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
	}
	for (int i = 0; i < totalStates; ++i)
	{
		index = -1;
		if ((states + i)->attackTo != NULL)
		{
			for (int j = 0; j < totalStates; ++j)
			{
				if ((states + i)->attackTo == (states + j))
				{
					index = j;
					break;
				}
			}
		}
		fprintf(dataBase, "%d %d %d %d %d %d %d %d %d\n", (states + i)->team, (states + i)->shape, (states + i)->troops, (states + i)->xArea, (states + i)->yArea, (states + i)->selected, (states + i)->attackCount, (states + i)->boostedMode, index);
	}
	fclose(dataBase);
}
int CountRandomSave(int name) {
	char temp[5];
	char string [50] = "res/DataBase/SavedMaps/";
	sprintf(temp, "%d", name);
	strcat(string, temp);
	strcat(string, "S.txt");
	int stateCount = 0;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		stateCount++;
	}
	fclose(dataBase);
	return stateCount;
}
void readRandomMap(struct State *states, int name) {
	char temp[5];
	char string [50] = "res/DataBase/SavedMaps/";
	sprintf(temp, "%d", name);
	strcat(string, temp);
	strcat(string, "S.txt");
	int team, shape, troops, xArea, yArea, selected, attackCount, boostedMode, indexOfState, control = 0;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %d %d %d %d %d %d %d %d", &team, &shape, &troops, &xArea, &yArea, &selected, &attackCount, &boostedMode, &indexOfState);
		(states + control)->team = team;
		(states + control)->shape = shape;
		(states + control)->troops = troops;
		(states + control)->xArea = xArea;
		(states + control)->yArea = yArea;
		(states + control)->selected = selected;
		(states + control)->attackCount = attackCount;
		(states + control)->boostedMode = boostedMode;
		if (indexOfState == -1) {(states + control)->attackTo = NULL;}
		else {(states + control)->attackTo = (states + indexOfState);}
		control++;
	}
	fclose(dataBase);
}
int ReadyMapCount(int map) {
	char temp[5];
	char string [50] = "res/DataBase/ReadyMaps/map";
	sprintf(temp, "%d", map);
	strcat(string, temp);
	strcat(string, ".txt");
	int stateCount = 0;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		stateCount++;
	}
	fclose(dataBase);
	return stateCount;
}
void ReadyMapOpen(struct State *states, int map) {
	char temp[5];
	char string [50] = "res/DataBase/ReadyMaps/map";
	sprintf(temp, "%d", map);
	strcat(string, temp);
	strcat(string, ".txt");
	int team, shape, troops, xArea, yArea, selected, attackCount, boostedMode, indexOfState, control = 0;
	FILE *dataBase = fopen(string, "r");
	if (dataBase == NULL)
	{
		printf("Error openning Files\n");
		return;
	}
	char line[256];
	while (fgets(line, 256, dataBase) != NULL)
	{
		sscanf(line, " %d %d %d %d %d %d %d %d %d", &team, &shape, &troops, &xArea, &yArea, &selected, &attackCount, &boostedMode, &indexOfState);
		(states + control)->team = team;
		(states + control)->shape = shape;
		(states + control)->troops = troops;
		(states + control)->xArea = xArea;
		(states + control)->yArea = yArea;
		(states + control)->selected = selected;
		(states + control)->attackCount = attackCount;
		(states + control)->boostedMode = boostedMode;
		if (indexOfState == -1) {(states + control)->attackTo = NULL;}
		else {(states + control)->attackTo = (states + indexOfState);}
		control++;
	}
	fclose(dataBase);
}
void gameSetup(int newOrOld , int id, int map , int G , int S , int RandSave)
{
	struct State *states;
	int counterPrint = 0 , teamPrint = -1 , boosterPrint = -1, modePrint = -1;
	struct Booster *(boosters[BoostersMax]);
	struct Troop *(troops[TroopsMax]);
	struct OnlineBooster *(onlineBoosters[OnlineBoostersMax]);
	for (int i = 0; i < OnlineBoostersMax; ++i) {onlineBoosters[i] = NULL;}
	for (int i = 0; i < TroopsMax; ++i) {troops[i] = NULL;}
	for (int i = 0; i < BoostersMax; ++i) {boosters[i] = NULL;}

//////////////////////////////////////////////////////////////////////////
	if (newOrOld == 1 && map == 3) {
		int groups = G;
		int greyStatesCount = S;
		totalStates = 2 * groups + greyStatesCount;
		states = (struct State *)malloc(sizeof(struct State) * totalStates);
		makeStates(states, groups, greyStatesCount);
		if (RandSave != -1) {saveRandomMap(states, RandSave);}
	}
	else if (newOrOld == 1 && map == 4) {
		totalStates = CountRandomSave(RandSave);
		states = (struct State *)malloc(sizeof(struct State) * totalStates);
		readRandomMap(states, RandSave);
	}
	else if (newOrOld == 1) {
		totalStates = ReadyMapCount(map);
		states = (struct State *)malloc(sizeof(struct State) * totalStates);
		ReadyMapOpen(states, map);
	}
	else if (newOrOld == 2) {
		totalStates = CountStates(id);
		states = (struct State *)malloc(sizeof(struct State) * totalStates);
		readMap(states, id);
		readTroop(troops, states, id);
		readBooster(boosters, id);
		readOnlineBooster(onlineBoosters, id);
	}
///////////////////////////////////////////////////////////////////////
	int slowFlag = 0;
	int indexTroops = 0, indexBoosters = 0;
	int loopCounter = 0, xMouse, yMouse, selectedState = -1, mouseOverState = -1, mouseDown = 0;
	int lose  , win  ;
	clock_t before = clock ();
	int Mmin = 0;
	while (1)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			xMouse = event.motion.x / (MapSize);
			yMouse = event.motion.y / (MapSize);
			if (event.type == SDL_QUIT)
			{
				writeMap(states, id);
				writeTroop(troops, states, id);
				writeBooster(boosters, id);
				writeOnlineBooster(onlineBoosters, id);
				// Mix_Quit();
				// TTF_Quit();
				/////////////////////////////////??!?!
				SDL_Quit();
			}
			else if (event.type == SDL_MOUSEBUTTONDOWN)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					for (int i = 0; i < totalStates; i++)
					{
						if ((states + i)->team == MyTeam && (states + i)->xArea == xMouse && (states + i)->yArea == yMouse)
						{
							selectedState = i;
							mouseDown = 1;
							(states + i)->selected = 1;
							break;
						}
					}
				}
			}
			else if (event.type == SDL_MOUSEBUTTONUP)
			{
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					mouseDown = 0;
					for (int i = 0; i < totalStates; ++i)
					{
						if ((states + i)->xArea == xMouse && (states + i)->yArea == yMouse && i != selectedState)
						{
							(states + selectedState)->attackTo = (states + i);
							(states + selectedState)->attackCount = (states + selectedState)->troops;
						}
					}
					if (selectedState != -1)
						(states + selectedState)->selected = 0;
					if (mouseOverState != -1)
						(states + mouseOverState)->selected = 0;
				}
			}
		}
		if (mouseDown)
		{
			int flag = 1;
			for (int i = 0; i < totalStates; i++)
			{
				if ((states + i)->xArea == xMouse && (states + i)->yArea == yMouse)
				{
					if (mouseOverState != -1)
						(states + mouseOverState)->selected = 0;
					if (i != selectedState)
						mouseOverState = i;
					(states + i)->selected = 1;
					flag = 0;
					break;
				}
			}
			if (flag)
			{
				(states + mouseOverState)->selected = 0;
			}
		}
		loopCounter++;
		SDL_RenderClear(sdlRenderer);
		gamePage();
		if (loopCounter > Speed)
		{
			for (int i = 0; i < totalStates; ++i)
			{
				if ( (states + i)->team != GreyTeam && ((states + i)->troops < MaxInState ||  (states + i)->boostedMode == 3 )) {
					(states + i)->troops++;
					if ((states + i)->boostedMode == 2 && (states + i)->troops < MaxInState) {(states + i)->troops++;}
				}
				else if ( (states + i)->team == GreyTeam && (states + i)->troops < StartingG)
				{
					(states + i)->troops++;
				}
				loadMap(states + i);
			}
			makeBooster(boosters, states, indexBoosters);
			indexBoosters++;
			indexBoosters %= BoostersMax;
			indexTroops += makeTroops(troops, states, indexTroops, slowFlag);
			indexTroops %= TroopsMax;
			loopCounter -= Speed;
		}
		else
		{
			for (int i = 0; i < totalStates; ++i)
			{
				loadMap(states + i);
			}
		}
		myAI(states);
		boosterTimer(boosters);
		/////////////////////////////////////

		for (int i = 0; i < TroopsMax; ++i)
		{
			if (troops[i] == NULL)
			{
				continue;
			}
			int flag = 0;
			for (int j = i + 1; j < TroopsMax; ++j)
			{
				if (troops[j] == NULL)
				{
					continue;
				}
				if (troops[i]->team != troops[j]->team && !(troops[i]->yPos + 3 <= troops[j]->yPos - 3) && !(troops[i]->yPos - 3 >= troops[j]->yPos + 3) && !(troops[i]->xPos + 3 <= troops[j]->xPos - 3) && !(troops[i]->xPos - 3 >= troops[j]->xPos + 3))
				{
					free(*(troops + j));
					troops[j] = NULL;
					flag = 1;
				}
			}
			if (flag)
			{
				free(*(troops + i));
				troops[i] = NULL;
				continue;
			}
			for (int k = 0; k < BoostersMax; ++k)
			{
				if (boosters[k] == NULL)
				{
					continue;
				}
				if (!(troops[i]->yPos + 3 <= boosters[k]->yPos) && !(troops[i]->yPos - 3 >= boosters[k]->yPos + 32) && !(troops[i]->xPos + 3 <= boosters[k]->xPos) && !(troops[i]->xPos - 3 >= boosters[k]->xPos + 32))
				{
					int team = troops[i]->team  ;
					boosters[k]->teamOnIt[team]++;
					if (boosters[k]->teamOnIt[team] > BoosterDeff)
					{
						if (onlineBoosters[team] != NULL) {continue;}  // bemoone ya na ?
						onlineBoosters[team] = (struct OnlineBooster *)malloc(sizeof(struct OnlineBooster));
						onlineBoosters[team]-> mode = boosters[k]->mode;
						onlineBoosters[team]-> timer = BoosterTime;
						free(*(boosters + k));
						boosters[k] = NULL;
						counterPrint = AllertTime;
						boosterPrint =  onlineBoosters[team]-> mode;
						modePrint = 1;
						teamPrint = team;
						for (int i = 0; i < totalStates; ++i)
						{
							if ((states + i)->team == team) {
								(states + i)->boostedMode = onlineBoosters[team]-> mode;
							}
						}
						if (onlineBoosters[team]-> mode == 4) {

							for (int i = 0; i < TroopsMax; ++i)
							{
								if ( troops[i] != NULL && (troops[i]->team == team)) {
									troops[i]->boostedMode = onlineBoosters[team]->mode;
									troops[i]->Vx *= 2;
									troops[i]->Vy *= 2;
								}
							}
						}
						if (onlineBoosters[team]-> mode == 1) {
							for (int i = 0; i < TroopsMax; ++i)
							{
								if (troops[i] == NULL ) {continue;}
								if ((troops[i]->team != team)) {
									troops[i]->Vx /= 2;
									troops[i]->Vy /= 2;
								} else {troops[i]->boostedMode = onlineBoosters[team]->mode;}

							}
						}

					}
				}
			}
		}
		slowFlag = 0 ;
		for (int j = 0; j < OnlineBoostersMax; ++j)
		{
			if (onlineBoosters[j] == NULL) {continue;}
			if (onlineBoosters[j]->timer < 2) {
				for (int i = 0; i < totalStates; ++i)
				{
					if ((states + i)->team == j) {
						(states + i)->boostedMode = 0;
					}
				}
				if (onlineBoosters[j]->mode == 4) {
					for (int i = 0; i < TroopsMax; ++i)
					{
						if (troops[i] != NULL && troops[i]->team == j) {
							troops[i]->boostedMode = 0;
							troops[i]->Vx /= 2;
							troops[i]->Vy /= 2;
						}
					}
				}
				if (onlineBoosters[j]->mode == 1) {
					for (int i = 0; i < TroopsMax; ++i)
					{
						if (troops[i] == NULL) {continue;}
						if (troops[i]->team == j) {
							troops[i]->boostedMode = 0;
						} else {
							troops[i]->Vx *= 2;
							troops[i]->Vy *= 2;
						}
					}
				}
				counterPrint = AllertTime ;
				teamPrint = j;
				boosterPrint =  onlineBoosters[j]-> mode;
				modePrint = 0;
				free(*(onlineBoosters + j));
				onlineBoosters[j] = NULL;
			}
			else {
				onlineBoosters[j]->timer--;
				if (onlineBoosters[j]->mode == 1) {slowFlag++;}
			}
		}
		if (counterPrint > 0 &&  teamPrint != -1 && boosterPrint != -1 && modePrint != -1 ) {
			printAllert(teamPrint, boosterPrint, modePrint);
			counterPrint--;
		}
		troopsMoveAndPrint(troops);
		SDL_RenderPresent(sdlRenderer);


		lose = 1, win = 1;
		for (int i = 0; i < totalStates; ++i)
		{
			if (!(win || lose)) {break;}
			if ((states + i)->team == MyTeam) {lose = 0;}
			else if ((states + i)->team != MyTeam && (states + i)->team != GreyTeam) {win = 0;}
		}
		if (lose) {
			// score -> 20 percent and -200
			endGame(id, 0, 120);
		}
		if (win) {
			// score -> total troops / 2 + total states * 4 + 2000/minute
			clock_t difference = clock () - before;
			Mmin = difference * 1000 / CLOCKS_PER_SEC / 60;
			// 
			/// 2000 / ( Mmin + 1 )
			// esc for backing out
			endGame(id, 1, 120);

		}

	}
}