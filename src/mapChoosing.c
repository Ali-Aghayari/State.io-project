#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdio.h>

#include "globalVariable.h"
#include "welcomePageRender.h"
#include "menuPageRender.h"
#include "gameRender.h"




void writeOnScreenForMaps(int mode1, int mode2, int mode3, int mode4) {
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 100, SCREEN_WIDTH / 2 + 250, 220, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 230, SCREEN_WIDTH / 2 + 250, 350, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 360, SCREEN_WIDTH / 2 + 250, 480, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 490, SCREEN_WIDTH / 2 + 250, 610, 0, 0, 0, 100);
	int RGB[] = {100, 100, 100};
	outputScreen("MAP 1", SCREEN_WIDTH / 2 , 160, 130 - 30 * mode1 , RGB, mode1);
	outputScreen("MAP 2", SCREEN_WIDTH / 2 , 290, 130 - 30 * mode2 , RGB, mode2);
	outputScreen("RANDOM", SCREEN_WIDTH / 2 , 420, 130 - 30 * mode3 , RGB, mode3);
	outputScreen("SAVED MAPS", SCREEN_WIDTH / 2 , 550, 130 - 30 * mode4 , RGB, mode4);
}
void writeOnScreenForGroups(int mode1, int mode2, int mode3, int mode4) {
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 100, SCREEN_WIDTH / 2 + 250, 220, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 230, SCREEN_WIDTH / 2 + 250, 350, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 360, SCREEN_WIDTH / 2 + 250, 480, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 490, SCREEN_WIDTH / 2 + 250, 610, 0, 0, 0, 100);
	int RGB[] = {100, 100, 100};
	outputScreen("2", SCREEN_WIDTH / 2 , 160, 130 - 30 * mode1 , RGB, mode1);
	outputScreen("3", SCREEN_WIDTH / 2 , 290, 130 - 30 * mode2 , RGB, mode2);
	outputScreen("4", SCREEN_WIDTH / 2 , 420, 130 - 30 * mode3 , RGB, mode3);
	outputScreen("5", SCREEN_WIDTH / 2 , 550, 130 - 30 * mode4 , RGB, mode4);
}
void writeOnScreenForStates(int mode1, int mode2, int mode3, int mode4, int mode5) {
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 100, SCREEN_WIDTH / 2 + 250, 220, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 230, SCREEN_WIDTH / 2 + 250, 350, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 360, SCREEN_WIDTH / 2 + 250, 480, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 490, SCREEN_WIDTH / 2 + 250, 610, 0, 0, 0, 100);
	boxRGBA(sdlRenderer, SCREEN_WIDTH / 2 - 250, 620, SCREEN_WIDTH / 2 + 250, 730, 0, 0, 0, 100);
	int RGB[] = {100, 100, 100};
	outputScreen("6", SCREEN_WIDTH / 2 , 160, 130 - 30 * mode1 , RGB, mode1);
	outputScreen("9", SCREEN_WIDTH / 2 , 290, 130 - 30 * mode2 , RGB, mode2);
	outputScreen("12", SCREEN_WIDTH / 2 , 420, 130 - 30 * mode3 , RGB, mode3);
	outputScreen("15", SCREEN_WIDTH / 2 , 550, 130 - 30 * mode4 , RGB, mode4);
	outputScreen("18", SCREEN_WIDTH / 2 , 680, 130 - 30 * mode4 , RGB, mode4);

}
int mapChoosePreSetup() {
	int RGB1[] = {115, 115, 125};
	int mode1, mode2, mode3, mode4;
	writeOnScreenForMaps(1, 1, 1, 1);
	SDL_RenderPresent(sdlRenderer);
	int running = 1;
	int xMouse, yMouse;
	mainMenuscreen();
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			mode1 = 1; mode2 = 1; mode3 = 1; mode4 = 1;
			xMouse = event.motion.x;
			yMouse = event.motion.y;
			if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 100 < yMouse && yMouse < 220) {
				mode1 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 1;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 230 < yMouse && yMouse < 350) {
				mode2 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 2;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 360 < yMouse && yMouse < 480) {
				mode3 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 3;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 490 < yMouse && yMouse < 610) {
				mode4 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 4;}
			}
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				return 0;
			}
			if  (event.type == SDL_QUIT) {
				TTF_Quit();
				SDL_Quit();
				exit(0);
			}

		}
		SDL_RenderClear(sdlRenderer);
		mainMenuscreen();
		writeOnScreenForMaps(mode1, mode2, mode3, mode4);
		if (mode1 == 3) {
			char location[] = "res/img/map1.bmp";
			SDL_Surface *sdlImage = SDL_LoadBMP(location);
			if (sdlImage == NULL)
			{
				printf("Unable to load bitmap: %s \n", SDL_GetError());
			}
			SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlImage);
			SDL_Rect  DestR;
			DestR.x = SCREEN_WIDTH / 2 - 175;
			DestR.y = 620;
			DestR.h = 175;
			DestR.w = 350;
			SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &DestR);
			SDL_DestroyTexture(sdlTexture);
			SDL_FreeSurface(sdlImage);
		}
		if (mode2 == 3) {
			char location[] = "res/img/map2.bmp";
			SDL_Surface *sdlImage = SDL_LoadBMP(location);
			if (sdlImage == NULL)
			{
				printf("Unable to load bitmap: %s \n", SDL_GetError());
			}
			SDL_Texture *sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, sdlImage);
			SDL_Rect DestR;
			DestR.x = SCREEN_WIDTH / 2 - 175;
			DestR.y = 620;
			DestR.h = 175;
			DestR.w = 350;
			SDL_RenderCopy(sdlRenderer, sdlTexture, NULL, &DestR);
			SDL_DestroyTexture(sdlTexture);
			SDL_FreeSurface(sdlImage);
		}
		outputScreen("press ESC to backout", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 , 30, RGB1, 3 );
		SDL_RenderPresent(sdlRenderer);
	}
	return -1;
}
int howManyGroups() {
	int RGB[] = {120, 120, 120};
	int RGB1[] = {115, 115, 125};
	int mode1, mode2, mode3, mode4;
	writeOnScreenForMaps(1, 1, 1, 1);
	SDL_RenderPresent(sdlRenderer);
	int running = 1;
	int xMouse, yMouse;
	mainMenuscreen();
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			mode1 = 1; mode2 = 1; mode3 = 1; mode4 = 1;
			xMouse = event.motion.x;
			yMouse = event.motion.y;
			if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 100 < yMouse && yMouse < 220) {
				mode1 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 2;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 230 < yMouse && yMouse < 350) {
				mode2 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 3;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 360 < yMouse && yMouse < 480) {
				mode3 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 4;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 490 < yMouse && yMouse < 610) {
				mode4 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 5;}
			}
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				return 0;
			}
			if  (event.type == SDL_QUIT) {
				TTF_Quit();
				SDL_Quit();
				exit(0);
			}
		}
		SDL_RenderClear(sdlRenderer);
		mainMenuscreen();
		outputScreen("Team Count", SCREEN_WIDTH / 2, 50 , 60, RGB, 3 );
		writeOnScreenForGroups(mode1, mode2, mode3, mode4);
		outputScreen("press ESC to backout", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 , 30, RGB1, 3 );
		SDL_RenderPresent(sdlRenderer);
	}
	return -1;
}
int howManyStates() {
	int RGB[] = {120, 120, 120};
	int RGB1[] = {115, 115, 125};
	int mode1, mode2, mode3, mode4, mode5;
	writeOnScreenForMaps(1, 1, 1, 1);
	SDL_RenderPresent(sdlRenderer);
	int running = 1;
	int xMouse, yMouse;
	mainMenuscreen();
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			mode1 = 1; mode2 = 1; mode3 = 1; mode4 = 1, mode5 = 1;
			xMouse = event.motion.x;
			yMouse = event.motion.y;
			if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 100 < yMouse && yMouse < 220) {
				mode1 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 6;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 230 < yMouse && yMouse < 350) {
				mode2 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 9;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 360 < yMouse && yMouse < 480) {
				mode3 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 12;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 360 < yMouse && yMouse < 610) {
				mode4 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 15;}
			}
			else if (SCREEN_WIDTH / 2 - 250 < xMouse && xMouse < SCREEN_WIDTH / 2 + 250 && 620 < yMouse && yMouse < 740) {
				mode5 = 3;
				if (event.type == SDL_MOUSEBUTTONDOWN) {return 18;}
			}
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				return 0;
			}
			if  (event.type == SDL_QUIT) {
				TTF_Quit();
				SDL_Quit();
				exit(0);
			}
		}
		SDL_RenderClear(sdlRenderer);
		mainMenuscreen();
		outputScreen("Grey state Count", SCREEN_WIDTH / 2, 50 , 60, RGB, 3 );
		writeOnScreenForStates(mode1, mode2, mode3, mode4, mode5);
		outputScreen("press ESC to backout", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 , 30, RGB1, 3 );
		SDL_RenderPresent(sdlRenderer);
	}
	return -1;
}
int saveCheck() {
	FILE *test;
	SDL_StartTextInput();
	char input[20] =	{' '};
	int running = 1, nextIndex = 0, flag = 0;
	int RGB1[] = {158, 16, 48}, RGB[] = {115, 115, 125};
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_TEXTINPUT)
			{
				if (strlen(input) < 5) {
					if (*event.text.text - '0' >= 0 && *event.text.text - '0' < 10)
					{	strcat(input, event.text.text);
						nextIndex = strlen(input);
						flag = 0;
					}
				}
			} else if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && strlen(input) > 1) {
				input[nextIndex - 1] = '\0';
				nextIndex--;
			}
			else if (event.type == SDL_KEYDOWN  && event.key.keysym.sym == SDLK_RETURN && strlen(input) > 1) {

				int number;
				sscanf(input, " %d", &number);
				char temp[5];
				char string [50] = "res/DataBase/SavedMaps/";
				sprintf(temp, "%d", number);
				strcat(string, temp);
				strcat(string, "S.txt");

				test = fopen(string, "r");
				if (test == NULL)
				{
					input[0] = ' ';
					input[1] = '\0';
					nextIndex = 0;
					flag = 1;
				}
				else {
					SDL_StopTextInput();
					return number;
				}
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE) {SDL_StopTextInput(); return -1;}
			else if  (event.type == SDL_QUIT ) {
				SDL_StopTextInput();
				TTF_Quit();
				SDL_Quit();
				exit(0);
			}
			SDL_RenderClear(sdlRenderer);
			mainMenuscreen();
			if (flag) {outputScreen("invalid map name!", SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 13 * 5   , 50 , RGB1, 1);}
			outputScreen("enter your saved map (integer)", SCREEN_WIDTH / 2 , 650  , 50 , RGB1, 1);
			outputScreen("press ESC to backout", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 , 30, RGB, 3 );
			outputScreen(input, SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 13 * 5   , 50 , RGB, 1);
			SDL_RenderPresent(sdlRenderer);
			SDL_Delay(1000 / FPS);
		}
	}
	SDL_StopTextInput();
	return -1;
}
int SaveMap() {
	SDL_StartTextInput();
	FILE *data;
	char input[20] =	{' '};
	int running = 1, nextIndex = 0,	 RGB[] = {115, 115, 125}, RGB1[] = {158, 16, 48}, flag = 0;
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_TEXTINPUT)
			{
				if (strlen(input) < 5) {
					if (*event.text.text - '0' >= 0 && *event.text.text - '0' < 10)
					{	strcat(input, event.text.text);
						nextIndex = strlen(input);
						flag = 0;
					}
				}
			} else if ( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && strlen(input) > 1) {
				input[nextIndex - 1] = '\0';
				nextIndex--;
			} else if (event.type == SDL_KEYDOWN  && event.key.keysym.sym == SDLK_RETURN) {
				if (strlen(input) == 1) {SDL_StopTextInput(); return -1;}
				else {
					int number;
					sscanf(input, " %d", &number);
					//////////////////////////////
					char temp[5];
					char string [50] = "res/DataBase/SavedMaps/";
					sprintf(temp, "%d", number);
					strcat(string, temp);
					strcat(string, "S.txt");
					data = fopen(string, "r");
					if (data != NULL) {
						input[1] = '\0';
						flag = 1;
						fclose(data);
					} else {
						SDL_StopTextInput();
						return number;
					}
				}
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE) {SDL_StopTextInput(); return 0;}
			else if  (event.type == SDL_QUIT ) {
				SDL_StopTextInput();
				TTF_Quit();
				SDL_Quit();
				exit(0);
			}
		}
		SDL_Delay(1000 / FPS);
		SDL_RenderClear(sdlRenderer);
		mainMenuscreen();
		outputScreen(input, SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 13 * 5   , 50 , RGB1, 1);
		if (flag) {outputScreen("this name already exist", SCREEN_WIDTH / 2 , SCREEN_HEIGHT / 13 * 5   , 50 , RGB1, 1);}
		outputScreen("name your saved map (integer)", SCREEN_WIDTH / 2 , 650  , 50 , RGB1, 1);
		outputScreen("- if you dont need a save , just press enter -", SCREEN_WIDTH / 2 , 700  , 50 , RGB, 1);
		outputScreen("press ESC to backout", SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50 , 30, RGB, 3 );
		SDL_RenderPresent(sdlRenderer);
	}
	SDL_StopTextInput();
	return -1;
}
int mapChooseSetup(int id) {
	int G = 0, S = 0, name;
	int mode = mapChoosePreSetup();
	if (mode == 0) {return 0;}
	switch (mode) {
	case 1:
		gameSetup(1, id , 1, -1, -1, -1);
		break;
	case 2:
		gameSetup(1, id , 2, -1, -1, -1);
		break;
	case 3:
		G = howManyGroups(); if (G == 0) {return 0;}
		S = howManyStates(); if (S == 0) {return 0;}
		name = SaveMap(); if (name == 0) {return 0;}
		if (name == -1) {gameSetup(1, id, 3, G, S, -1);}
		else {gameSetup(1, id, 3, G, S, name);}
		break;
	case 4:
		name = saveCheck();
		if (name == -1) {return 0;}
		gameSetup(1, id, 4, -1, -1, name);
		break;
	}
	return 0 ;
}